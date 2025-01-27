//
// Created by Swung0x48 on 2024/10/10.
//

#include <EGL/egl.h>
#include <string.h>
#include "loader.h"
#include "../includes.h"
#include "../gl/log.h"
#include "../gl/envvars.h"

#define LOAD_CORE_FUNC(handle, name) \
    g_egl_func.name = _mglues_dlsym(handle, #name); \
    if (!g_egl_func.name) { \
        LOG_F("Failed to load core function: %s", #name); \
    }

void init_target_egl() {
    LOG_V("Initializing %s @ %s", RENDERERNAME, __FUNCTION__);
    char* egl_name = GetEnvVar("LIBGL_EGL") ? GetEnvVar("LIBGL_EGL") : "libEGL.so";
    void* handle = _mglues_dlopen(egl_name);
    if (!handle) LOG_F("Cannot load system %s!", egl_name);

    LOAD_CORE_FUNC(handle, eglGetProcAddress);
    LOAD_CORE_FUNC(handle, eglBindAPI);
    LOAD_CORE_FUNC(handle, eglInitialize);
    LOAD_CORE_FUNC(handle, eglGetDisplay);
    LOAD_CORE_FUNC(handle, eglCreatePbufferSurface);
    LOAD_CORE_FUNC(handle, eglDestroySurface);
    LOAD_CORE_FUNC(handle, eglDestroyContext);
    LOAD_CORE_FUNC(handle, eglMakeCurrent);
    LOAD_CORE_FUNC(handle, eglChooseConfig);
    LOAD_CORE_FUNC(handle, eglCreateContext);
    LOAD_CORE_FUNC(handle, eglQueryString);
    LOAD_CORE_FUNC(handle, eglTerminate);
    LOAD_CORE_FUNC(handle, eglGetError);

    EGLDisplay eglDisplay = EGL_NO_DISPLAY;
    EGLSurface eglSurface = EGL_NO_SURFACE;
    EGLContext eglContext = EGL_NO_CONTEXT;

    eglDisplay = g_egl_func.eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (eglDisplay == EGL_NO_DISPLAY) {
        LOG_E("eglGetDisplay failed (0x%x)", g_egl_func.eglGetError());
        goto cleanup;
    }

    if (g_egl_func.eglInitialize(eglDisplay, NULL, NULL) != EGL_TRUE) {
        LOG_E("eglInitialize failed (0x%x)", g_egl_func.eglGetError());
        goto cleanup;
    }

    if (g_egl_func.eglBindAPI(EGL_OPENGL_ES_API) != EGL_TRUE) {
        LOG_E("eglBindAPI failed (0x%x)", g_egl_func.eglGetError());
        goto cleanup;
    }

    EGLint configAttribs[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE
    };

    EGLConfig pbufConfig;
    EGLint configsFound = 0;
    if (g_egl_func.eglChooseConfig(eglDisplay, configAttribs, &pbufConfig, 1, &configsFound) != EGL_TRUE) {
        LOG_E("eglChooseConfig failed (0x%x)", g_egl_func.eglGetError());
        goto cleanup;
    }

    if (configsFound == 0) {
        configAttribs[6] = 0;
        if (g_egl_func.eglChooseConfig(eglDisplay, configAttribs, &pbufConfig, 1, &configsFound) != EGL_TRUE) {
            LOG_E("Retry eglChooseConfig failed (0x%x)", g_egl_func.eglGetError());
            goto cleanup;
        }
        if (configsFound) {
            LOG_I("Using config without alpha channel");
        } else {
            LOG_E("No valid EGL config found");
            goto cleanup;
        }
    }

    EGLint ctxAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    eglContext = g_egl_func.eglCreateContext(eglDisplay, pbufConfig, EGL_NO_CONTEXT, ctxAttribs);
    if (eglContext == EGL_NO_CONTEXT) {
        LOG_E("eglCreateContext failed (0x%x)", g_egl_func.eglGetError());
        goto cleanup;
    }

    EGLint pbAttribs[] = { EGL_WIDTH, 32, EGL_HEIGHT, 32, EGL_NONE };
    eglSurface = g_egl_func.eglCreatePbufferSurface(eglDisplay, pbufConfig, pbAttribs);
    if (eglSurface == EGL_NO_SURFACE) {
        LOG_E("eglCreatePbufferSurface failed (0x%x)", g_egl_func.eglGetError());
        goto cleanup;
    }

    if (g_egl_func.eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) != EGL_TRUE) {
        LOG_E("eglMakeCurrent failed (0x%x)", g_egl_func.eglGetError());
        goto cleanup;
    }

    LOG_V("EGL initialized successfully");
    return;

cleanup:
    if (eglSurface != EGL_NO_SURFACE) {
        g_egl_func.eglDestroySurface(eglDisplay, eglSurface);
    }
    if (eglContext != EGL_NO_CONTEXT) {
        g_egl_func.eglDestroyContext(eglDisplay, eglContext);
    }
    if (eglDisplay != EGL_NO_DISPLAY) {
        g_egl_func.eglTerminate(eglDisplay);
    }
    LOG_E("EGL initialization failed");
}