//
// Created by Swung 0x48 on 2024/10/7.
//

#ifndef MOBILEGLUES_INCLUDES_H
#define MOBILEGLUES_INCLUDES_H

#define RENDERERNAME "MobileGlues"
#include <android/log.h>
#include <dlfcn.h>

#include <EGL/egl.h>
#include <GLES3/gl32.h>

#define _mglues_dlopen(name) dlopen(name, RTLD_LAZY)
#define _mglues_dlclose(handle) dlclose(handle)
#define _mglues_dlsym(handle, name) dlsym(handle, name)

static int g_initialized = 0;

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

static struct egl_func_t g_target_egl_func;

#endif //MOBILEGLUES_INCLUDES_H
