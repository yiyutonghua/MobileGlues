//
// Created by BZLZHH on 2025/1/27.
//

#include "texture.h"

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <android/log.h>

#include "gl.h"
#include "../gles/gles.h"
#include "log.h"
#include "../gles/loader.h"
#include "../includes.h"
#include "glsl/glsl_for_es.h"
#include "mg.h"

#define DEBUG 0

const GLenum GLUBYTE = GL_UNSIGNED_BYTE;

int nlevel(int size, int level) {
    if(size) {
        size>>=level;
        if(!size) size=1;
    }
    return size;
}

static bool support_rgba16 = false;
static bool checked_rgba16 = false;

bool check_rgba16() {
    LOAD_GLES(glGetStringi, const GLubyte *, GLenum, GLuint);
    LOAD_GLES(glGetIntegerv, void, GLenum pname, GLint *params);

    GLint numFormats = 0;
    gles_glGetIntegerv(GL_NUM_EXTENSIONS, &numFormats);

    for (int i = 0; i < numFormats; ++i) {
        const GLubyte* extension = gles_glGetStringi(GL_EXTENSIONS, i);
        if (strcmp((const char*)extension, "GL_EXT_texture_norm16") == 0) {
            return true;
        }
    }

    return false;
}

void internal_convert(GLenum* internal_format, GLenum* type) {
    switch (*internal_format) {
        case GL_DEPTH_COMPONENT:
            if (*type == GL_UNSIGNED_SHORT) {
                *internal_format = GL_DEPTH_COMPONENT16;
            } else if (*type == GL_UNSIGNED_INT) {
                *internal_format = GL_DEPTH_COMPONENT32;
            } else if (*type == GL_FLOAT) {
                *internal_format = GL_DEPTH_COMPONENT32F;
            } else if (*type == GL_DOUBLE) {
                *internal_format = GL_DEPTH_COMPONENT32F;
                *type = GL_FLOAT;
            }
            break;

        case GL_DEPTH_STENCIL:
            *internal_format = GL_DEPTH32F_STENCIL8;
            *type = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
            break;

        case GL_RGB10_A2:
            *type = GL_UNSIGNED_INT_2_10_10_10_REV;
            break;

        case GL_RGB5_A1:
            *type = GL_UNSIGNED_INT_2_10_10_10_REV;
            break;

        case GL_COMPRESSED_RED_RGTC1:
        case GL_COMPRESSED_RG_RGTC2:
            *type = 0;
            break;

        case GL_SRGB8:
            *type = GL_UNSIGNED_BYTE;
            break;

        case GL_RGBA32F:
        case GL_RGB32F:
        case GL_RG32F:
        case GL_R32F:
            *type = GL_FLOAT;
            break;

        case GL_R11F_G11F_B10F:
        case GL_RGB9_E5:
            *type = GL_FLOAT;
            break;

        case GL_RGBA32UI:
        case GL_RGB32UI:
        case GL_RG32UI:
        case GL_R32UI:
            *type = GL_UNSIGNED_INT;
            break;

        case GL_RGBA32I:
        case GL_RGB32I:
        case GL_RG32I:
        case GL_R32I:
            *type = GL_INT;
            break;

        case GL_RGBA16: {
            if (!checked_rgba16) {
                support_rgba16 = check_rgba16();
                checked_rgba16 = true;
            }
            if (support_rgba16) {
                *type = GL_UNSIGNED_SHORT;
            } else {
                *internal_format = GL_RGBA16F;
                *type = GL_FLOAT;
            }
            break;
        }
        case GL_RGBA8:
            *type = GL_UNSIGNED_BYTE;
            break;

        case GL_RGBA16F:
        case GL_R16F:
            *type = GL_FLOAT;
            break;

        default:
            if (*internal_format == GL_RGB8 && *type != GL_UNSIGNED_BYTE) {
                *type = GL_UNSIGNED_BYTE; 
            }
            else if (*internal_format == GL_RGBA16_SNORM && *type != GL_SHORT) {
                *type = GL_SHORT; 
            }
            break;
    }
}

void glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    LOG();
    pname = pname_convert(pname);
    if(pname == GL_TEXTURE_LOD_BIAS)
        return;
    LOG_D("glTexParameterf, target: %d, pname: %d, param: %f",target, pname, param);
    LOAD_GLES(glTexParameterf, void, GLenum target, GLenum pname, GLfloat param);
    gles_glTexParameterf(target,pname, param);
    CHECK_GL_ERROR
}

void glTexImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels) {
    LOG();
    LOG_D("glTexImage1D not implemeted!");
    LOG_D("glTexImage1D, target: %d, level: %d, internalFormat: %d, width: %d, border: %d, format: %d, type: %d",
          target, level, internalFormat, width, border, format, type);
    return;
    internal_convert(&internalFormat,& type);

    GLenum rtarget = map_tex_target(target);
    if (rtarget == GL_PROXY_TEXTURE_1D) {
        int max1 = 4096;
        LOAD_GLES(glGetIntegerv, void, GLenum pname, GLint * data)
        gles_glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max1);
        set_gl_state_proxy_width(((width << level) > max1) ? 0 : width);
        set_gl_state_proxy_intformat(internalFormat);
        return;
    }

//    LOAD_GLES(glTexImage1D, void, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
//    gles_glTexImage1D(target, level, internalFormat, width, border, format, type, pixels);

    CHECK_GL_ERROR
}

void glTexImage2D(GLenum target, GLint level,GLint internalFormat,GLsizei width, GLsizei height,GLint border, GLenum format, GLenum type,const GLvoid* pixels) {
    LOG();
    internal_convert(&internalFormat,& type);
    LOG_D("glTexImage2D,target: 0x%x,level: %d,internalFormat: 0x%x->0x%x,width: %d,height: %d,border: %d,format: 0x%x,type: 0x%x",target,level,internalFormat,internalFormat,width,height,border,format,type);
    GLenum rtarget = map_tex_target(target);
    if(rtarget == GL_PROXY_TEXTURE_2D) {
        int max1 = 4096;
        LOAD_GLES(glGetIntegerv, void, GLenum pname, GLint * data)
        gles_glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max1);
        set_gl_state_proxy_width(((width<<level)>max1)?0:width);
        set_gl_state_proxy_height(((height<<level)>max1)?0:height);
        set_gl_state_proxy_intformat(internalFormat);
        return;
    }
    LOAD_GLES(glTexImage2D, void, GLenum target, GLint level,GLint internalFormat,GLsizei width, GLsizei height,GLint border, GLenum format, GLenum type,const GLvoid* pixels);
    gles_glTexImage2D(target,level,internalFormat,width,height,border,format,type,pixels);
    CHECK_GL_ERROR
}

void glTexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels) {
    LOG();
    LOG_D("glTexImage3D, target: %d, level: %d, internalFormat: %d, width: %d, height: %d, depth: %d, border: %d, format: %d, type: %d",
          target, level, internalFormat, width, height, depth, border, format, type);

    internal_convert(&internalFormat, &type);

    GLenum rtarget = map_tex_target(target);
    if (rtarget == GL_PROXY_TEXTURE_3D) {
        int max1 = 4096;
        LOAD_GLES(glGetIntegerv, void, GLenum pname, GLint * data)
        gles_glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max1);
        set_gl_state_proxy_width(((width << level) > max1) ? 0 : width);
        set_gl_state_proxy_height(((height << level) > max1) ? 0 : height);
        //set_gl_state_proxy_depth(((depth << level) > max1) ? 0 : depth);
        set_gl_state_proxy_intformat(internalFormat);
        return;
    }

    LOAD_GLES(glTexImage3D, void, GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
    gles_glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, pixels);

    CHECK_GL_ERROR
}

void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width) {
    LOG();
    LOG_D("glTexStorage1D not implemented!")
    LOG_D("glTexStorage1D, target: %d, levels: %d, internalFormat: %d, width: %d",
          target, levels, internalFormat, width);
    return;
    internal_convert(&internalFormat,&GLUBYTE);

//    LOAD_GLES(glTexStorage1D, void, GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width);
//    gles_glTexStorage1D(target, levels, internalFormat, width);

    CHECK_GL_ERROR
}

void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height) {
    LOG();
    LOG_D("glTexStorage2D, target: %d, levels: %d, internalFormat: %d, width: %d, height: %d",
          target, levels, internalFormat, width, height);

    internal_convert(&internalFormat,&GLUBYTE);

    LOAD_GLES(glTexStorage2D, void, GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height);
    gles_glTexStorage2D(target, levels, internalFormat, width, height);

    LOAD_GLES(glGetError, GLenum);
    GLenum ERR = gles_glGetError();
    if (ERR != GL_NO_ERROR)
        LOG_E("glTexStorage2D ERROR: %d", ERR);
}

void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth) {
    LOG();
    LOG_D("glTexStorage3D, target: %d, levels: %d, internalFormat: %d, width: %d, height: %d, depth: %d",
          target, levels, internalFormat, width, height, depth);

    internal_convert(&internalFormat,&GLUBYTE);

    LOAD_GLES(glTexStorage3D, void, GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth);
    gles_glTexStorage3D(target, levels, internalFormat, width, height, depth);

    CHECK_GL_ERROR
}

void glCopyTexImage1D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border) {
    LOG();
    LOG_D("glCopyTexImage1D not implemented!");
    LOG_D("glCopyTexImage1D, target: %d, level: %d, internalFormat: %d, x: %d, y: %d, width: %d, border: %d",
          target, level, internalFormat, x, y, width, border);
    return;
    internal_convert(&internalFormat,&GLUBYTE);

//    LOAD_GLES(glCopyTexImage1D, void, GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
//    gles_glCopyTexImage1D(target, level, internalFormat, x, y, width, border);

    CHECK_GL_ERROR
}

void glCopyTexImage2D(GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    LOG();
    LOG_D("glCopyTexImage2D, target: %d, level: %d, internalFormat: %d, x: %d, y: %d, width: %d, height: %d, border: %d",
          target, level, internalFormat, x, y, width, height, border);

    internal_convert(&internalFormat,&GLUBYTE);

    LOAD_GLES(glCopyTexImage2D, void, GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
    gles_glCopyTexImage2D(target, level, internalFormat, x, y, width, height, border);

    CHECK_GL_ERROR
}

void glRenderbufferStorage(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height) {
    LOG();
    LOG_D("glRenderbufferStorage, target: %d, internalFormat: %d, width: %d, height: %d",
          target, internalFormat, width, height);

    internal_convert(&internalFormat,&GLUBYTE);

    LOAD_GLES(glRenderbufferStorage, void, GLenum target, GLenum internalFormat, GLsizei width, GLsizei height);
    gles_glRenderbufferStorage(target, internalFormat, width, height);

    CHECK_GL_ERROR
}

void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height) {
    LOG();
    LOG_D("glRenderbufferStorageMultisample, target: %d, samples: %d, internalFormat: %d, width: %d, height: %d",
          target, samples, internalFormat, width, height);

    internal_convert(&internalFormat,&GLUBYTE);

    LOAD_GLES(glRenderbufferStorageMultisample, void, GLenum target, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height);
    gles_glRenderbufferStorageMultisample(target, samples, internalFormat, width, height);

    CHECK_GL_ERROR
}

void glGetTexLevelParameterfv(GLenum target, GLint level,GLenum pname, GLfloat *params) {
    LOG();
    LOG_D("glGetTexLevelParameterfv,target: %d, level: %d, pname: %d",target,level,pname);
    GLenum rtarget = map_tex_target(target);
    if (rtarget==GL_PROXY_TEXTURE_2D) {
        switch (pname) {
            case GL_TEXTURE_WIDTH:
                (*params) = nlevel(gl_state->proxy_width, level);
                break;
            case GL_TEXTURE_HEIGHT:
                (*params) = nlevel(gl_state->proxy_height, level);
                break;
            case GL_TEXTURE_INTERNAL_FORMAT:
                (*params) = gl_state->proxy_intformat;
                break;
        }
        return;
    }
    LOAD_GLES(glGetTexLevelParameterfv, void, GLenum target, GLint level,GLenum pname, GLfloat *params);
    gles_glGetTexLevelParameterfv(target,level,pname,params);
    CHECK_GL_ERROR
}

void glGetTexLevelParameteriv(GLenum target, GLint level,GLenum pname, GLint *params) {
    LOG();
    LOG_D("glGetTexLevelParameteriv,target: %d, level: %d, pname: %d",target,level,pname);
    GLenum rtarget = map_tex_target(target);
    if (rtarget==GL_PROXY_TEXTURE_2D) {
        switch (pname) {
            case GL_TEXTURE_WIDTH:
                (*params) = nlevel(gl_state->proxy_width, level);
                break;
            case GL_TEXTURE_HEIGHT:
                (*params) = nlevel(gl_state->proxy_height, level);
                break;
            case GL_TEXTURE_INTERNAL_FORMAT:
                (*params) = gl_state->proxy_intformat;
                break;
        }
        return;
    }
    LOAD_GLES(glGetTexLevelParameteriv, void, GLenum target, GLint level,GLenum pname, GLint *params);
    GLint *fparams = NULL;
    gles_glGetTexLevelParameteriv(target,level,pname,params);
    CHECK_GL_ERROR
}