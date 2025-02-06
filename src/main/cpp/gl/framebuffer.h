//
// Created by hanji on 2025/2/6.
//

#ifndef MOBILEGLUES_FRAMEBUFFER_H
#define MOBILEGLUES_FRAMEBUFFER_H

#include "gl.h"

struct attachment_t {
    GLenum textarget;
    GLuint texture;
    GLint level;
};

struct framebuffer_t {
    GLenum current_target;
    struct attachment_t* draw_attachment;
    struct attachment_t* read_attachment;
};

GLint getMaxDrawBuffers();

void rebind_framebuffer(GLenum old_attachment, GLenum target_attachment);

GLAPI GLAPIENTRY void glBindFramebuffer(GLenum target, GLuint framebuffer);

GLAPI GLAPIENTRY void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);

GLAPI GLAPIENTRY void glDrawBuffer(GLenum buf);

GLAPI GLAPIENTRY void glDrawBuffers(GLsizei n, const GLenum *bufs);

#endif //MOBILEGLUES_FRAMEBUFFER_H
