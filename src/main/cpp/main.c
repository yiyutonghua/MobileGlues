//
// Created by Swung 0x48 on 2024/10/7.
//

#include <string.h>
#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif

void init_target_egl();
void init_target_gles();
__eglMustCastToProperFunctionPointerType prehook(const char *procname);
__eglMustCastToProperFunctionPointerType posthook(const char *procname);

void proc_init() {
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Initializing %s @ %s", RENDERERNAME, __FUNCTION__);

    void* handle = _mglues_dlopen("libEGL.so");
    if (handle == NULL)
        __android_log_print(ANDROID_LOG_FATAL, RENDERERNAME,
                            "Cannot load system libEGL.so!");

    g_target_egl_func.eglGetProcAddress = _mglues_dlsym(handle, "eglGetProcAddress");

    init_target_egl();
    init_target_gles();

    g_initialized = 1;
}

void init_target_egl() {
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Initializing %s @ %s", RENDERERNAME, __FUNCTION__);

    g_target_egl_func.eglCreateContext =
            (EGLCREATECONTEXTPROCP)g_target_egl_func.eglGetProcAddress("eglCreateContext");
    g_target_egl_func.eglDestroyContext =
            (EGLDESTROYCONTEXTPROCP) g_target_egl_func.eglGetProcAddress("eglDestroyContext");
    g_target_egl_func.eglMakeCurrent =
            (EGLMAKECURRENTPROCP) g_target_egl_func.eglGetProcAddress("eglMakeCurrent");

    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Got host eglCreateContext @ 0x%lx", g_target_egl_func.eglCreateContext);
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Got host eglDestroyContext @ 0x%lx", g_target_egl_func.eglDestroyContext);
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Got host eglMakeCurrent @ 0x%lx", g_target_egl_func.eglMakeCurrent);
}

void init_target_gles() {

}

__eglMustCastToProperFunctionPointerType prehook(const char *procname) {
    if (strcmp(procname, "glGetString") == 0)
        return (__eglMustCastToProperFunctionPointerType) glGetString;
    return NULL;
}

__eglMustCastToProperFunctionPointerType posthook(const char *procname) {
    return NULL;
}

EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY glXGetProcAddress (const char *procname) {
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "%s @ %s(%s)", RENDERERNAME, __FUNCTION__, procname);

    if (!g_initialized) {
        proc_init();
    }

    __eglMustCastToProperFunctionPointerType proc = NULL;

    proc = prehook(procname);
    if (proc) return proc;
    else
        __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                            "Unimplemented function: %s(%s) @ prehook", __FUNCTION__, procname);

    //proc = eglGetProcAddress(procname);
    if (proc) return proc;
    else
        __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                            "Unimplemented function: %s(%s) @ system", __FUNCTION__, procname);

    proc = posthook(procname);
    if (!proc)
        __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                            "Unimplemented function: %s(%s) @ posthook", __FUNCTION__, procname);
    return proc;
}

EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress (const char *procname) {
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "%s @ %s(%s)", RENDERERNAME, __FUNCTION__, procname);
}

GL_APICALL const GLubyte *GL_APIENTRY glGetString (GLenum name) {
    switch (name) {
        case GL_VENDOR: return "GL_VENDOR";
        case GL_RENDERER:
            return "GL_RENDERER";
        default:
            return "default";
    }
}

#ifdef __cplusplus
}
#endif
