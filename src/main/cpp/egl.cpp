//
// Created by Swung 0x48 on 2024/10/8.
//

#ifdef __cplusplus
extern "C" {
#endif

#include "egl.h"
#include "includes.h"
#include <EGL/egl.h>

#ifdef __cplusplus
}
#endif

#include <unordered_map>

static std::unordered_map<EGLContext, context_t> g_context;

EGLContext mglues_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list) {
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "%s @ %s(...)", RENDERERNAME, __FUNCTION__);
    g_egl_func.eglCreateContext =
            (EGLCREATECONTEXTPROCP)g_egl_func.eglGetProcAddress("eglCreateContext");
    EGLContext ctx = g_egl_func.eglCreateContext(dpy, config, share_context, attrib_list);

    g_context[ctx] = { .context = ctx };

    return ctx;
}

EGLBoolean mglues_eglDestroyContext(EGLDisplay dpy, EGLContext ctx) {
    if (g_context.find(ctx) == g_context.end())
        return EGL_FALSE;

    EGLBoolean b = g_egl_func.eglDestroyContext(dpy, ctx);
    if (b)
        g_context.erase(ctx);
    return b;
}

EGLBoolean mglues_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx) {
    return g_egl_func.eglMakeCurrent(dpy, draw, read, ctx);
}



