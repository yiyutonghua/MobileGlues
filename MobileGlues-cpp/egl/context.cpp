// MobileGlues - egl/context.cpp
// Copyright (c) 2025-2026 MobileGL-Dev
// Licensed under the GNU Lesser General Public License v2.1:
//   https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
// SPDX-License-Identifier: LGPL-2.1-only
// End of Source File Header

#include "context.h"
#include "../gl/log.h"
#include "../gl/mg.h"
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#define DEBUG 0

thread_local MGContext* g_current_ctx = nullptr;

namespace {

// The library initialises itself from a static constructor, and that
// constructor reaches these tables through mg_display_initialised. A namespace
// scope std::unordered_map is dynamically initialised, so whether it had been
// constructed by then came down to the order the linker happened to emit the
// translation units in -- and it did not: the first insertion ran against an
// all zero map, whose zero max_load_factor asked for an infinite bucket count
// and aborted the process before main. Constructing on first use removes the
// ordering question instead of relying on it.
std::mutex& ctx_mutex() {
    static std::mutex m;
    return m;
}
std::unordered_map<EGLContext, std::shared_ptr<MGContext>>& contexts() {
    static std::unordered_map<EGLContext, std::shared_ptr<MGContext>> m;
    return m;
}
std::unordered_map<EGLDisplay, int>& display_refs() {
    static std::unordered_map<EGLDisplay, int> m;
    return m;
}

unsigned long long g_next_ctx_id = 1;
unsigned long long g_next_group_id = 1;

// The reference behind g_current_ctx. Same record, kept as a shared_ptr so this
// thread is a co-owner rather than a bystander watching the map's only reference.
// It is also what identifies the outgoing record in mg_context_make_current:
// looking it up by handle stopped being reliable the moment a handle could name a
// different record than the one this thread has current.
//
// Deliberately a plain shared_ptr and not something that releases on thread exit.
// A thread that dies with a context still current already leaks it -- the count
// never comes down -- and the map is still holding the record, so nothing is
// freed behind anyone's back. The one case where this destructor is the last
// owner is an orphan whose holder exits, which leaks that context's per-subsystem
// bookkeeping; a destructor that took g_ctx_mutex to do it properly would be
// running against function-local statics that may already have been destroyed at
// process exit, which is the worse of the two.
thread_local std::shared_ptr<MGContext> g_current_ref;

} // namespace

// Access sites read the same way they did when these were plain globals.
#define g_ctx_mutex ctx_mutex()
#define g_contexts contexts()
#define g_display_refs display_refs()

namespace {

// Caller holds g_ctx_mutex.
//
// By value: the caller's shared_ptr is often the one living in the map, and the
// erase below would destroy it -- and with it the record every line after that
// reads through.
void release_locked(std::shared_ptr<MGContext> ctx) {
    if (ctx->current_count > 0) return;

    // Identity, not handle. After eglCreateContext is handed back an address it
    // has just destroyed, g_contexts[handle] names a different record than this
    // one, and erasing by handle would drop the live context instead.
    const auto it = g_contexts.find(ctx->handle);
    const bool in_map = it != g_contexts.end() && it->second == ctx;
    // A record the map no longer names is an orphan: nothing can reach it any
    // more, so it goes as soon as its last holder lets go, whether or not
    // eglDestroyContext was ever called on it.
    if (in_map && !ctx->destroy_pending) return;

    LOG_D("MGContext %llu released", ctx->id)
    if (gl_state == &ctx->gl) gl_state = &g_default_gl_state;
    // Drop the per-context bookkeeping each subsystem keeps for this id. Safe
    // here and only here: current_count has reached zero, so no thread still has
    // a pointer into the entries being erased.
    mg_buffer_forget_context(ctx->id);
    mg_texture_forget_context(ctx->id);
    mg_framebuffer_forget_context(ctx->id);
    mg_fsr1_forget_context(ctx->id);
    mg_depth_clear_forget_context(ctx->id);
    if (in_map) g_contexts.erase(it);
}

} // namespace

MGContext* mg_context_create(EGLDisplay dpy, EGLContext handle, EGLContext share_handle, EGLenum client_type,
                             EGLint major, EGLint minor, EGLint profile_mask, EGLint context_flags) {
    if (handle == EGL_NO_CONTEXT) return nullptr;

    std::lock_guard<std::mutex> lock(g_ctx_mutex);

    auto ctx = std::make_shared<MGContext>();
    ctx->id = g_next_ctx_id++;
    ctx->display = dpy;
    ctx->handle = handle;
    ctx->client_type = client_type;
    ctx->granted_major = major;
    ctx->granted_minor = minor;
    ctx->profile_mask = profile_mask;
    ctx->context_flags = context_flags;
    ctx->draw = EGL_NO_SURFACE;
    ctx->read = EGL_NO_SURFACE;
    ctx->current_count = 0;
    ctx->destroy_pending = false;
    mg_enable_reset(&ctx->enable);
    ctx->gl = gl_state_s{};

    // A context created with a share handle joins that context's group, so the
    // objects GL shares stay described by one record.
    if (share_handle != EGL_NO_CONTEXT) {
        const auto it = g_contexts.find(share_handle);
        if (it != g_contexts.end()) {
            ctx->share_group = it->second->share_group;
        }
    }
    if (!ctx->share_group) {
        ctx->share_group = std::make_shared<MGShareGroup>();
        ctx->share_group->id = g_next_group_id++;
    }

    LOG_D("MGContext %llu created (handle %p, share group %llu, %d.%d)", ctx->id, handle, ctx->share_group->id, major,
          minor)

    // An EGLContext is a driver heap allocation, so the address of one that has
    // just been destroyed comes straight back out of the next create. The record
    // for the old one can still be alive at that point -- eglDestroyContext only
    // marks a context that is current, and it stays until the last thread makes
    // something else current -- and assigning over the map entry dropped the map's
    // reference, which was the only one. That freed a record another thread had
    // current, leaving g_current_ctx and the gl_state_s inside it dangling.
    //
    // Orphan it instead: out of the map so nothing new can find it, alive until
    // whoever still has it current lets go.
    const auto stale = g_contexts.find(handle);
    if (stale != g_contexts.end()) {
        const std::shared_ptr<MGContext> previous = stale->second;
        g_contexts.erase(stale);
        LOG_D("MGContext %llu orphaned: handle %p was handed out again", previous->id, handle)
        release_locked(previous);
    }

    g_contexts[handle] = ctx;
    return ctx.get();
}

void mg_display_initialised(EGLDisplay dpy) {
    if (dpy == EGL_NO_DISPLAY) return;
    std::lock_guard<std::mutex> lock(g_ctx_mutex);
    ++g_display_refs[dpy];
    LOG_D("EGLDisplay %p initialise count -> %d", dpy, g_display_refs[dpy])
}

bool mg_display_release(EGLDisplay dpy) {
    if (dpy == EGL_NO_DISPLAY) return false;
    std::lock_guard<std::mutex> lock(g_ctx_mutex);
    const auto it = g_display_refs.find(dpy);
    if (it == g_display_refs.end()) return false;
    if (--it->second > 0) return false;
    g_display_refs.erase(it);
    return true;
}

MGContext* mg_context_find(EGLContext handle) {
    if (handle == EGL_NO_CONTEXT) return nullptr;
    std::lock_guard<std::mutex> lock(g_ctx_mutex);
    const auto it = g_contexts.find(handle);
    return it == g_contexts.end() ? nullptr : it->second.get();
}

void mg_context_make_current(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext handle) {
    std::lock_guard<std::mutex> lock(g_ctx_mutex);

    // The same record going current again, which is what an application that calls
    // eglMakeCurrent once a frame does. Nothing the rebind below sets up can have
    // changed, and mg_enable_sync_driver is a round of driver calls, so only the
    // surfaces are worth updating.
    if (g_current_ref && handle != EGL_NO_CONTEXT) {
        const auto same = g_contexts.find(handle);
        if (same != g_contexts.end() && same->second == g_current_ref) {
            g_current_ref->display = dpy;
            g_current_ref->draw = draw;
            g_current_ref->read = read;
            return;
        }
    }

    if (g_current_ref) {
        // Through this thread's own reference, never through g_contexts[handle]:
        // once a handle has been handed out twice the map entry for it is a
        // different record, and decrementing that one would release a live context
        // and strand this one at a count it can never come down from.
        if (g_current_ref->current_count > 0) --g_current_ref->current_count;
        const std::shared_ptr<MGContext> previous = std::move(g_current_ref);
        g_current_ref.reset();
        g_current_ctx = nullptr;
        gl_state = &g_default_gl_state;
        // 0 selects each subsystem's fallback instance, the one used before any
        // tracked context is current.
        mg_buffer_bind_context(0, 0);
        mg_texture_bind_context(0, 0);
        mg_framebuffer_bind_context(0);
        mg_fsr1_bind_context(0);
        // Releasing here is why eglDestroyContext can be called on a context
        // that is still current: the record outlives the EGL handle until the
        // last thread lets go of it.
        release_locked(previous);
    }

    if (handle == EGL_NO_CONTEXT) {
        LOG_D("MGContext: no context current on this thread")
        return;
    }

    const auto it = g_contexts.find(handle);
    if (it == g_contexts.end()) {
        // A context this layer never saw created -- the bootstrap probe context,
        // or one made before the library was loaded. Leaving g_current_ctx null
        // keeps every consumer on its fallback path rather than inventing a
        // record with made-up attributes.
        LOG_D("MGContext: handle %p is not tracked, leaving no current record", handle)
        return;
    }

    it->second->display = dpy;
    it->second->draw = draw;
    it->second->read = read;
    ++it->second->current_count;
    g_current_ref = it->second;
    g_current_ctx = g_current_ref.get();
    mg_buffer_bind_context(g_current_ctx->id, g_current_ctx->share_group->id);
    mg_texture_bind_context(g_current_ctx->id, g_current_ctx->share_group->id);
    mg_framebuffer_bind_context(g_current_ctx->id);
    mg_fsr1_bind_context(g_current_ctx->id);
    // Repoint the shared gl_state at this context's copy. Everything that reads
    // gl_state-> keeps working unchanged; it simply stops being one set of values
    // for every context in the process.
    gl_state = &g_current_ctx->gl;
    // Now, and not in mg_context_create() where nothing was current yet, the
    // enable table can talk to the driver.
    mg_enable_sync_driver(&g_current_ctx->enable);
    LOG_D("MGContext %llu is now current", it->second->id)
}

void mg_context_destroy(EGLContext handle) {
    if (handle == EGL_NO_CONTEXT) return;
    std::lock_guard<std::mutex> lock(g_ctx_mutex);
    const auto it = g_contexts.find(handle);
    if (it == g_contexts.end()) return;

    it->second->destroy_pending = true;
    // Deliberately not erased while still current: GL permits destroying a
    // context that is current, and the record has to answer queries until the
    // last thread makes something else current.
    release_locked(it->second);
}

void mg_context_forget_display(EGLDisplay dpy) {
    std::lock_guard<std::mutex> lock(g_ctx_mutex);
    std::vector<std::shared_ptr<MGContext>> doomed;
    for (auto& entry : g_contexts) {
        if (entry.second->display != dpy) continue;
        // eglTerminate marks resources for deletion but a context that is still
        // current stays usable until it is replaced, so it survives -- which is
        // what release_locked decides, one record at a time.
        entry.second->destroy_pending = true;
        doomed.push_back(entry.second);
    }
    // Collected first because release_locked erases, and every erase goes through
    // it: this loop used to drop entries inline, skipping the per-subsystem
    // teardown, so the bookkeeping for every context on a terminated display
    // outlived the display for the life of the process.
    for (const auto& ctx : doomed) release_locked(ctx);
}
