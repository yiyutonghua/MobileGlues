//
// Created by BZLZHH on 2025/1/29.
//

#include "drawing.h"
#include "buffer.h"

#define DEBUG 0

void glMultiDrawElementsBaseVertex( GLenum mode, GLsizei *counts, GLenum type, const void * const *indices, GLsizei primcount, const GLint * basevertex) {
    LOG();
    if (primcount <= 0 || !counts || !indices) return;
    for (int i = 0; i < primcount; i++) {
        if (counts[i] > 0)
            glDrawElementsBaseVertex(mode,
                    counts[i],
                    type,
                    indices[i],
                    basevertex[i]);
    }
}


void glMultiDrawElements(GLenum mode,const GLsizei * count,GLenum type,const void * const * indices,GLsizei primcount) {
    LOG();
    if (primcount <= 0 || !count || !indices) return;
    for (GLsizei i = 0; i < primcount; ++i) {
        if (count[i] > 0) {
            glDrawElements(
                    mode,
                    count[i],
                    type,
                    indices[i]
            );
        }
    }
}

void glDrawBuffer(GLenum buffer) {
    LOG()

    LOAD_GLES(glDrawBuffers, void, GLsizei n, const GLenum *bufs)

    GLint currentFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentFBO);

    if (currentFBO == 0) { // 默认帧缓冲
        GLenum buffers[1] = {GL_NONE};
        switch (buffer) {
            case GL_FRONT:
            case GL_BACK:
            case GL_NONE:
                buffers[0] = buffer;
                gles_glDrawBuffers(1, buffers);
                break;
            default:
                // 生成错误：GL_INVALID_ENUM
                break;
        }
    } else { // FBO场景
        GLint maxAttachments;
        glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttachments);

        if (buffer == GL_NONE) {
            GLenum *buffers = (GLenum *)alloca(maxAttachments * sizeof(GLenum));
            for (int i = 0; i < maxAttachments; i++) {
                buffers[i] = GL_NONE;
            }
            gles_glDrawBuffers(maxAttachments, buffers);
        } else if (buffer >= GL_COLOR_ATTACHMENT0 &&
                   buffer < GL_COLOR_ATTACHMENT0 + maxAttachments) {
            GLenum *buffers = (GLenum *)alloca(maxAttachments * sizeof(GLenum));
            for (int i = 0; i < maxAttachments; i++) {
                buffers[i] = (i == (buffer - GL_COLOR_ATTACHMENT0)) ? buffer : GL_NONE;
            }
            gles_glDrawBuffers(maxAttachments, buffers);
        } else {
            // 生成错误：GL_INVALID_ENUM
        }
    }
}

void glDrawBuffers(GLsizei n, const GLenum *bufs) {
    LOG()

    LOG_D("glDrawBuffers(%d, %p), [0]=0x%x", n, bufs, n ? bufs[0] : 0)
    LOAD_GLES(glDrawBuffers, void, GLsizei n, const GLenum *bufs)
    gles_glDrawBuffers(n, bufs);

    CHECK_GL_ERROR
}