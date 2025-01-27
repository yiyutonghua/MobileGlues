//
// Created by Swung 0x48 on 2024/10/10.
//

#ifndef FOLD_CRAFT_LAUNCHER_EGL_LOADER_H
#define FOLD_CRAFT_LAUNCHER_EGL_LOADER_H

#include "egl.h"

struct egl_func_t {
    EGLGETPROCADDRESSPROCP eglGetProcAddress;
    EGLCREATECONTEXTPROCP eglCreateContext;
    EGLDESTROYCONTEXTPROCP eglDestroyContext;
    EGLMAKECURRENTPROCP eglMakeCurrent;
    EGLQUERYSTRINGPROCP eglQueryString;
    EGLTERMINATEPROCP eglTerminate;
    EGLCHOOSECONFIGPROCP eglChooseConfig;
    EGLBINDAPIPROCP eglBindAPI;
    EGLINITIALIZEPROCP eglInitialize;
    EGLGETDISPLAYP eglGetDisplay;
    EGLCREATEPBUFFERSURFACEPROCP eglCreatePbufferSurface;
    EGLDESTROYSURFACEPROCP eglDestroySurface;
    EGLGETERRORPROCP eglGetError;
};


void init_target_egl();

EGLContext mglues_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list);
EGLBoolean mglues_eglDestroyContext(EGLDisplay dpy, EGLContext ctx);
EGLBoolean mglues_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);


#endif //FOLD_CRAFT_LAUNCHER_EGL_LOADER_H
