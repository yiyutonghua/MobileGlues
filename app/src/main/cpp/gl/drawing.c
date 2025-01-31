//
// Created by BZLZHH on 2025/1/29.
//

#include "drawing.h"
#include "buffer.h"

#define DEBUG 0

void glMultiDrawElementsBaseVertex( GLenum mode, GLsizei *counts, GLenum type, const void * const *indices, GLsizei primcount, const GLint * basevertex) {
    LOG();

//    force_unmap();

    for (int i = 0; i < primcount; i++) {
        if (counts[i] > 0 && counts[i] < 50000)
            glDrawElementsBaseVertex(mode,
                    counts[i],
                    type,
                    indices[i],
                    basevertex[i]);
    }
}