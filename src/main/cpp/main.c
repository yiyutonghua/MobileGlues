//
// Created by Swung 0x48 on 2024/10/7.
//

#include <string.h>
#include "includes.h"
#include <GL/gl.h>

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
                        "Got target eglCreateContext @ 0x%lx", g_target_egl_func.eglCreateContext);
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Got target eglDestroyContext @ 0x%lx", g_target_egl_func.eglDestroyContext);
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Got target eglMakeCurrent @ 0x%lx", g_target_egl_func.eglMakeCurrent);
}

void init_target_gles() {

}

#define UNIMPL_PH(name) if (strcmp(procname, #name) == 0)  \
    return (__eglMustCastToProperFunctionPointerType) name;

__eglMustCastToProperFunctionPointerType prehook(const char *procname) {
//    if (strcmp(procname, "glGetString") == 0)
//        return (__eglMustCastToProperFunctionPointerType) glGetString;
//    if (strcmp(procname, "glGetIntegerv") == 0)
//        return (__eglMustCastToProperFunctionPointerType) glGetIntegerv;
    UNIMPL_PH(glAccum);
    UNIMPL_PH(glAreTexturesResident);
    UNIMPL_PH(glAreTexturesResident);
    UNIMPL_PH(glArrayElement);
    UNIMPL_PH(glBegin);
    UNIMPL_PH(glBitmap);
    UNIMPL_PH(glCallList);
    UNIMPL_PH(glCallLists);
    UNIMPL_PH(glClearAccum);
    UNIMPL_PH(glClearIndex);
    UNIMPL_PH(glClipPlane);
    UNIMPL_PH(glColor3b);
    UNIMPL_PH(glColor3s);
    UNIMPL_PH(glColor3i);
    UNIMPL_PH(glColor3f);
    UNIMPL_PH(glColor3d);
    UNIMPL_PH(glColor3ub);
    UNIMPL_PH(glColor3us);
    UNIMPL_PH(glColor3ui);
    UNIMPL_PH(glColor3bv);
    UNIMPL_PH(glColor3sv);
    UNIMPL_PH(glColor3iv);
    UNIMPL_PH(glColor3fv);
    UNIMPL_PH(glColor3dv);
    UNIMPL_PH(glColor3ubv);
    UNIMPL_PH(glColor3usv);
    UNIMPL_PH(glColor3uiv);
    UNIMPL_PH(glColor4b);
    UNIMPL_PH(glColor4s);
    UNIMPL_PH(glColor4i);
    UNIMPL_PH(glColor4d);
    UNIMPL_PH(glColor4us);
    UNIMPL_PH(glColor4ui);
    UNIMPL_PH(glColor4bv);
    UNIMPL_PH(glColor4sv);
    UNIMPL_PH(glColor4iv);
    UNIMPL_PH(glColor4fv);
    UNIMPL_PH(glColor4dv);
    UNIMPL_PH(glColor4ubv);
    UNIMPL_PH(glColor4usv);
    UNIMPL_PH(glColor4uiv);
    UNIMPL_PH(glColorMaterial);
    UNIMPL_PH(glCopyPixels);
    UNIMPL_PH(glDeleteLists);
    UNIMPL_PH(glDrawPixels);
    UNIMPL_PH(glEdgeFlag);
    UNIMPL_PH(glEdgeFlagv);
    UNIMPL_PH(glEdgeFlagPointer);
    UNIMPL_PH(glEnd);
    UNIMPL_PH(glEvalCoord1f);
    UNIMPL_PH(glEvalCoord1fv);
    UNIMPL_PH(glEvalCoord1d);
    UNIMPL_PH(glEvalCoord1dv);
    UNIMPL_PH(glEvalCoord2f);
    UNIMPL_PH(glEvalCoord2fv);
    UNIMPL_PH(glEvalCoord2d);
    UNIMPL_PH(glEvalCoord2dv);
    UNIMPL_PH(glEvalMesh1);
    UNIMPL_PH(glEvalMesh2);
    UNIMPL_PH(glEvalPoint1);
    UNIMPL_PH(glEvalPoint2);
    UNIMPL_PH(glFeedbackBuffer);
    UNIMPL_PH(glFogi);
    UNIMPL_PH(glFogiv);
    UNIMPL_PH(glGenLists);
    UNIMPL_PH(glGetClipPlane);
    UNIMPL_PH(glGetLightiv);
    UNIMPL_PH(glGetMapiv);
    UNIMPL_PH(glGetMapfv);
    UNIMPL_PH(glGetMapdv);
    UNIMPL_PH(glGetMaterialiv);
    UNIMPL_PH(glGetPixelMapfv);
    UNIMPL_PH(glGetPixelMapusv);
    UNIMPL_PH(glGetPixelMapuiv);
    UNIMPL_PH(glGetPolygonStipple);
    UNIMPL_PH(glGetTexGeniv);
    UNIMPL_PH(glGetTexGenfv);
    UNIMPL_PH(glGetTexGendv);
    UNIMPL_PH(glIndexi);
    UNIMPL_PH(glIndexub);
    UNIMPL_PH(glIndexs);
    UNIMPL_PH(glIndexf);
    UNIMPL_PH(glIndexd);
    UNIMPL_PH(glIndexiv);
    UNIMPL_PH(glIndexubv);
    UNIMPL_PH(glIndexsv);
    UNIMPL_PH(glIndexfv);
    UNIMPL_PH(glIndexdv);
    UNIMPL_PH(glIndexMask);
    UNIMPL_PH(glIndexPointer);
    UNIMPL_PH(glInitNames);
    UNIMPL_PH(glInterleavedArrays);
    UNIMPL_PH(glIsList);
    UNIMPL_PH(glLightModeli);
    UNIMPL_PH(glLightModeliv);
    UNIMPL_PH(glLighti);
    UNIMPL_PH(glLightiv);
    UNIMPL_PH(glLineStipple);
    UNIMPL_PH(glListBase);
    UNIMPL_PH(glLoadMatrixd);
    UNIMPL_PH(glLoadName);
    UNIMPL_PH(glMap1f);
    UNIMPL_PH(glMap1d);
    UNIMPL_PH(glMap2f);
    UNIMPL_PH(glMap2d);
    UNIMPL_PH(glMapGrid1f);
    UNIMPL_PH(glMapGrid1d);
    UNIMPL_PH(glMapGrid2f);
    UNIMPL_PH(glMapGrid2d);
    UNIMPL_PH(glMateriali);
    UNIMPL_PH(glMaterialiv);
    UNIMPL_PH(glMultMatrixd);
    UNIMPL_PH(glFrustum);
    UNIMPL_PH(glNewList);
    UNIMPL_PH(glEndList);
    UNIMPL_PH(glNormal3b);
    UNIMPL_PH(glNormal3s);
    UNIMPL_PH(glNormal3i);
    UNIMPL_PH(glNormal3d);
    UNIMPL_PH(glNormal3fv);
    UNIMPL_PH(glNormal3bv);
    UNIMPL_PH(glNormal3sv);
    UNIMPL_PH(glNormal3iv);
    UNIMPL_PH(glNormal3dv);
    UNIMPL_PH(glOrtho);
    UNIMPL_PH(glPassThrough);
    UNIMPL_PH(glPixelMapfv);
    UNIMPL_PH(glPixelMapusv);
    UNIMPL_PH(glPixelMapuiv);
    UNIMPL_PH(glPixelTransferi);
    UNIMPL_PH(glPixelTransferf);
    UNIMPL_PH(glPixelZoom);
    UNIMPL_PH(glPolygonStipple);
    UNIMPL_PH(glPushAttrib);
    UNIMPL_PH(glPushClientAttrib);
    UNIMPL_PH(glPopAttrib);
    UNIMPL_PH(glPopClientAttrib);
    UNIMPL_PH(glPopName);
    UNIMPL_PH(glPrioritizeTextures);
    UNIMPL_PH(glPushName);
    UNIMPL_PH(glRasterPos2i);
    UNIMPL_PH(glRasterPos2s);
    UNIMPL_PH(glRasterPos2f);
    UNIMPL_PH(glRasterPos2d);
    UNIMPL_PH(glRasterPos2iv);
    UNIMPL_PH(glRasterPos2sv);
    UNIMPL_PH(glRasterPos2fv);
    UNIMPL_PH(glRasterPos2dv);
    UNIMPL_PH(glRasterPos3i);
    UNIMPL_PH(glRasterPos3s);
    UNIMPL_PH(glRasterPos3f);
    UNIMPL_PH(glRasterPos3d);
    UNIMPL_PH(glRasterPos3iv);
    UNIMPL_PH(glRasterPos3sv);
    UNIMPL_PH(glRasterPos3fv);
    UNIMPL_PH(glRasterPos3dv);
    UNIMPL_PH(glRasterPos4i);
    UNIMPL_PH(glRasterPos4s);
    UNIMPL_PH(glRasterPos4f);
    UNIMPL_PH(glRasterPos4d);
    UNIMPL_PH(glRasterPos4iv);
    UNIMPL_PH(glRasterPos4sv);
    UNIMPL_PH(glRasterPos4fv);
    UNIMPL_PH(glRasterPos4dv);
    UNIMPL_PH(glRecti);
    UNIMPL_PH(glRects);
    UNIMPL_PH(glRectf);
    UNIMPL_PH(glRectd);
    UNIMPL_PH(glRectiv);
    UNIMPL_PH(glRectsv);
    UNIMPL_PH(glRectfv);
    UNIMPL_PH(glRectdv);
    UNIMPL_PH(glRenderMode);
    UNIMPL_PH(glRotated);
    UNIMPL_PH(glScaled);
    UNIMPL_PH(glSelectBuffer);
    UNIMPL_PH(glTexCoord1f);
    UNIMPL_PH(glTexCoord1s);
    UNIMPL_PH(glTexCoord1i);
    UNIMPL_PH(glTexCoord1d);
    UNIMPL_PH(glTexCoord1fv);
    UNIMPL_PH(glTexCoord1sv);
    UNIMPL_PH(glTexCoord1iv);
    UNIMPL_PH(glTexCoord1dv);
    UNIMPL_PH(glTexCoord2f);
    UNIMPL_PH(glTexCoord2s);
    UNIMPL_PH(glTexCoord2i);
    UNIMPL_PH(glTexCoord2d);
    UNIMPL_PH(glTexCoord2fv);
    UNIMPL_PH(glTexCoord2sv);
    UNIMPL_PH(glTexCoord2iv);
    UNIMPL_PH(glTexCoord2dv);
    UNIMPL_PH(glTexCoord3f);
    UNIMPL_PH(glTexCoord3s);
    UNIMPL_PH(glTexCoord3i);
    UNIMPL_PH(glTexCoord3d);
    UNIMPL_PH(glTexCoord3fv);
    UNIMPL_PH(glTexCoord3sv);
    UNIMPL_PH(glTexCoord3iv);
    UNIMPL_PH(glTexCoord3dv);
    UNIMPL_PH(glTexCoord4f);
    UNIMPL_PH(glTexCoord4s);
    UNIMPL_PH(glTexCoord4i);
    UNIMPL_PH(glTexCoord4d);
    UNIMPL_PH(glTexCoord4fv);
    UNIMPL_PH(glTexCoord4sv);
    UNIMPL_PH(glTexCoord4iv);
    UNIMPL_PH(glTexCoord4dv);
    UNIMPL_PH(glTexGeni);
    UNIMPL_PH(glTexGeniv);
    UNIMPL_PH(glTexGenf);
    UNIMPL_PH(glTexGenfv);
    UNIMPL_PH(glTexGend);
    UNIMPL_PH(glTexGendv);
    UNIMPL_PH(glTranslated);
    UNIMPL_PH(glVertex2f);
    UNIMPL_PH(glVertex2s);
    UNIMPL_PH(glVertex2i);
    UNIMPL_PH(glVertex2d);
    UNIMPL_PH(glVertex2fv);
    UNIMPL_PH(glVertex2sv);
    UNIMPL_PH(glVertex2iv);
    UNIMPL_PH(glVertex2dv);
    UNIMPL_PH(glVertex3f);
    UNIMPL_PH(glVertex3s);
    UNIMPL_PH(glVertex3i);
    UNIMPL_PH(glVertex3d);
    UNIMPL_PH(glVertex3fv);
    UNIMPL_PH(glVertex3sv);
    UNIMPL_PH(glVertex3iv);
    UNIMPL_PH(glVertex3dv);
    UNIMPL_PH(glVertex4f);
    UNIMPL_PH(glVertex4s);
    UNIMPL_PH(glVertex4i);
    UNIMPL_PH(glVertex4d);
    UNIMPL_PH(glVertex4fv);
    UNIMPL_PH(glVertex4sv);
    UNIMPL_PH(glVertex4iv);
    UNIMPL_PH(glVertex4dv);
    UNIMPL_PH(glClearDepth);
    UNIMPL_PH(glDepthRange);
    UNIMPL_PH(glDrawBuffer);
    UNIMPL_PH(glGetDoublev);
    UNIMPL_PH(glGetTexImage);
    UNIMPL_PH(glPixelStoref);
    UNIMPL_PH(glPolygonMode);
    UNIMPL_PH(glTexImage1D);
    UNIMPL_PH(glCopyTexImage1D);
    UNIMPL_PH(glCopyTexSubImage1D);
    UNIMPL_PH(glTexSubImage1D);
//    UNIMPL_PH(glMultiTexCoord1f);
//    UNIMPL_PH(glMultiTexCoord1s);
//    UNIMPL_PH(glMultiTexCoord1i);
//    UNIMPL_PH(glMultiTexCoord1d);
//    UNIMPL_PH(glMultiTexCoord1fv);
//    UNIMPL_PH(glMultiTexCoord1sv);
//    UNIMPL_PH(glMultiTexCoord1iv);
//    UNIMPL_PH(glMultiTexCoord1dv);
//    UNIMPL_PH(glMultiTexCoord2f);
//    UNIMPL_PH(glMultiTexCoord2s);
//    UNIMPL_PH(glMultiTexCoord2i);
//    UNIMPL_PH(glMultiTexCoord2d);
//    UNIMPL_PH(glMultiTexCoord2fv);
//    UNIMPL_PH(glMultiTexCoord2sv);
//    UNIMPL_PH(glMultiTexCoord2iv);
//    UNIMPL_PH(glMultiTexCoord2dv);
//    UNIMPL_PH(glMultiTexCoord3f);
//    UNIMPL_PH(glMultiTexCoord3s);
//    UNIMPL_PH(glMultiTexCoord3i);
//    UNIMPL_PH(glMultiTexCoord3d);
//    UNIMPL_PH(glMultiTexCoord3fv);
//    UNIMPL_PH(glMultiTexCoord3sv);
//    UNIMPL_PH(glMultiTexCoord3iv);
//    UNIMPL_PH(glMultiTexCoord3dv);
//    UNIMPL_PH(glMultiTexCoord4s);
//    UNIMPL_PH(glMultiTexCoord4i);
//    UNIMPL_PH(glMultiTexCoord4d);
//    UNIMPL_PH(glMultiTexCoord4fv);
//    UNIMPL_PH(glMultiTexCoord4sv);
//    UNIMPL_PH(glMultiTexCoord4iv);
//    UNIMPL_PH(glMultiTexCoord4dv);
//    UNIMPL_PH(glLoadTransposeMatrixf);
//    UNIMPL_PH(glLoadTransposeMatrixd);
//    UNIMPL_PH(glMultTransposeMatrixf);
//    UNIMPL_PH(glMultTransposeMatrixd);
//    UNIMPL_PH(glCompressedTexImage1D);
//    UNIMPL_PH(glCompressedTexSubImage1D);
//    UNIMPL_PH(glGetCompressedTexImage);
//    UNIMPL_PH(glFogCoordd);
//    UNIMPL_PH(glFogCoordfv);
//    UNIMPL_PH(glFogCoorddv);
//    UNIMPL_PH(glFogCoordPointer);
//    UNIMPL_PH(glSecondaryColor3b);
//    UNIMPL_PH(glSecondaryColor3s);
//    UNIMPL_PH(glSecondaryColor3i);
//    UNIMPL_PH(glSecondaryColor3f);
//    UNIMPL_PH(glSecondaryColor3d);
//    UNIMPL_PH(glSecondaryColor3ub);
//    UNIMPL_PH(glSecondaryColor3us);
//    UNIMPL_PH(glSecondaryColor3ui);
//    UNIMPL_PH(glSecondaryColor3bv);
//    UNIMPL_PH(glSecondaryColor3sv);
//    UNIMPL_PH(glSecondaryColor3iv);
//    UNIMPL_PH(glSecondaryColor3fv);
//    UNIMPL_PH(glSecondaryColor3dv);
//    UNIMPL_PH(glSecondaryColor3ubv);
//    UNIMPL_PH(glSecondaryColor3usv);
//    UNIMPL_PH(glSecondaryColor3uiv);
//    UNIMPL_PH(glSecondaryColorPointer);
//    UNIMPL_PH(glWindowPos2i);
//    UNIMPL_PH(glWindowPos2s);
//    UNIMPL_PH(glWindowPos2f);
//    UNIMPL_PH(glWindowPos2d);
//    UNIMPL_PH(glWindowPos2iv);
//    UNIMPL_PH(glWindowPos2sv);
//    UNIMPL_PH(glWindowPos2fv);
//    UNIMPL_PH(glWindowPos2dv);
//    UNIMPL_PH(glWindowPos3i);
//    UNIMPL_PH(glWindowPos3s);
//    UNIMPL_PH(glWindowPos3f);
//    UNIMPL_PH(glWindowPos3d);
//    UNIMPL_PH(glWindowPos3iv);
//    UNIMPL_PH(glWindowPos3sv);
//    UNIMPL_PH(glWindowPos3fv);
//    UNIMPL_PH(glWindowPos3dv);
//    UNIMPL_PH(glMultiDrawArrays);
//    UNIMPL_PH(glMultiDrawElements);
//    UNIMPL_PH(glPointParameteri);
//    UNIMPL_PH(glPointParameteriv);
//    UNIMPL_PH(glGetBufferSubData);
//    UNIMPL_PH(glMapBuffer);
//    UNIMPL_PH(glGetQueryObjectiv);
//    UNIMPL_PH(glVertexAttrib1s);
//    UNIMPL_PH(glVertexAttrib1d);
//    UNIMPL_PH(glVertexAttrib2s);
//    UNIMPL_PH(glVertexAttrib2d);
//    UNIMPL_PH(glVertexAttrib3s);
//    UNIMPL_PH(glVertexAttrib3d);
//    UNIMPL_PH(glVertexAttrib4s);
//    UNIMPL_PH(glVertexAttrib4d);
//    UNIMPL_PH(glVertexAttrib4Nub);
//    UNIMPL_PH(glVertexAttrib1sv);
//    UNIMPL_PH(glVertexAttrib1dv);
//    UNIMPL_PH(glVertexAttrib2sv);
//    UNIMPL_PH(glVertexAttrib2dv);
//    UNIMPL_PH(glVertexAttrib3sv);
//    UNIMPL_PH(glVertexAttrib3dv);
//    UNIMPL_PH(glVertexAttrib4sv);
//    UNIMPL_PH(glVertexAttrib4dv);
//    UNIMPL_PH(glVertexAttrib4iv);
//    UNIMPL_PH(glVertexAttrib4bv);
//    UNIMPL_PH(glVertexAttrib4ubv);
//    UNIMPL_PH(glVertexAttrib4usv);
//    UNIMPL_PH(glVertexAttrib4uiv);
//    UNIMPL_PH(glVertexAttrib4Nbv);
//    UNIMPL_PH(glVertexAttrib4Nsv);
//    UNIMPL_PH(glVertexAttrib4Niv);
//    UNIMPL_PH(glVertexAttrib4Nubv);
//    UNIMPL_PH(glVertexAttrib4Nusv);
//    UNIMPL_PH(glVertexAttrib4Nuiv);
//    UNIMPL_PH(glGetVertexAttribdv);
//    UNIMPL_PH(glVertexAttribI1i);
//    UNIMPL_PH(glVertexAttribI2i);
//    UNIMPL_PH(glVertexAttribI3i);
//    UNIMPL_PH(glVertexAttribI1ui);
//    UNIMPL_PH(glVertexAttribI2ui);
//    UNIMPL_PH(glVertexAttribI3ui);
//    UNIMPL_PH(glVertexAttribI1iv);
//    UNIMPL_PH(glVertexAttribI2iv);
//    UNIMPL_PH(glVertexAttribI3iv);
//    UNIMPL_PH(glVertexAttribI1uiv);
//    UNIMPL_PH(glVertexAttribI2uiv);
//    UNIMPL_PH(glVertexAttribI3uiv);
//    UNIMPL_PH(glVertexAttribI4bv);
//    UNIMPL_PH(glVertexAttribI4sv);
//    UNIMPL_PH(glVertexAttribI4ubv);
//    UNIMPL_PH(glVertexAttribI4usv);
//    UNIMPL_PH(glBindFragDataLocation);
//    UNIMPL_PH(glBeginConditionalRender);
//    UNIMPL_PH(glEndConditionalRender);
//    UNIMPL_PH(glClampColor);
//    UNIMPL_PH(glFramebufferTexture1D);
//    UNIMPL_PH(glFramebufferTexture3D);
//    UNIMPL_PH(glPrimitiveRestartIndex);
//    UNIMPL_PH(glGetActiveUniformName);
//    UNIMPL_PH(glMultiDrawElementsBaseVertex);
//    UNIMPL_PH(glProvokingVertex);
//    UNIMPL_PH(glTexImage2DMultisample);
//    UNIMPL_PH(glTexImage3DMultisample);
//    UNIMPL_PH(glVertexP2ui);
//    UNIMPL_PH(glVertexP3ui);
//    UNIMPL_PH(glVertexP4ui);
//    UNIMPL_PH(glVertexP2uiv);
//    UNIMPL_PH(glVertexP3uiv);
//    UNIMPL_PH(glVertexP4uiv);
//    UNIMPL_PH(glTexCoordP1ui);
//    UNIMPL_PH(glTexCoordP2ui);
//    UNIMPL_PH(glTexCoordP3ui);
//    UNIMPL_PH(glTexCoordP4ui);
//    UNIMPL_PH(glTexCoordP1uiv);
//    UNIMPL_PH(glTexCoordP2uiv);
//    UNIMPL_PH(glTexCoordP3uiv);
//    UNIMPL_PH(glTexCoordP4uiv);
//    UNIMPL_PH(glMultiTexCoordP1ui);
//    UNIMPL_PH(glMultiTexCoordP2ui);
//    UNIMPL_PH(glMultiTexCoordP3ui);
//    UNIMPL_PH(glMultiTexCoordP4ui);
//    UNIMPL_PH(glMultiTexCoordP1uiv);
//    UNIMPL_PH(glMultiTexCoordP2uiv);
//    UNIMPL_PH(glMultiTexCoordP3uiv);
//    UNIMPL_PH(glMultiTexCoordP4uiv);
//    UNIMPL_PH(glNormalP3ui);
//    UNIMPL_PH(glNormalP3uiv);
//    UNIMPL_PH(glColorP3ui);
//    UNIMPL_PH(glColorP4ui);
//    UNIMPL_PH(glColorP3uiv);
//    UNIMPL_PH(glColorP4uiv);
//    UNIMPL_PH(glSecondaryColorP3ui);
//    UNIMPL_PH(glSecondaryColorP3uiv);
//    UNIMPL_PH(glBindFragDataLocationIndexed);
//    UNIMPL_PH(glGetFragDataIndex);
//    UNIMPL_PH(glQueryCounter);
//    UNIMPL_PH(glGetQueryObjecti64v);
//    UNIMPL_PH(glGetQueryObjectui64v);
//    UNIMPL_PH(glVertexAttribP1ui);
//    UNIMPL_PH(glVertexAttribP2ui);
//    UNIMPL_PH(glVertexAttribP3ui);
//    UNIMPL_PH(glVertexAttribP4ui);
//    UNIMPL_PH(glVertexAttribP1uiv);
//    UNIMPL_PH(glVertexAttribP2uiv);
//    UNIMPL_PH(glVertexAttribP3uiv);
//    UNIMPL_PH(glVertexAttribP4uiv);
//    UNIMPL_PH(glTexStorageMem1DEXT);

    return NULL;
}

__eglMustCastToProperFunctionPointerType posthook(const char *procname) {

    return NULL;
}

EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY glXGetProcAddress (const char *procname) {
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "%s @ %s(%s)", RENDERERNAME, __FUNCTION__, procname);
    __eglMustCastToProperFunctionPointerType proc = NULL;

    proc = prehook(procname);
    if (proc) return proc;
    else
        __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                            "bad func addr: %s(%s) @ prehook", __FUNCTION__, procname);

    proc = eglGetProcAddress(procname);
    if (proc) return proc;
    else
        __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                            "bad func addr: %s(%s) @ system", __FUNCTION__, procname);

    proc = posthook(procname);
    if (!proc)
        __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                            "bad func addr: %s(%s) @ posthook", __FUNCTION__, procname);
    return proc;
}

EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY eglGetProcAddress (const char *procname) {
    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "%s @ %s(%s)", RENDERERNAME, __FUNCTION__, procname);

    return g_target_egl_func.eglGetProcAddress(procname);
}

//static const unsigned char* vendor = "GL_VENDOR";
//static const unsigned char* renderer = "GL_RENDERER";
//static const unsigned char* defaultstring = "defaultstring";
//
//GL_APICALL const GLubyte *GL_APIENTRY glGetString (GLenum name) {
//    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
//                        "%s(0x%x, ...)", __FUNCTION__, name);
//    switch (name) {
//        case GL_VENDOR: return vendor;
//        case GL_RENDERER:
//            return renderer;
//        default:
//            return defaultstring;
//    }
//    return defaultstring;
//}

//GL_APICALL void glGetIntegerv( GLenum pname, GLint *params ) {
//    __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
//                        "%s(0x%x, ...)", __FUNCTION__, pname);
//
//}

#ifdef __cplusplus
}
#endif
