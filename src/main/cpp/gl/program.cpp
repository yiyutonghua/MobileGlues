//
// Created by hanji on 2025/2/3.
//

#include <regex.h>
#include "log.h"
#include "shader.h"
#include "program.h"
#include <regex>
#include <cstring>
#include <iostream>
#include "../config/settings.h"
#include <ankerl/unordered_dense.h>
#include "drawing.h"

#define DEBUG 0

extern UnorderedMap<GLuint, bool> shader_map_is_sampler_buffer_emulated;
UnorderedMap<GLuint, bool> program_map_is_sampler_buffer_emulated;

extern UnorderedMap<GLuint, bool> shader_map_is_atomic_counter_emulated;
UnorderedMap<GLuint, bool> program_map_is_atomic_counter_emulated;

char* updateLayoutLocation(const char* esslSource, GLuint color, const char* name) {
    std::string shaderCode(esslSource);

    std::string pattern = std::string(R"((layout\s*$[^)]*location\s*=\s*\d+[^)]*$\s*)?)")
                          + R"(out\s+((?:highp|mediump|lowp|\w+\s+)*\w+)\s+)"
                          + name + R"(\s*;)";

    std::string replacement = "layout (location = " + std::to_string(color)
                              + ") out $2 " + name + ";";

    std::regex reg(pattern);
    std::string modifiedCode = std::regex_replace(shaderCode, reg, replacement);

    char* result = new char[modifiedCode.size() + 1];
    strcpy(result, modifiedCode.c_str());
    return result;
}

void glBindFragDataLocation(GLuint program, GLuint color, const GLchar *name) {
    LOG()
    LOG_D("glBindFragDataLocation(%d, %d, %s)", program, color, name)

    if (strlen(name) > 8 && strncmp(name, "outColor", 8) == 0) {
        const char* numberStr = name + 8;
        bool isNumber = true;
        for (int i = 0; numberStr[i] != '\0'; ++i) {
            if (!isdigit(numberStr[i])) {
                isNumber = false;
                break;
            }
        }

        if (isNumber) {
            unsigned int extractedColor = static_cast<unsigned int>(std::stoul(numberStr));
            if (extractedColor == color) {
                // outColor was bound in glsl process. exit now
                LOG_D("Find outColor* with color *, skipping")
                return;
            }
        }
    }

    char* origin_glsl = nullptr;
    if (shaderInfo.frag_data_changed) {
        size_t glslLen  = strlen(shaderInfo.frag_data_changed_converted) + 1;
        origin_glsl = (char *)malloc(glslLen);
        if (origin_glsl == nullptr) {
            LOG_E("Memory reallocation failed for frag_data_changed_converted\n")
            return;
        }
        strcpy(origin_glsl, shaderInfo.frag_data_changed_converted);
    } else {
        size_t glslLen  = shaderInfo.converted.length() + 1;
        origin_glsl = (char *)malloc(glslLen);
        if (origin_glsl == nullptr) {
            LOG_E("Memory reallocation failed for converted\n")
            return;
        }
        strcpy(origin_glsl, shaderInfo.converted.c_str());
    }

    char* result_glsl = updateLayoutLocation(origin_glsl, color, name);
    free(origin_glsl);

    shaderInfo.frag_data_changed_converted = result_glsl;
    shaderInfo.frag_data_changed = 1;
}

void glLinkProgram(GLuint program) {
    LOG()

    LOG_D("glLinkProgram(%d)", program)
    if (!shaderInfo.converted.empty() && shaderInfo.frag_data_changed) {
        GLES.glShaderSource(shaderInfo.id, 1, (const GLchar * const*) &shaderInfo.frag_data_changed_converted, nullptr);
        GLES.glCompileShader(shaderInfo.id);
        GLint status = 0;
        GLES.glGetShaderiv(shaderInfo.id, GL_COMPILE_STATUS, &status);
        if(status!=GL_TRUE) {
            char tmp[500];
            GLES.glGetShaderInfoLog(shaderInfo.id, 500, nullptr, tmp);
            LOG_E("Failed to compile patched shader, log:\n%s", tmp)
        }
        GLES.glDetachShader(program, shaderInfo.id);
        GLES.glAttachShader(program, shaderInfo.id);
        CHECK_GL_ERROR
    }
    shaderInfo.id = 0;
    shaderInfo.converted = "";
    shaderInfo.frag_data_changed_converted = nullptr;
    shaderInfo.frag_data_changed = 0;
    GLES.glLinkProgram(program);

    CHECK_GL_ERROR
}

void glGetProgramiv(GLuint program, GLenum pname, GLint *params) {
    LOG()
    GLES.glGetProgramiv(program, pname, params);
    if(global_settings.ignore_error >= IgnoreErrorLevel::Partial && (pname == GL_LINK_STATUS || pname == GL_VALIDATE_STATUS) && !*params) {
        GLchar infoLog[512];
        GLES.glGetProgramInfoLog(program, 512, nullptr, infoLog);

        LOG_W_FORCE("Program %d linking failed: \n%s", program, infoLog);
        LOG_W_FORCE("Now try to cheat.");
        *params = GL_TRUE;
    }
    CHECK_GL_ERROR
}

void glUseProgram(GLuint program) {
    LOG()
    LOG_D("glUseProgram(%d)", program)
    if (program != gl_state->current_program) {
        gl_state->current_program = program;
        GLES.glUseProgram(program);
        CHECK_GL_ERROR
    }
}

void glAttachShader(GLuint program, GLuint shader) {
    LOG()
    LOG_D("glAttachShader(%u, %u)", program, shader)
    if (hardware->emulate_texture_buffer && shader_map_is_sampler_buffer_emulated[shader])
        program_map_is_sampler_buffer_emulated[program] = true;
    if (shader_map_is_atomic_counter_emulated[shader]) {
        program_map_is_atomic_counter_emulated[program] = true;
		LOG_D("Shader %d is atomic counter emulated, setting program %d to atomic counter emulated", shader, program)
    }

    GLES.glAttachShader(program, shader);
    CHECK_GL_ERROR
}

extern ankerl::unordered_dense::map<GLuint, SamplerInfo> g_samplerCacheForSamplerBuffer;

GLuint glCreateProgram() {
    LOG()
    LOG_D("glCreateProgram")
    GLuint program = GLES.glCreateProgram();
    if (hardware->emulate_texture_buffer) {
        program_map_is_sampler_buffer_emulated[program] = false;
        if (g_samplerCacheForSamplerBuffer.find(program) != g_samplerCacheForSamplerBuffer.end()) {
            g_samplerCacheForSamplerBuffer.erase(program);  
        }
    }
    CHECK_GL_ERROR
    return program;
}