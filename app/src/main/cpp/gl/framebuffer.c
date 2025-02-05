//
// Created by hanji on 2025/2/6.
//

#include "framebuffer.h"
#include "log.h"

#define DEBUG 0

struct framebuffer_t* bound_framebuffer;

GLint MAX_DRAW_BUFFERS = 0;

GLint getMaxDrawBuffers() {
    if (!MAX_DRAW_BUFFERS) {
        LOAD_GLES(glGetIntegerv, void, GLenum pname, GLint *params)
        gles_glGetIntegerv(GL_MAX_DRAW_BUFFERS, &MAX_DRAW_BUFFERS);
    }
    return MAX_DRAW_BUFFERS;
}

void rebind_framebuffer(GLenum old_attachment, GLenum target_attachment) {
    if (!bound_framebuffer || !bound_framebuffer->attachment)
        return;

    struct attachment_t attachment = bound_framebuffer->attachment[old_attachment - GL_COLOR_ATTACHMENT0];

    LOAD_GLES(glFramebufferTexture2D, void, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
    gles_glFramebufferTexture2D(bound_framebuffer->target, target_attachment, attachment.textarget, attachment.texture, attachment.level);
}

void glBindFramebuffer(GLenum target, GLuint framebuffer) {
    LOG()

    LOG_D("glBindFramebuffer(0x%x, %d)", target, framebuffer)

    LOAD_GLES(glBindFramebuffer, void, GLenum target, GLuint framebuffer)
    gles_glBindFramebuffer(target, framebuffer);

    if (!bound_framebuffer)
        bound_framebuffer = malloc(sizeof(struct framebuffer_t));
    free(bound_framebuffer->attachment);
    bound_framebuffer->attachment = malloc(getMaxDrawBuffers() * sizeof(struct attachment_t));
    bound_framebuffer->target = target;

    CHECK_GL_ERROR
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    LOG()

    LOG_D("glFramebufferTexture2D(0x%x, 0x%x, 0x%x, %d, %d)", target, attachment, textarget, texture, level)

    if (bound_framebuffer && bound_framebuffer->attachment) {
        bound_framebuffer->attachment[attachment - GL_COLOR_ATTACHMENT0].textarget = textarget;
        bound_framebuffer->attachment[attachment - GL_COLOR_ATTACHMENT0].texture = texture;
        bound_framebuffer->attachment[attachment - GL_COLOR_ATTACHMENT0].level = level;
    }

    LOAD_GLES(glFramebufferTexture2D, void, GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
    gles_glFramebufferTexture2D(target, attachment, textarget, texture, level);

    CHECK_GL_ERROR
}