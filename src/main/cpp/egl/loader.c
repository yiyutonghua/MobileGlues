//
// Created by Swung0x48 on 2024/10/10.
//
#include "loader.h"
#include "../includes.h"

#define EGL_LOAD_FUNC(name) g_egl_func.name = (void*)g_egl_func.eglGetProcAddress(#name);

void init_target_egl() {
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Initializing %s @ %s", RENDERERNAME, __FUNCTION__);

//    g_egl_func.eglCreateContext = (EGLCREATECONTEXTPROCP)g_egl_func.eglGetProcAddress("eglCreateContext");
    EGL_LOAD_FUNC(eglCreateContext);
    EGL_LOAD_FUNC(eglDestroyContext);
    EGL_LOAD_FUNC(eglMakeCurrent);

    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Got target eglCreateContext @ 0x%lx", g_egl_func.eglCreateContext);
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Got target eglDestroyContext @ 0x%lx", g_egl_func.eglDestroyContext);
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Got target eglMakeCurrent @ 0x%lx", g_egl_func.eglMakeCurrent);
}