//
// Created by BZLZHH on 2025/1/28.
//

#ifndef MOBILEGLUES_BUFFER_H

#include "../includes.h"
#include "gl.h"
#include "glcorearb.h"
#include "log.h"
#include "../gles/loader.h"
#include "mg.h"

#include <vector>

typedef struct {
    GLenum target;
    GLuint buffer_id;
    void *mapped_ptr;
#if GLOBAL_DEBUG || DEBUG
    void *client_ptr;
#endif
    GLsizeiptr size;
    GLbitfield flags;
    GLboolean is_dirty;
} BufferMapping;

#ifdef __cplusplus
extern "C" {
#endif

static GLenum get_binding_query(GLenum target);

GLAPI GLAPIENTRY void glGenBuffers(GLsizei n, GLuint *buffers);

GLAPI GLAPIENTRY void glDeleteBuffers(GLsizei n, const GLuint *buffers);

GLAPI GLAPIENTRY GLboolean glIsBuffer(GLuint buffer);

GLAPI GLAPIENTRY void glBindBuffer(GLenum target, GLuint buffer);

GLAPI GLAPIENTRY GLboolean glUnmapBuffer(GLenum target);

GLAPI GLAPIENTRY void *glMapBuffer(GLenum target, GLenum access);

GLAPI GLAPIENTRY void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage);

GLAPI GLAPIENTRY void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data);

GLAPI GLAPIENTRY void glBufferStorage(GLenum target, GLsizeiptr size, const void* data, GLbitfield flags);

#ifdef __cplusplus
}
#endif

#define MOBILEGLUES_BUFFER_H

#endif //MOBILEGLUES_BUFFER_H
