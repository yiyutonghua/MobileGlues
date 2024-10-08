//
// Created by Swung 0x48 on 2024/10/8.
//

#ifndef FOLD_CRAFT_LAUNCHER_EGL_H
#define FOLD_CRAFT_LAUNCHER_EGL_H

#include <EGL/egl.h>

typedef __eglMustCastToProperFunctionPointerType (EGLGETPROCADDRESSPROC) (const char *procname);
typedef EGLGETPROCADDRESSPROC* EGLGETPROCADDRESSPROCP;
typedef EGLContext (EGLCREATECONTEXTPROC) (EGLDisplay, EGLConfig, EGLContext, const EGLint *);
typedef EGLCREATECONTEXTPROC* EGLCREATECONTEXTPROCP;
typedef EGLBoolean (EGLDESTROYCONTEXTPROC) (EGLDisplay, EGLContext);
typedef EGLDESTROYCONTEXTPROC* EGLDESTROYCONTEXTPROCP;
typedef EGLBoolean (EGLMAKECURRENTPROC)(EGLDisplay, EGLSurface, EGLSurface, EGLContext);
typedef EGLMAKECURRENTPROC* EGLMAKECURRENTPROCP;

struct egl_func_t {
    EGLGETPROCADDRESSPROCP eglGetProcAddress;
    EGLCREATECONTEXTPROCP eglCreateContext;
    EGLDESTROYCONTEXTPROCP eglDestroyContext;
    EGLMAKECURRENTPROCP eglMakeCurrent;
};

struct context_t {
    EGLContext context;
};

#endif //FOLD_CRAFT_LAUNCHER_EGL_H
