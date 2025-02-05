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
    GLenum target;
    struct attachment_t attachment[];
};

extern struct framebuffer_t* bound_framebuffer;

GLint getMaxDrawBuffers();

void rebind_framebuffer(GLenum old_attachment, GLenum target_attachment);

GLAPI GLAPIENTRY void glBindFramebuffer(GLenum target, GLuint framebuffer);

GLAPI GLAPIENTRY void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);

#endif //MOBILEGLUES_FRAMEBUFFER_H
