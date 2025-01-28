//
// Created by BZLZHH on 2025/1/29.
//

#ifndef MOBILEGLUES_DRAWING_H
#define MOBILEGLUES_DRAWING_H

#include <stdbool.h>
#include "../gl/log.h"
#include "../gl/gl.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLES3/gl32.h>

GLAPI GLAPIENTRY void glMultiDrawElementsBaseVertex( GLenum mode, GLsizei *counts, GLenum type, const void * const *indices, GLsizei primcount, const GLint * basevertex);

#endif //MOBILEGLUES_DRAWING_H
