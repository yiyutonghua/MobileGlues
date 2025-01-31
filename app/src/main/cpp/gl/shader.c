//
// Created by BZLZHH on 2025/1/26.
//

#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <android/log.h>
#include "shader.h"

#include "gl.h"
#include "log.h"
#include "../gles/loader.h"
#include "../includes.h"
#include "glsl/glsl_for_es.h"

#define DEBUG 0

void trim(char* str) {
    char* end;
    while (isspace((unsigned char)*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;
    *(end + 1) = 0;
}

int startsWith(const char *str, const char *prefix) {
    if (!str || !prefix) return 0;
    while (*prefix) {
        if (*str++ != *prefix++) return 0;
    }
    return 1;
}

char* process_uniform_declarations(char* glslCode) {
    char* cursor = glslCode;
    char name[256], type[256], initial_value[1024];
    int modifiedCodeIndex = 0;
    size_t maxLength = 1024 * 10;
    char* modifiedGlslCode = (char*)malloc(maxLength * sizeof(char));
    if (!modifiedGlslCode) return NULL;

    while (*cursor) {
        if (strncmp(cursor, "uniform", 7) == 0) {
            char* cursor_start = cursor;

            cursor += 7;

            while (isspace((unsigned char)*cursor)) cursor++;

            // may be precision qualifier
            char* precision = NULL;
            if (startsWith(cursor, "highp")) {
                precision = " highp";
                cursor += 5;
                while (isspace((unsigned char)*cursor)) cursor++;
            } else if (startsWith(cursor, "lowp")) {
                precision = " lowp";
                cursor += 4;
                while (isspace((unsigned char)*cursor)) cursor++;
            } else if (startsWith(cursor, "mediump")) {
                precision = " mediump";
                cursor += 7;
                while (isspace((unsigned char)*cursor)) cursor++;
            }

            int i = 0;
            while (isalnum((unsigned char)*cursor) || *cursor == '_') {
                type[i++] = *cursor++;
            }
            type[i] = '\0';

            while (isspace((unsigned char)*cursor)) cursor++;

            // may be precision qualifier
            if(!precision)
            {
                if (startsWith(cursor, "highp")) {
                    precision = " highp";
                    cursor += 5;
                    while (isspace((unsigned char)*cursor)) cursor++;
                } else if (startsWith(cursor, "lowp")) {
                    precision = " lowp";
                    cursor += 4;
                    while (isspace((unsigned char)*cursor)) cursor++;
                } else if (startsWith(cursor, "mediump")) {
                    precision = " mediump";
                    cursor += 7;
                    while (isspace((unsigned char)*cursor)) cursor++;
                } else {
                    precision = "";
                }
            }

            while (isspace((unsigned char)*cursor)) cursor++;

            i = 0;
            while (isalnum((unsigned char)*cursor) || *cursor == '_') {
                name[i++] = *cursor++;
            }
            name[i] = '\0';
            while (isspace((unsigned char)*cursor)) cursor++;

            initial_value[0] = '\0';
            if (*cursor == '=') {
                cursor++;
                i = 0;
                while (*cursor && *cursor != ';') {
                    initial_value[i++] = *cursor++;
                }
                initial_value[i] = '\0';
                trim(initial_value);
            }

            while (*cursor != ';' && *cursor) {
                cursor++;
            }

            char* cursor_end = cursor;

            int spaceLeft = maxLength - modifiedCodeIndex;
            int len = 0;

            if (*initial_value) {
                len = snprintf(modifiedGlslCode + modifiedCodeIndex, spaceLeft, "uniform%s %s %s;", precision, type, name);
            } else {
                // use original declaration
                size_t length = cursor_end - cursor_start + 1;
                if (length < spaceLeft) {
                    memcpy(modifiedGlslCode + modifiedCodeIndex, cursor_start, length);
                    len = (int)length;
                } else {
                    fprintf(stderr, "Error: Not enough space in buffer\n");
                }
                // len = snprintf(modifiedGlslCode + modifiedCodeIndex, spaceLeft, "uniform%s %s %s;", precision, type, name);
            }

            if (len < 0 || len >= spaceLeft) {
                free(modifiedGlslCode);
                return NULL;
            }
            modifiedCodeIndex += len;

            while (*cursor == ';') cursor++;

        } else {
            modifiedGlslCode[modifiedCodeIndex++] = *cursor++;
        }

        if (modifiedCodeIndex >= maxLength - 1) {
            maxLength *= 2;
            modifiedGlslCode = (char*)realloc(modifiedGlslCode, maxLength);
            if (!modifiedGlslCode) return NULL;
        }
    }

    modifiedGlslCode[modifiedCodeIndex] = '\0';
    return modifiedGlslCode;
}

bool can_run_essl3(int esversion, const char *glsl) {
    int glsl_version;

    if (strncmp(glsl, "#version 100", 12) == 0) {
        return true;
    } else if (strncmp(glsl, "#version 300 es", 15) == 0) {
        return true;
    } else if (strncmp(glsl, "#version 310 es", 15) == 0) {
        glsl_version = 310;
    } else if (strncmp(glsl, "#version 320 es", 15) == 0) {
        glsl_version = 320;
    } else {
        return false;
    }

    if (esversion >= glsl_version) {
        return true;
    } else {
        return false;
    }
}

bool is_direct_shader(char *glsl)
{
    bool es3_ability = can_run_essl3(320, glsl); //Assuming it is 320
    return es3_ability;
}

void glShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint *length) {    
    LOG();
    int l = 0;
    for (int i=0; i<count; i++) l+=(length && length[i] >= 0)?length[i]:strlen(string[i]);
    char* source = NULL;
    char* converted = NULL;
    source = malloc(l+1);
    memset(source, 0, l+1);
    if(length) {
        for (int i=0; i<count; i++) {
            if(length[i] >= 0)
                strncat(source, string[i], length[i]);
            else
                strcat(source, string[i]);
        }
    } else {
        for (int i=0; i<count; i++)
            strcat(source, string[i]);
    }
    LOAD_GLES2(glShaderSource, void, GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
    if (gles_glShaderSource) {
        if(is_direct_shader(source)){
            LOG_D("[INFO] [Shader] Direct shader source: ");
            LOG_D("%s", source);
            converted = strdup(source);
        } else {
            int glsl_version = getGLSLVersion(source);
            LOG_D("[INFO] [Shader] Shader source: ");
            LOG_D("%s", source);
            GLint shaderType;
            glGetShaderiv(shader, GL_SHADER_TYPE, &shaderType);
            converted = glsl_version<140?GLSLtoGLSLES_1(source, shaderType):GLSLtoGLSLES_2(source,shaderType,320);
            converted = process_uniform_declarations(converted);
            LOG_D("\n[INFO] [Shader] Converted Shader source: \n%s", converted);
        }
        if (converted)
            gles_glShaderSource(shader, count, (const GLchar * const*)&converted, NULL);
        else
            LOG_E("Failed to convert glsl.")
        CHECK_GL_ERROR
    } else {
        LOG_E("No gles_glShaderSource")
    }
}
    
