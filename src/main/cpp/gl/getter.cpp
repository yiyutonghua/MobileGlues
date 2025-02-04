//
// Created by BZLZHH on 2025/1/28.
//

#include "getter.h"
#include <string>

#define DEBUG 0

void glGetIntegerv(GLenum pname, GLint *params) {
    LOG();
    LOG_D("glGetIntegerv, pname: 0x%x",pname);
    if (pname == GL_CONTEXT_PROFILE_MASK) {
        (*params) = GL_CONTEXT_CORE_PROFILE_BIT;
        return;
    } 
    if (pname == GL_NUM_EXTENSIONS) {
        static GLint num_extensions = -1;
        if (num_extensions == -1) {
            const GLubyte* ext_str = glGetString(GL_EXTENSIONS);
            if (ext_str) {
                char* copy = strdup((const char*)ext_str);
                char* token = strtok(copy, " ");
                num_extensions = 0;
                while (token) {
                    num_extensions++;
                    token = strtok(NULL, " ");
                }
                free(copy);
            } else {
                num_extensions = 0;
            }
        }
        (*params) = num_extensions;
        return;
    }
    LOAD_GLES(glGetIntegerv, void, GLenum pname, GLint *params);
    gles_glGetIntegerv(pname, params);
    LOG_D("  -> %d",*params);
    CHECK_GL_ERROR
}

GLenum glGetError() {
    LOG();
    LOAD_GLES(glGetError, GLenum);
    return gles_glGetError();
}

static std::string es_ext;
const char* GetExtensionsList() {
    return es_ext.c_str();
}

void InitGLESBaseExtensions() {
    es_ext = "GL_ARB_fragment_program "
             "GL_ARB_vertex_buffer_object "
             "GL_ARB_vertex_array_object "
             "GL_ARB_vertex_buffer "
             "GL_EXT_vertex_array "
             "GL_ARB_ES2_compatibility "
             "GL_ARB_ES3_compatibility "
             "GL_EXT_packed_depth_stencil "
             "GL_EXT_depth_texture "
             "GL_ARB_depth_texture "
             "GL_ARB_shading_language_100 "
             "ARB_imaging "
             "GL_ARB_draw_buffers_blend "
             "OpenGL30 "
             "OpenGL31 "
             "OpenGL32 "
             "OpenGL33 "
             "OpenGL40 "
             //"OpenGL43 "
             //"ARB_compute_shader "
             "GL_ARB_get_program_binary ";
}

void AppendExtension(const char* ext) {
    es_ext += ext;
    es_ext += ' ';
}

const GLubyte * glGetString( GLenum name ) {
    LOG();
    LOAD_GLES(glGetString, const GLubyte *, GLenum);
    /* Feature in the Future
     * Advanced OpenGL driver: NV renderer.
    switch (name) {
        case GL_VENDOR:
            return (const GLubyte *) "NVIDIA Corporation";
        case GL_VERSION:
            return (const GLubyte *) "4.6.0 NVIDIA 572.16";
        case GL_RENDERER:
            return (const GLubyte *) "NVIDIA GeForce RTX 5090/PCIe/SSE2";
        case GL_SHADING_LANGUAGE_VERSION:
            return (const GLubyte *) "4.50 MobileGlues with glslang and SPIRV-Cross";
        case GL_EXTENSIONS:
            return (const GLubyte *) GetExtensionsList();
    }
    */
    switch (name) {
        case GL_VENDOR:
            return (const GLubyte *) "Swung0x48, BZLZHH, Tungsten";
        case GL_VERSION:
            return (const GLubyte *) "4.0.0 MobileGlues";
        case GL_RENDERER:
            return gles_glGetString(GL_RENDERER);
        case GL_SHADING_LANGUAGE_VERSION:
            return (const GLubyte *) "4.50 MobileGlues with glslang and SPIRV-Cross";
        case GL_EXTENSIONS:
            return (const GLubyte *) GetExtensionsList();
    }
     
    return gles_glGetString(name);
}

const GLubyte * glGetStringi(GLenum name, GLuint index) {
    LOG();
    LOAD_GLES(glGetStringi, const GLubyte *, GLenum, GLuint);
    typedef struct {
        GLenum name;
        const char** parts;
        GLuint count;
    } StringCache;
    static StringCache caches[] = {
            {GL_EXTENSIONS, NULL, 0},
            {GL_VENDOR, NULL, 0},
            {GL_VERSION, NULL, 0},
            {GL_SHADING_LANGUAGE_VERSION, NULL, 0}
    };
    static int initialized = 0;
    if (!initialized) {
        for (int i = 0; i < sizeof(caches)/sizeof(StringCache); i++) {
            GLenum target = caches[i].name;
            const GLubyte* str = NULL;
            const char* delimiter = " ";

            switch (target) {
                case GL_VENDOR:
                    str = (const GLubyte*)"Swung0x48, BZLZHH, Tungsten";
                    delimiter = ", ";
                    break;
                case GL_VERSION:
                    str = (const GLubyte*)"4.0.0 MobileGlues";
                    delimiter = " .";
                    break;
                case GL_SHADING_LANGUAGE_VERSION:
                    str = (const GLubyte*)"4.50 MobileGlues with glslang and SPIRV-Cross";
                    break;
                case GL_EXTENSIONS:
                    str = glGetString(GL_EXTENSIONS);
                    break;
            }

            if (!str) continue;

            char* copy = strdup((const char*)str);
            char* token = strtok(copy, delimiter);
            while (token) {
                caches[i].parts = (const char**)realloc(caches[i].parts, (caches[i].count + 1) * sizeof(char*));
                caches[i].parts[caches[i].count++] = strdup(token);
                token = strtok(NULL, delimiter);
            }
            free(copy);
        }
        initialized = 1;
    }

    for (int i = 0; i < sizeof(caches)/sizeof(StringCache); i++) {
        if (caches[i].name == name) {
            if (index >= caches[i].count) {
                return NULL;
            }
            return (const GLubyte*)caches[i].parts[index];
        }
    }

    return NULL;
}