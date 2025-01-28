//
// Created by BZLZHH on 2025/1/29.
//

#include "drawing.h"

void glMultiDrawElementsBaseVertex( GLenum mode, GLsizei *counts, GLenum type, const void * const *indices, GLsizei primcount, const GLint * basevertex) {
    LOG();
    for (int i = 0; i < primcount; i++) {
    if (counts[i] > 0)
    glDrawElementsBaseVertex(mode,
            counts[i],
            type,
            indices[i],
            basevertex[i]);
    }
}