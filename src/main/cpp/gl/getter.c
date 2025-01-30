//
// Created by BZLZHH on 2025/1/28.
//

#include "getter.h"

#define DEBUG 0

void glGetIntegerv(GLenum pname, GLint *params) {
    LOG();
    LOG_D("glGetIntegerv, pname: %d",pname);
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

char* GetExtensionsList() {
    char *extensions = (char*)malloc(20000);
    strcpy(extensions,
           "GL_EXT_abgr "
           "GL_EXT_packed_pixels "
           "GL_EXT_compiled_vertex_array "
           "GL_EXT_compiled_vertex_arrays "
           "GL_ARB_vertex_buffer_object "
           "GL_ARB_vertex_array_object "
           "GL_ARB_vertex_buffer "
           "GL_EXT_vertex_array "
           "GL_EXT_secondary_color "
           "GL_ARB_multitexture "
           "GL_ARB_texture_border_clamp "
           "GL_ARB_texture_env_add "
           "GL_EXT_texture_env_add "
           "GL_ARB_texture_env_combine "
           "GL_EXT_texture_env_combine "
           "GL_ARB_texture_env_crossbar "
           "GL_EXT_texture_env_crossbar "
           "GL_ARB_texture_env_dot3 "
           "GL_EXT_texture_env_dot3 "
           "GL_SGIS_generate_mipmap "
           "GL_EXT_draw_range_elements "
           "GL_EXT_bgra "
           "GL_ARB_texture_compression "
           "GL_EXT_texture_compression_s3tc "
           "GL_OES_texture_compression_S3TC "
           "GL_EXT_texture_compression_dxt1 "
           "GL_EXT_texture_compression_dxt3 "
           "GL_EXT_texture_compression_dxt5 "
           "GL_ARB_point_parameters "
           "GL_EXT_point_parameters "
           "GL_EXT_stencil_wrap "
           "GL_SGIS_texture_edge_clamp "
           "GL_EXT_texture_edge_clamp "
           "GL_EXT_direct_state_access "
           "GL_EXT_multi_draw_arrays "
           "GL_SUN_multi_draw_arrays "
           "GL_ARB_multisample "
           "GL_EXT_texture_object "
           "GL_EXT_polygon_offset "
           "GL_GL4ES_hint "
           "GL_ARB_draw_elements_base_vertex "
           "GL_EXT_draw_elements_base_vertex "
           "GL_ARB_map_buffer_range "
           "GL_NV_blend_square "
           "GL_EXT_polygon_offset_clamp "
           "GL_ARB_clear_texture "
           "GL_ARB_texture_mirror_clamp_to_edge "
           "GL_ARB_debug_output "
           "GL_ARB_enhanced_layouts "
           "GL_KHR_debug "
           "GL_ARB_arrays_of_arrays "
           "GL_ARB_texture_query_levels "
           "GL_ARB_invalidate_subdata "
           "GL_ARB_clear_buffer_object "
           "GL_INTEL_map_texture "
           "GL_ARB_texture_compression_bptc "
           "GL_ARB_ES2_compatibility "
           "GL_ARB_ES3_compatibility "
           "GL_ARB_robustness "
           "GL_ARB_robust_buffer_access_behavior "
           "GL_EXT_texture_sRGB_decode "
           "GL_ARB_copy_image "
           "GL_KHR_blend_equation_advanced "
           "GL_EXT_direct_state_access "
           "GL_ARB_stencil_texturing "
           "GL_ARB_texture_stencil8 "
           "GL_ARB_explicit_uniform_location "
           "GL_ARB_explicit_attrib_location "
           "GL_ARB_multi_bind "
           "GL_ARB_indirect_parameters "
           "GL_ARB_texture_rectangle "
           "GL_ARB_vertex_array_bgra "
           //"GL_APPLE_texture_2D_limited_npot "
           "GL_EXT_texture_filter_anisotropic "
           "GL_ARB_texture_mirrored_repeat "
           "GL_EXT_blend_equation_separate "
           "GL_EXT_blend_subtract "
           "GL_EXT_blend_func_separate "
           "GL_ARB_texture_non_power_of_two "
           "GL_EXT_blend_color "
           "GL_EXT_blend_minmax "
           "GL_ARB_framebuffer_object "
           "GL_EXT_framebuffer_object "
           "GL_EXT_packed_depth_stencil "
           "GL_EXT_framebuffer_blit "
           "GL_ARB_draw_buffers "
           "GL_EXT_draw_buffers2 "
           "GL_ARB_draw_buffers_blend "
           "GL_ARB_point_sprite "
           "GL_ARB_texture_cube_map "
           "GL_EXT_texture_cube_map "
           "GL_EXT_texture_rg "
           "GL_ARB_texture_rg "
           "GL_EXT_texture_float "
           "GL_ARB_texture_float "
           "GL_EXT_texture_half_float "
           "GL_EXT_color_buffer_float "
           "GL_EXT_color_buffer_half_float "
           "GL_EXT_depth_texture "
           "GL_ARB_depth_texture "
           "GL_EXT_fog_coord "
           "GL_EXT_separate_specular_color "
           "GL_EXT_rescale_normal "
           "GL_ARB_ES2_compatibility "
           "GL_ARB_ES3_compatibility "
           "GL_ARB_fragment_shader "
           "GL_ARB_vertex_shader "
           "GL_ARB_shader_objects "
           "GL_ARB_shading_language_100 "
           "GL_ATI_texture_env_combine3 "
           "GL_ATIX_texture_env_route "
           "GL_NV_texture_env_combine4 "
           "GL_NV_fog_distance "
           "GL_ARB_draw_instanced "
           "GL_ARB_instanced_arrays "
           "GL_ARB_vertex_program "
           "GL_ARB_fragment_program "
           "GL_EXT_program_parameters "
           "ARB_imaging "
           "GL_ARB_draw_buffers_blend "
           "OpenGL30 "
           "OpenGL31 "
           "OpenGL32 "
           "OpenGL33 "
           "OpenGL40 "
           "OpenGL40 "
           "GL_ARB_get_program_binary ");
    return extensions;
}

const GLubyte * glGetString( GLenum name ) {
    LOG();
    LOAD_GLES(glGetString, const GLubyte *, GLenum);
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