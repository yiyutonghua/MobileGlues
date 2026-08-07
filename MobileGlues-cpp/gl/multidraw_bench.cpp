// MobileGlues - gl/multidraw_bench.cpp
// Copyright (c) 2025-2026 MobileGL-Dev
// Licensed under the GNU Lesser General Public License v2.1:
//   https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
// SPDX-License-Identifier: LGPL-2.1-only
// End of Source File Header

// In-process micro benchmark behind the plugin app's "benchmark and sort"
// button. The app dlopens this library, makes a context current through our own
// EGL layer (the same path MGInfoGetter uses to query GL info), then calls
// mg_multidraw_bench_run() and reads back one JSON string.
//
// The measurement therefore runs on the same GPU and driver the game will use,
// but in the plugin app's process, not the game's -- an accepted trade-off for
// being able to run it immediately instead of piggybacking on the next game
// launch (see the delivery notes).
//
// Each (entry point, backend) pair is timed by calling the mg_* implementation
// the dispatcher itself would call, so translation overhead is included. A
// measurement is discarded when g_md_fallback_tick moved, because that means
// the call was actually served by a different backend and the number would be
// a lie.
//
// What this benchmark is really up against is noise, not measurement: the
// numbers being compared are often within a few percent of each other, while a
// phone under a DVFS governor can shift by tens of percent within a second. So
// the schedule matters more than the timer:
//
//   * candidates are measured round-robin, not one candidate to completion --
//     a frequency ramp or a thermal drift then hits every candidate alike
//     instead of systematically favouring whoever was measured while the clock
//     was high;
//   * the traversal order flips every other round, so a candidate cannot
//     profit from always following the same neighbour;
//   * each candidate gets its own iteration count, picked so that one timed
//     batch lasts long enough for the glFinish and clock_gettime overhead to
//     stop mattering -- backends here differ by two orders of magnitude in cost
//     per call, and a fixed count cannot serve both ends;
//   * the reported number is the median over all rounds, not the mean. A
//     scheduler hiccup or a stray compositor frame lands on one round and the
//     median ignores it, whereas a mean would carry it into the ranking;
//   * the spread across rounds is reported alongside, so the UI can tell the
//     user when two candidates are simply too close to separate.
//
// Total wall time is a budget (MG_BENCH_BUDGET_MS, default 8 s) rather than a
// fixed amount of work: a slow device does fewer rounds instead of making the
// user wait proportionally longer.
//
// If a pass still comes out too shaky to rank anything by, it is repeated with
// longer batches -- up to four passes. When even the fourth misses the target,
// the calmest of the four is reported with noisy=true and the app puts the
// decision to the user rather than presenting noise as a measurement.

#include "multidraw.h"
#include "../config/settings.h"
#include "../config/cJSON.h"
#include "../gles/loader.h"
#include "log.h"

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <vector>

extern std::atomic<uint32_t> g_md_fallback_tick;

// Progress of the current run, as attempt * 1000 + permille within that attempt
// (attempt is 0-based). A retry restarts the bar, which is what actually
// happened; keeping both numbers in one atomic keeps them consistent for the
// thread reading them through mg_multidraw_bench_progress().
static std::atomic<int> g_bench_progress{0};

namespace {

constexpr GLsizei BENCH_SUBDRAWS = 96;   // sub-draws per multi-draw call
constexpr GLsizei BENCH_INDICES = 24;    // indices per sub-draw, whole triangles

// Enough to get past compute shader compilation, scratch buffer growth and the
// first-call probes, and to let the GPU governor notice we are here.
constexpr int BENCH_WARMUP = 8;

// One timed batch aims for this long. Below roughly a millisecond the glFinish
// round trip and the timer resolution start showing up in the result.
constexpr double BENCH_TARGET_BATCH_US = 2000.0;
constexpr int BENCH_MIN_ITERATIONS = 2;
constexpr int BENCH_MAX_ITERATIONS = 8192;

// Odd round counts so the median is a real sample rather than an average of
// two. Five is the floor at which a single outlier cannot move the median.
constexpr int BENCH_MIN_ROUNDS = 5;
constexpr int BENCH_MAX_ROUNDS = 101;

constexpr double BENCH_DEFAULT_BUDGET_US = 8.0e6;
constexpr double BENCH_MIN_BUDGET_US = 1.0e6;
constexpr double BENCH_MAX_BUDGET_US = 120.0e6;

// A spread wider than this means candidates within a few percent of each other
// cannot be told apart, so the pass is retried with longer batches.
constexpr double BENCH_NOISE_TARGET = 0.15;
constexpr int BENCH_MAX_ATTEMPTS = 4;
constexpr double BENCH_MIN_RETRY_SCALE = 2.0;
constexpr double BENCH_MAX_RETRY_SCALE = 8.0;
// How much longer than the base budget a single retry may take, and how long
// the whole thing may take before giving up on ever settling down.
constexpr double BENCH_MAX_BUDGET_SCALE = 3.0;
constexpr double BENCH_TOTAL_BUDGET_US = 75.0e6;

// Written when a run finishes, past any value a real attempt can produce.
constexpr int BENCH_PROGRESS_DONE = BENCH_MAX_ATTEMPTS * 1000;

struct bench_scene_t {
    GLuint program = 0;
    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ibo = 0;
    GLuint indirect_elements = 0;
    GLuint indirect_arrays = 0;

    std::vector<GLsizei> counts;
    std::vector<const void*> offsets; // byte offsets into the IBO
    std::vector<GLint> basevertex;
    std::vector<GLint> firsts;

    bool ok = false;
    std::string error;
};

double now_us() {
    timespec ts{};
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return static_cast<double>(ts.tv_sec) * 1e6 + static_cast<double>(ts.tv_nsec) / 1e3;
}

GLuint bench_compile(GLenum type, const char* src, std::string* err) {
    GLuint shader = GLES.glCreateShader(type);
    GLES.glShaderSource(shader, 1, &src, nullptr);
    GLES.glCompileShader(shader);
    GLint ok = GL_FALSE;
    GLES.glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512] = {0};
        GLES.glGetShaderInfoLog(shader, sizeof(log) - 1, nullptr, log);
        *err = std::string("shader compile failed: ") + log;
        GLES.glDeleteShader(shader);
        return 0;
    }
    return shader;
}

// The scene goes straight through the GLES table: the multidraw backends read
// GL state through the same table, and the frontend state machine plays no part
// in what is being measured.
void bench_scene_build(bench_scene_t& s) {
    if (!GLES.glCreateShader || !GLES.glGenVertexArrays || !GLES.glGenBuffers) {
        s.error = "GLES entry points missing";
        return;
    }

    const char* vs_src = "#version 300 es\n"
                         "layout(location = 0) in vec2 aPos;\n"
                         "void main() { gl_Position = vec4(aPos, 0.0, 1.0); }\n";
    const char* fs_src = "#version 300 es\n"
                         "precision mediump float;\n"
                         "out vec4 oColor;\n"
                         "void main() { oColor = vec4(0.5); }\n";

    std::string err;
    GLuint vs = bench_compile(GL_VERTEX_SHADER, vs_src, &err);
    if (!vs) {
        s.error = err;
        return;
    }
    GLuint fs = bench_compile(GL_FRAGMENT_SHADER, fs_src, &err);
    if (!fs) {
        GLES.glDeleteShader(vs);
        s.error = err;
        return;
    }
    s.program = GLES.glCreateProgram();
    GLES.glAttachShader(s.program, vs);
    GLES.glAttachShader(s.program, fs);
    GLES.glLinkProgram(s.program);
    GLES.glDeleteShader(vs);
    GLES.glDeleteShader(fs);
    GLint linked = GL_FALSE;
    GLES.glGetProgramiv(s.program, GL_LINK_STATUS, &linked);
    if (!linked) {
        s.error = "program link failed";
        return;
    }
    GLES.glUseProgram(s.program);

    // 1024 vertices in a tiny square; every draw lands on the same few pixels of
    // the 1x1 pbuffer, which is exactly what a driver-overhead benchmark wants.
    std::vector<float> verts(1024 * 2);
    for (size_t i = 0; i < verts.size(); i += 2) {
        verts[i] = static_cast<float>(i % 17) / 17.0f * 0.01f;
        verts[i + 1] = static_cast<float>(i % 13) / 13.0f * 0.01f;
    }

    // Index values stay under 512 so index + basevertex (< 256) stays in range.
    std::vector<GLushort> indices(static_cast<size_t>(BENCH_SUBDRAWS) * BENCH_INDICES);
    for (size_t i = 0; i < indices.size(); ++i) {
        indices[i] = static_cast<GLushort>((i * 7) % 512);
    }

    GLES.glGenVertexArrays(1, &s.vao);
    GLES.glBindVertexArray(s.vao);

    GLES.glGenBuffers(1, &s.vbo);
    GLES.glBindBuffer(GL_ARRAY_BUFFER, s.vbo);
    GLES.glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(verts.size() * sizeof(float)), verts.data(),
                      GL_STATIC_DRAW);
    GLES.glEnableVertexAttribArray(0);
    GLES.glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    GLES.glGenBuffers(1, &s.ibo);
    GLES.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s.ibo);
    GLES.glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(GLushort)),
                      indices.data(), GL_STATIC_DRAW);

    s.counts.assign(BENCH_SUBDRAWS, BENCH_INDICES);
    s.offsets.resize(BENCH_SUBDRAWS);
    s.basevertex.resize(BENCH_SUBDRAWS);
    s.firsts.resize(BENCH_SUBDRAWS);
    for (GLsizei i = 0; i < BENCH_SUBDRAWS; ++i) {
        s.offsets[i] =
            reinterpret_cast<const void*>(static_cast<uintptr_t>(i) * BENCH_INDICES * sizeof(GLushort));
        s.basevertex[i] = (i * 3) % 256;
        s.firsts[i] = (i * 5) % 512;
    }

    // Command buffers for the two *Indirect entry points, which take commands
    // from the application instead of building them.
    struct {
        GLuint count, instanceCount, firstIndex;
        GLint baseVertex;
        GLuint reserved;
    } elem_cmds[BENCH_SUBDRAWS];
    struct {
        GLuint count, instanceCount, first, reserved;
    } array_cmds[BENCH_SUBDRAWS];
    for (GLsizei i = 0; i < BENCH_SUBDRAWS; ++i) {
        elem_cmds[i] = {static_cast<GLuint>(BENCH_INDICES), 1, static_cast<GLuint>(i * BENCH_INDICES),
                        s.basevertex[i], 0};
        array_cmds[i] = {static_cast<GLuint>(BENCH_INDICES), 1, static_cast<GLuint>(s.firsts[i]), 0};
    }
    GLES.glGenBuffers(1, &s.indirect_elements);
    GLES.glBindBuffer(GL_DRAW_INDIRECT_BUFFER, s.indirect_elements);
    GLES.glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(elem_cmds), elem_cmds, GL_STATIC_DRAW);
    GLES.glGenBuffers(1, &s.indirect_arrays);
    GLES.glBindBuffer(GL_DRAW_INDIRECT_BUFFER, s.indirect_arrays);
    GLES.glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(array_cmds), array_cmds, GL_STATIC_DRAW);
    GLES.glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);

    GLES.glViewport(0, 0, 1, 1);
    while (GLES.glGetError() != GL_NO_ERROR) {
    }
    s.ok = true;
}

void bench_scene_destroy(bench_scene_t& s) {
    if (s.indirect_arrays) GLES.glDeleteBuffers(1, &s.indirect_arrays);
    if (s.indirect_elements) GLES.glDeleteBuffers(1, &s.indirect_elements);
    if (s.ibo) GLES.glDeleteBuffers(1, &s.ibo);
    if (s.vbo) GLES.glDeleteBuffers(1, &s.vbo);
    if (s.vao) GLES.glDeleteVertexArrays(1, &s.vao);
    if (s.program) GLES.glDeleteProgram(s.program);
}

// One measured call of `entry` on `backend`. Returns false when the call cannot
// be issued at all (no implementation for the pair).
bool bench_issue(bench_scene_t& s, md_entry_t entry, md_backend_t backend) {
    using B = md_backend_t;
    const GLsizei n = BENCH_SUBDRAWS;
    switch (entry) {
    case md_entry_t::Elements:
        switch (backend) {
        case B::Unroll:
            mg_glMultiDrawElements_drawelements(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT, s.offsets.data(), n);
            return true;
        case B::Indirect:
            mg_glMultiDrawElements_indirect(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT, s.offsets.data(), n);
            return true;
        case B::MultiIndirect:
            mg_glMultiDrawElements_multiindirect(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT, s.offsets.data(),
                                                 n);
            return true;
        case B::MultiBaseVertex:
            mg_glMultiDrawElements_multibasevertex(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT, s.offsets.data(),
                                                   n);
            return true;
        case B::MultiArrays:
            mg_glMultiDrawElements_multiarrays(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT, s.offsets.data(), n);
            return true;
        default:
            return false;
        }
    case md_entry_t::ElementsBaseVertex:
        switch (backend) {
        case B::Unroll:
            mg_glMultiDrawElementsBaseVertex_drawelements(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT,
                                                          s.offsets.data(), n, s.basevertex.data());
            return true;
        case B::BaseVertex:
            mg_glMultiDrawElementsBaseVertex_basevertex(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT,
                                                        s.offsets.data(), n, s.basevertex.data());
            return true;
        case B::Indirect:
            mg_glMultiDrawElementsBaseVertex_indirect(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT,
                                                      s.offsets.data(), n, s.basevertex.data());
            return true;
        case B::MultiIndirect:
            mg_glMultiDrawElementsBaseVertex_multiindirect(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT,
                                                           s.offsets.data(), n, s.basevertex.data());
            return true;
        case B::MultiBaseVertex:
            mg_glMultiDrawElementsBaseVertex_multibasevertex(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT,
                                                             s.offsets.data(), n, s.basevertex.data());
            return true;
        case B::Compute:
            mg_glMultiDrawElementsBaseVertex_compute(GL_TRIANGLES, s.counts.data(), GL_UNSIGNED_SHORT,
                                                     s.offsets.data(), n, s.basevertex.data());
            return true;
        default:
            return false;
        }
    case md_entry_t::Arrays:
        switch (backend) {
        case B::Unroll:
            mg_glMultiDrawArrays_unroll(GL_TRIANGLES, s.firsts.data(), s.counts.data(), n);
            return true;
        case B::MultiArrays:
            mg_glMultiDrawArrays_multiarrays(GL_TRIANGLES, s.firsts.data(), s.counts.data(), n);
            return true;
        case B::MultiIndirect:
            mg_glMultiDrawArrays_multiindirect(GL_TRIANGLES, s.firsts.data(), s.counts.data(), n);
            return true;
        default:
            return false;
        }
    case md_entry_t::ArraysIndirect:
        // The application supplies the command buffer, so the two variants are
        // reproduced directly: one driver call vs. a walk of the commands.
        GLES.glBindBuffer(GL_DRAW_INDIRECT_BUFFER, s.indirect_arrays);
        if (backend == B::MultiIndirect) {
            if (!GLES.glMultiDrawArraysIndirectEXT) return false;
            GLES.glMultiDrawArraysIndirectEXT(GL_TRIANGLES, nullptr, n, 0);
            return true;
        }
        if (backend == B::Indirect) {
            if (!GLES.glDrawArraysIndirect) return false;
            for (GLsizei i = 0; i < n; ++i) {
                GLES.glDrawArraysIndirect(GL_TRIANGLES, reinterpret_cast<const void*>(
                                                            static_cast<uintptr_t>(i) * 4 * sizeof(GLuint)));
            }
            return true;
        }
        return false;
    case md_entry_t::ElementsIndirect:
        GLES.glBindBuffer(GL_DRAW_INDIRECT_BUFFER, s.indirect_elements);
        if (backend == B::MultiIndirect) {
            if (!GLES.glMultiDrawElementsIndirectEXT) return false;
            GLES.glMultiDrawElementsIndirectEXT(GL_TRIANGLES, GL_UNSIGNED_SHORT, nullptr, n, 0);
            return true;
        }
        if (backend == B::Indirect) {
            if (!GLES.glDrawElementsIndirect) return false;
            for (GLsizei i = 0; i < n; ++i) {
                GLES.glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_SHORT,
                                            reinterpret_cast<const void*>(static_cast<uintptr_t>(i) * 5 *
                                                                          sizeof(GLuint)));
            }
            return true;
        }
        return false;
    default:
        return false;
    }
}

// One (entry point, backend) pair that survived probing, with its per-round
// samples in microseconds per multi-draw call.
struct bench_candidate_t {
    md_entry_t entry = md_entry_t::Arrays;
    md_backend_t backend = md_backend_t::Unroll;
    int iterations = 1;
    double probe_us = 0.0;      // rough cost from probing, used to size rounds
    std::vector<double> samples;
    int discarded = 0;          // rounds thrown away because a fallback fired
};

// Runs `iterations` calls back to back and returns microseconds per call, or a
// negative value if a fallback fired during the batch (the number would then
// describe some other backend).
double bench_timed_batch(bench_scene_t& s, md_entry_t entry, md_backend_t backend, int iterations) {
    const uint32_t tick_before = g_md_fallback_tick.load(std::memory_order_relaxed);
    GLES.glFinish();
    const double t0 = now_us();
    for (int i = 0; i < iterations; ++i) {
        bench_issue(s, entry, backend);
    }
    GLES.glFinish();
    const double t1 = now_us();
    if (g_md_fallback_tick.load(std::memory_order_relaxed) != tick_before) return -1.0;
    return (t1 - t0) / iterations;
}

double bench_median(std::vector<double> v) {
    if (v.empty()) return 0.0;
    const size_t mid = v.size() / 2;
    std::nth_element(v.begin(), v.begin() + mid, v.end());
    const double hi = v[mid];
    if (v.size() % 2 != 0) return hi;
    const double lo = *std::max_element(v.begin(), v.begin() + mid);
    return (lo + hi) / 2.0;
}

// Median absolute deviation, scaled to be comparable to a standard deviation on
// normal data. Unlike a standard deviation it does not let one bad round
// dominate the spread it reports.
double bench_mad(const std::vector<double>& v, double median) {
    if (v.empty()) return 0.0;
    std::vector<double> dev;
    dev.reserve(v.size());
    for (double x : v) dev.push_back(std::fabs(x - median));
    return 1.4826 * bench_median(std::move(dev));
}

// One complete pass over every candidate, and how well it came out.
struct bench_attempt_t {
    std::vector<bench_candidate_t> candidates;
    int rounds = 0;
    double worst_rsd = 0.0;
};

// The spread of the shakiest candidate is the grade for the whole pass: the
// ranking is only as trustworthy as its least stable member.
double bench_worst_rsd(const std::vector<bench_candidate_t>& candidates) {
    double worst = 0.0;
    for (const bench_candidate_t& c : candidates) {
        // Fewer than three samples cannot say anything about spread, and a
        // candidate that kept falling back never really ran.
        if (c.samples.size() < 3) continue;
        if (c.samples.size() * 2 <= static_cast<size_t>(c.discarded)) continue;
        const double median = bench_median(c.samples);
        if (median <= 0.0) continue;
        worst = std::max(worst, bench_mad(c.samples, median) / median);
    }
    return worst;
}

// One round-robin pass. `templ` supplies the candidate list and the per-candidate
// batch size; samples come back in the returned copy.
bench_attempt_t bench_measure(bench_scene_t& scene, const std::vector<bench_candidate_t>& templ,
                              double budget_us, int attempt) {
    bench_attempt_t result;
    result.candidates = templ;
    for (bench_candidate_t& c : result.candidates) {
        c.samples.clear();
        c.discarded = 0;
    }

    double per_round_us = 0.0;
    for (const bench_candidate_t& c : result.candidates) {
        per_round_us += c.probe_us * c.iterations;
    }
    // Two glFinish round trips per batch, generously accounted for.
    per_round_us += static_cast<double>(result.candidates.size()) * 400.0;

    int rounds = per_round_us > 0.0 ? static_cast<int>(budget_us / per_round_us) : BENCH_MIN_ROUNDS;
    rounds = std::min(std::max(rounds, BENCH_MIN_ROUNDS), BENCH_MAX_ROUNDS);
    if (rounds % 2 == 0) ++rounds;

    const double start_us = now_us();
    const int total_batches = rounds * static_cast<int>(result.candidates.size());
    int completed = 0;
    for (int r = 0; r < rounds; ++r) {
        const bool forward = (r % 2) == 0;
        for (size_t i = 0; i < result.candidates.size(); ++i) {
            bench_candidate_t& c =
                result.candidates[forward ? i : result.candidates.size() - 1 - i];
            const double us = bench_timed_batch(scene, c.entry, c.backend, c.iterations);
            if (us < 0.0) {
                ++c.discarded;
            } else {
                c.samples.push_back(us);
            }
            ++completed;
            g_bench_progress.store(attempt * 1000 + completed * 1000 / total_batches,
                                   std::memory_order_relaxed);
        }
        // Overrunning the budget is worse than one round short: the user is
        // staring at a spinner, and the median is already stable by now.
        if (r + 1 >= BENCH_MIN_ROUNDS && now_us() - start_us > budget_us) {
            rounds = r + 1;
            break;
        }
    }

    result.rounds = rounds;
    result.worst_rsd = bench_worst_rsd(result.candidates);
    return result;
}

double bench_budget_us() {
    double budget = BENCH_DEFAULT_BUDGET_US;
    if (const char* raw = getenv("MG_BENCH_BUDGET_MS")) {
        char* end = nullptr;
        const double ms = strtod(raw, &end);
        if (end != raw && ms > 0.0) budget = ms * 1000.0;
    }
    return std::min(std::max(budget, BENCH_MIN_BUDGET_US), BENCH_MAX_BUDGET_US);
}

const char* bench_entry_label(md_entry_t e) {
    switch (e) {
    case md_entry_t::Arrays:
        return "glMultiDrawArrays";
    case md_entry_t::Elements:
        return "glMultiDrawElements";
    case md_entry_t::ElementsBaseVertex:
        return "glMultiDrawElementsBaseVertex";
    case md_entry_t::ArraysIndirect:
        return "glMultiDrawArraysIndirect";
    case md_entry_t::ElementsIndirect:
        return "glMultiDrawElementsIndirect";
    default:
        return "?";
    }
}

} // namespace

// attempt * 1000 + permille within that attempt, attempt 0-based. Stays at its
// last value once the run returns; the caller decides what to do with that.
extern "C" __attribute__((visibility("default"))) int mg_multidraw_bench_progress() {
    return g_bench_progress.load(std::memory_order_relaxed);
}

extern "C" __attribute__((visibility("default"))) const char* mg_multidraw_bench_run() {
    static std::string result;

    g_bench_progress.store(0, std::memory_order_relaxed);

    const double budget_us = bench_budget_us();
    const double started_us = now_us();

    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "version", 2);
    cJSON_AddNumberToObject(root, "subDraws", BENCH_SUBDRAWS);
    cJSON_AddNumberToObject(root, "indicesPerSubDraw", BENCH_INDICES);
    cJSON_AddNumberToObject(root, "budgetMs", budget_us / 1000.0);

    bench_scene_t scene;
    bench_scene_build(scene);
    if (!scene.ok) {
        cJSON_AddStringToObject(root, "error", scene.error.c_str());
        char* text = cJSON_PrintUnformatted(root);
        result = text ? text : "{\"error\":\"print failed\"}";
        cJSON_free(text);
        cJSON_Delete(root);
        bench_scene_destroy(scene);
        g_bench_progress.store(BENCH_PROGRESS_DONE, std::memory_order_relaxed);
        return result.c_str();
    }

    // ---- Probe: who can actually run, and how long one call takes ----
    //
    // The cost estimate here is deliberately crude. It only has to be right to
    // within a factor of a few, because all it decides is how many calls go
    // into one timed batch.

    std::vector<bench_candidate_t> candidates;
    for (int ei = 0; ei < MD_ENTRY_COUNT; ++ei) {
        const md_entry_t entry = static_cast<md_entry_t>(ei);
        const int order_len = global_settings.multidraw_order_len[ei];
        for (int k = 0; k < order_len; ++k) {
            const md_backend_t backend = global_settings.multidraw_order[ei][k];

            const uint32_t tick_before_warmup = g_md_fallback_tick.load(std::memory_order_relaxed);
            bool issued = true;
            for (int w = 0; w < BENCH_WARMUP && issued; ++w) {
                issued = bench_issue(scene, entry, backend);
            }
            GLES.glFinish();
            if (!issued) continue;
            if (g_md_fallback_tick.load(std::memory_order_relaxed) != tick_before_warmup) {
                // The warmup was served by some other backend: the driver cannot
                // actually run this one. No number is better than a wrong one.
                continue;
            }

            const double probe_us = bench_timed_batch(scene, entry, backend, 4);
            if (probe_us < 0.0) continue;

            bench_candidate_t c;
            c.entry = entry;
            c.backend = backend;
            c.probe_us = probe_us;
            const double want = probe_us > 0.0 ? BENCH_TARGET_BATCH_US / probe_us : BENCH_MAX_ITERATIONS;
            c.iterations = static_cast<int>(
                std::min(std::max(want, static_cast<double>(BENCH_MIN_ITERATIONS)),
                         static_cast<double>(BENCH_MAX_ITERATIONS)));
            candidates.push_back(std::move(c));
        }
    }

    if (candidates.empty()) {
        cJSON_AddStringToObject(root, "error", "no measurable backend on this device");
        char* text = cJSON_PrintUnformatted(root);
        result = text ? text : "{\"error\":\"print failed\"}";
        cJSON_free(text);
        cJSON_Delete(root);
        bench_scene_destroy(scene);
        g_bench_progress.store(BENCH_PROGRESS_DONE, std::memory_order_relaxed);
        return result.c_str();
    }

    // ---- Measure, and measure again if the numbers are too shaky ----
    //
    // The spread being fought here is between rounds, so adding rounds does not
    // shrink it -- it only pins it down more precisely. What shrinks it is a
    // longer timed batch, which averages the jitter away inside each sample:
    // spread falls as 1/sqrt(batch length), so reaching the target from a
    // spread k times too large means batches roughly k^2 times longer.
    //
    // Four passes at most. If none of them lands under the target, the calmest
    // one is reported with noisy=true, and the caller asks the user whether an
    // order that shaky is worth adopting.

    bench_attempt_t best;
    bool have_best = false;
    double budget_scale = 1.0;
    int attempt = 0;
    for (; attempt < BENCH_MAX_ATTEMPTS; ++attempt) {
        const double attempt_budget = budget_us * budget_scale;
        bench_attempt_t pass = bench_measure(scene, candidates, attempt_budget, attempt);
        if (!have_best || pass.worst_rsd < best.worst_rsd) {
            best = std::move(pass);
            have_best = true;
        }
        if (best.worst_rsd <= BENCH_NOISE_TARGET) break;
        if (attempt + 1 >= BENCH_MAX_ATTEMPTS) break;
        // A device this busy will not settle down within any budget we are
        // willing to make the user sit through.
        if (now_us() - started_us > BENCH_TOTAL_BUDGET_US) break;

        double scale = best.worst_rsd / BENCH_NOISE_TARGET;
        scale = std::min(std::max(scale * scale, BENCH_MIN_RETRY_SCALE), BENCH_MAX_RETRY_SCALE);
        for (bench_candidate_t& c : candidates) {
            c.iterations = static_cast<int>(std::min(c.iterations * scale,
                                                     static_cast<double>(BENCH_MAX_ITERATIONS)));
        }
        // Longer batches with the same budget would just mean fewer rounds, so
        // the budget grows with them -- up to a cap, since the user is waiting.
        budget_scale = std::min(budget_scale * scale, BENCH_MAX_BUDGET_SCALE);
    }

    const int attempts = attempt + 1;
    const bool noisy = best.worst_rsd > BENCH_NOISE_TARGET;
    candidates = std::move(best.candidates);
    const int rounds = best.rounds;

    // ---- Report ----

    cJSON* entries = cJSON_AddObjectToObject(root, "entries");
    cJSON* stats = cJSON_AddObjectToObject(root, "stats");
    for (int ei = 0; ei < MD_ENTRY_COUNT; ++ei) {
        const md_entry_t entry = static_cast<md_entry_t>(ei);
        const char* label = bench_entry_label(entry);
        cJSON* entry_obj = cJSON_AddObjectToObject(entries, label);
        cJSON* stats_obj = cJSON_AddObjectToObject(stats, label);

        for (const bench_candidate_t& c : candidates) {
            if (c.entry != entry) continue;
            // A backend that kept falling back mid-run never really ran; the
            // few rounds that did survive describe a driver we cannot rely on.
            if (c.samples.size() * 2 <= static_cast<size_t>(c.discarded)) continue;
            if (c.samples.empty()) continue;

            const double median = bench_median(c.samples);
            const double mad = bench_mad(c.samples, median);
            const double best = *std::min_element(c.samples.begin(), c.samples.end());

            cJSON_AddNumberToObject(entry_obj, md_backend_name(c.backend), median);

            cJSON* st = cJSON_AddObjectToObject(stats_obj, md_backend_name(c.backend));
            cJSON_AddNumberToObject(st, "median", median);
            cJSON_AddNumberToObject(st, "mad", mad);
            cJSON_AddNumberToObject(st, "rsd", median > 0.0 ? mad / median : 0.0);
            cJSON_AddNumberToObject(st, "best", best);
            cJSON_AddNumberToObject(st, "samples", static_cast<double>(c.samples.size()));
            cJSON_AddNumberToObject(st, "discarded", c.discarded);
            cJSON_AddNumberToObject(st, "iterations", c.iterations);
        }
    }

    cJSON_AddNumberToObject(root, "rounds", rounds);
    cJSON_AddNumberToObject(root, "attempts", attempts);
    cJSON_AddNumberToObject(root, "worstNoise", best.worst_rsd);
    cJSON_AddNumberToObject(root, "noiseTarget", BENCH_NOISE_TARGET);
    cJSON_AddBoolToObject(root, "noisy", noisy);
    cJSON_AddNumberToObject(root, "elapsedMs", (now_us() - started_us) / 1000.0);

    GLES.glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
    bench_scene_destroy(scene);

    char* text = cJSON_PrintUnformatted(root);
    result = text ? text : "{\"error\":\"print failed\"}";
    cJSON_free(text);
    cJSON_Delete(root);
    g_bench_progress.store(BENCH_PROGRESS_DONE, std::memory_order_relaxed);
    return result.c_str();
}
