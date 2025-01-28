//
// Created by Swung0x48 on 2024/10/8.
//

#include "../includes.h"
#include "gl.h"
#include "glcorearb.h"
#include "log.h"
#include "loader.h"
#include "../gles/loader.h"
#include "mg.h"

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

GLAPI GLAPIENTRY void glClearDepth(GLclampd depth) {
	LOG();
	glClearDepthf(depth);
	glClear(GL_DEPTH_BUFFER_BIT);
}