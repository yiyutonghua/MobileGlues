//
// Created by BZLZHH on 2025/1/28.
//

#include "../includes.h"
#include "gl.h"
#include "glcorearb.h"
#include "log.h"
#include "loader.h"
#include "../gles/loader.h"
#include "mg.h"

#ifndef MOBILEGLUES_GETTER_H
#define MOBILEGLUES_GETTER_H

GLAPI GLAPIENTRY const GLubyte * glGetString( GLenum name );
GLAPI GLAPIENTRY GLenum glGetError();
GLAPI GLAPIENTRY void glGetIntegerv(GLenum pname, GLint *params);

#endif //MOBILEGLUES_GETTER_H
