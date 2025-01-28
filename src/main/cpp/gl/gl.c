#include "../includes.h"
#include "gl.h"
#include "glcorearb.h"
#include "log.h"
#include "loader.h"
#include "../gles/loader.h"
#include "mg.h"

/*
* Miscellaneous
*/

GLAPI GLAPIENTRY void glGetIntegerv(GLenum pname, GLint *params) {
    LOG();
    LOG_D("glGetIntegerv, pname: %d",pname);
    if (pname == GL_CONTEXT_PROFILE_MASK) {
        (*params) = GL_CONTEXT_COMPATIBILITY_PROFILE_BIT;
        return;
    }
    LOAD_GLES(glGetIntegerv, void, GLenum pname, GLint *params);
    gles_glGetIntegerv(pname, params);
    LOAD_GLES(glGetError, GLenum)
    GLenum ERR = gles_glGetError();
    if (ERR != GL_NO_ERROR)
        LOG_E("ERROR: %d", ERR)
}

GLAPI GLAPIENTRY GLenum glGetError() {
    LOG();
    LOAD_GLES(glGetError, GLenum);
    return gles_glGetError();
}

GLAPI GLAPIENTRY const GLubyte * glGetString( GLenum name ) {
    LOG();
    switch (name) {
        case GL_VENDOR:
            return (const GLubyte *)"Swung0x48, BZLZHH";
        case GL_RENDERER:
            return (const GLubyte *)"2.1 MobileGlues";
        case GL_VERSION:
            return (const GLubyte *)"2.1.0";
    }
    return (const GLubyte *)"NotSupported_GLenum";
}

/*
* Depth Buffer
*/

GLAPI GLAPIENTRY void glClearDepth(GLclampd depth) {
    LOG();
    glClearDepthf(depth);
    glClear(GL_DEPTH_BUFFER_BIT);
}

// OpenGL 3.1

GLAPI GLAPIENTRY GLenum glCheckFramebufferStatus(GLenum target) {
    LOG();
    LOAD_GLES(glCheckFramebufferStatus, GLenum, GLenum target);
    GLenum result = gles_glCheckFramebufferStatus(target);
    LOG_D("Result: %d", result);
    return result;
}

GLAPI GLAPIENTRY void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    LOG();
    LOG_D("glFramebufferTexture2D, target: %d, attachment: %d, textarget: %d, texture: %d, level: %d",target,attachment,textarget,texture,level);
    LOAD_GLES(glFramebufferTexture2D, void, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    gles_glFramebufferTexture2D(target,attachment,textarget,texture,level);
    LOAD_GLES(glGetError, GLenum)
    GLenum ERR = gles_glGetError();
    if (ERR != GL_NO_ERROR)
        LOG_E("ERROR: %d", ERR)
}


GLbitfield gl_to_es_access(GLenum access) {
    switch (access) {
        case GL_READ_ONLY:
            return GL_MAP_READ_BIT;
        case GL_WRITE_ONLY:
            return GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
        case GL_READ_WRITE:
            return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
        default:
            LOG_E("Invalid glMapBuffer access parameter!");
            return 0;
    }
}

GLAPI void *APIENTRY glMapBuffer (GLenum target, GLenum access) {
    LOAD_GLES(glGetBufferParameteriv,void, GLenum target, GLenum pname, GLint* params);
    LOAD_GLES(glMapBufferRange,void*, GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);

    GLint buffer_size = 0;
    gles_glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);

    GLbitfield flags = gl_to_es_access(GL_STATIC_DRAW);
    if (flags == 0) {
        flags = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
    }
    void* ptr = gles_glMapBufferRange(target, 0, buffer_size, flags);
    return ptr;
}
