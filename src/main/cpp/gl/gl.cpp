﻿//
// Created by Swung0x48 on 2024/10/8.
//

#include "../includes.h"
#include <GL/gl.h>
#include "glcorearb.h"
#include "log.h"
#include "../gles/loader.h"
#include "../config/settings.h"
#include "mg.h"
#include "framebuffer.h"

#define DEBUG 0

static GLclampd currentDepthValue;

extern GLuint current_draw_fbo;
extern std::vector<framebuffer_t> framebuffers;

void glClearDepth(GLclampd depth) {
    LOG()
    currentDepthValue = depth;
    GLES.glClearDepthf((float)depth);
    CHECK_GL_ERROR
}

static GLuint g_depthClearProgram = 0;
static GLuint g_depthClearVAO = 0;
static GLuint g_depthClearVBO = 0;

static const GLfloat kFullScreenTri[3][2] = {
    { -1.0f, -1.0f },
    {  3.0f, -1.0f },
    { -1.0f,  3.0f }
};

static const char* kDepthClearVS = R"glsl(
    #version 300 es
    layout(location = 0) in vec2 aPos;
    void main() {
        // Write far‐plane depth
        gl_Position = vec4(aPos, 1.0, 1.0);
    }
)glsl";
static const char* kDepthClearFS = R"glsl(
    #version 300 es
    precision mediump float;
    out vec4 fragColor;
    void main() {
        // Empty—color writes will be disabled
        fragColor = vec4(0.0);
    }
)glsl";

void InitDepthClearCoreProfile() {
    if (g_depthClearProgram) return;

    auto compile = [&](GLenum type, const char* src) {
        GLuint s = GLES.glCreateShader(type);
        GLES.glShaderSource(s, 1, &src, nullptr);
        GLES.glCompileShader(s);
        return s;
        };
    GLuint vs = compile(GL_VERTEX_SHADER, kDepthClearVS);
    GLuint fs = compile(GL_FRAGMENT_SHADER, kDepthClearFS);

    g_depthClearProgram = GLES.glCreateProgram();
    GLES.glAttachShader(g_depthClearProgram, vs);
    GLES.glAttachShader(g_depthClearProgram, fs);
    GLES.glLinkProgram(g_depthClearProgram);
    GLES.glDeleteShader(vs);
    GLES.glDeleteShader(fs);

    GLES.glGenVertexArrays(1, &g_depthClearVAO);
    GLES.glGenBuffers(1, &g_depthClearVBO);

    GLES.glBindVertexArray(g_depthClearVAO);
    GLES.glBindBuffer(GL_ARRAY_BUFFER, g_depthClearVBO);
    GLES.glBufferData(GL_ARRAY_BUFFER, sizeof(kFullScreenTri), kFullScreenTri, GL_STATIC_DRAW);

    GLES.glEnableVertexAttribArray(0);
    GLES.glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLES.glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLES.glBindVertexArray(0);
}

void DrawDepthClearTri() {
    InitDepthClearCoreProfile();

    GLboolean prevColorMask[4];
    GLES.glGetBooleanv(GL_COLOR_WRITEMASK, prevColorMask);
    GLboolean prevDepthMask;
    GLES.glGetBooleanv(GL_DEPTH_WRITEMASK, &prevDepthMask);
    GLint prevDepthFunc;
    GLES.glGetIntegerv(GL_DEPTH_FUNC, &prevDepthFunc);

    GLES.glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    GLES.glDepthMask(GL_TRUE);
    GLES.glDepthFunc(GL_ALWAYS);
    
    GLES.glUseProgram(g_depthClearProgram);
    GLES.glBindVertexArray(g_depthClearVAO);
    GLES.glDrawArrays(GL_TRIANGLES, 0, 3);
    GLES.glBindVertexArray(0);
    GLES.glUseProgram(0);

    GLES.glDepthFunc(prevDepthFunc);
    GLES.glDepthMask(prevDepthMask);
    GLES.glColorMask(prevColorMask[0], prevColorMask[1], prevColorMask[2], prevColorMask[3]);
}

void glClear(GLbitfield mask) {
    LOG();
    LOG_D("glClear, mask = 0x%x", mask);

    INIT_CHECK_GL_ERROR

    GLES.glClear(mask);
    CHECK_GL_ERROR_NO_INIT

    if (global_settings.angle == AngleMode::Enabled &&
        mask == GL_DEPTH_BUFFER_BIT && 
        fabs(currentDepthValue - 1.0f) <= 0.001f
        && framebuffers[current_draw_fbo].color_attachments_all_none
        ) {
        LOG_D("doing depth workaround")
        if (global_settings.angle_depth_clear_fix_mode == AngleDepthClearFixMode::Mode1)
            // Workaround for ANGLE depth-clear bug: if depth≈1.0, draw a fullscreen triangle at z=1.0 to force actual depth buffer write.
            DrawDepthClearTri();
        else if (global_settings.angle_depth_clear_fix_mode == AngleDepthClearFixMode::Mode2) {
            // Or just explicitly clear depth buffer and see what's happened
            const GLfloat clear_depth_value = 1.0f;
            GLES.glClearBufferfv(GL_DEPTH, 0, &clear_depth_value);
        }
        // Clear again
    }

    CHECK_GL_ERROR_NO_INIT;
}

void glHint(GLenum target, GLenum mode) {
    LOG()
    LOG_D("glHint, target = %s, mode = %s", glEnumToString(target), glEnumToString(mode))
}

typedef struct FakeSync {
    int id;
} FakeSync;

static int g_fake_sync_counter = 1;

GLAPI GLAPIENTRY GLsync glFenceSync(GLenum condition, GLbitfield flags) {
    (void)condition;
    (void)flags;
    auto* sync = (FakeSync*)malloc(sizeof(FakeSync));
    if (!sync) return nullptr;
    sync->id = g_fake_sync_counter++;
    return (GLsync)sync;
}

GLAPI GLAPIENTRY GLboolean glIsSync(GLsync sync) {
    return (sync != nullptr) ? GL_TRUE : GL_FALSE;
}

GLAPI GLAPIENTRY void glDeleteSync(GLsync sync) {
    if (sync) {
        free(sync);
    }
}

GLAPI GLAPIENTRY GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    (void)sync;
    (void)flags;
    (void)timeout;
    return GL_ALREADY_SIGNALED;
}

GLAPI GLAPIENTRY void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    (void)sync;
    (void)flags;
    (void)timeout;
}

GLAPI GLAPIENTRY void glGetSynciv(GLsync sync, GLenum pname, GLsizei bufSize,
                 GLsizei* length, GLint* values) {
    if (!values) return;

    switch (pname) {
        case GL_OBJECT_TYPE:
            *values = GL_SYNC_FENCE;
            break;
        case GL_SYNC_STATUS:
            *values = GL_SIGNALED;
            break;
        case GL_SYNC_CONDITION:
            *values = GL_SYNC_GPU_COMMANDS_COMPLETE;
            break;
        case GL_SYNC_FLAGS:
            *values = 0;
            break;
        default:
            *values = 0;
            break;
    }
    if (length) *length = 1;
}