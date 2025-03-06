//
// Created by BZLZHH on 2025/1/29.
//

#include "drawing.h"
#include "buffer.h"
#include "framebuffer.h"

#define DEBUG 0

static bool g_indirect_cmds_inited = false;
//std::vector<draw_elements_indirect_command_t> g_commands;
static GLsizei g_cmdbufsize = 0;
GLuint g_indirectbuffer = 0;

void glMultiDrawElementsBaseVertex(GLenum mode, GLsizei* counts, GLenum type, const void* const* indices, GLsizei primcount, const GLint* basevertex) {
    LOG()

//    LOAD_GLES_FUNC(glDrawElementsBaseVertex)
//
//    for (GLsizei i = 0; i < primcount; ++i) {
//        const GLsizei count = counts[i];
//        if (count > 0) {
//            gles_glDrawElementsBaseVertex(mode, count, type, indices[i], basevertex[i]);
//        }
//    }

    if (!g_indirect_cmds_inited) {
        GLES.glGenBuffers(1, &g_indirectbuffer);
        GLES.glBindBuffer(GL_DRAW_INDIRECT_BUFFER, g_indirectbuffer);
        g_cmdbufsize = 1;
        GLES.glBufferData(GL_DRAW_INDIRECT_BUFFER,
                          g_cmdbufsize * sizeof(draw_elements_indirect_command_t), NULL, GL_DYNAMIC_DRAW);

        g_indirect_cmds_inited = true;
    }

    if (g_cmdbufsize < primcount) {
        size_t sz = g_cmdbufsize;

        LOG_D("Before resize: %d", sz)

        // 2-exponential to reduce reallocation
        while (sz < primcount)
            sz *= 2;

//        g_commands.resize(sz);
        GLES.glBufferData(GL_DRAW_INDIRECT_BUFFER,
                          sz * sizeof(draw_elements_indirect_command_t), NULL, GL_DYNAMIC_DRAW);
        g_cmdbufsize = sz;
    }

    LOG_D("After resize: %d", g_cmdbufsize)

    draw_elements_indirect_command_t* pcmds = (draw_elements_indirect_command_t*)
            GLES.glMapBufferRange(GL_DRAW_INDIRECT_BUFFER,
                                        0, primcount * sizeof(draw_elements_indirect_command_t),
                                        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

    for (GLsizei i = 0; i < primcount; ++i) {
        pcmds[i].count = counts[i];
        pcmds[i].instanceCount = 1;
        pcmds[i].firstIndex = static_cast<GLuint>(reinterpret_cast<uintptr_t>(indices[i]));
        pcmds[i].baseVertex = basevertex[i];
        pcmds[i].reservedMustBeZero = 0;
    }

//    void* pcmds = GLES.glMapBufferRange(GL_DRAW_INDIRECT_BUFFER,
//                                        0, primcount * sizeof(draw_elements_indirect_command_t),
//                                        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

//    memcpy(pcmds, g_commands.data(), primcount * sizeof(draw_elements_indirect_command_t));
    GLES.glUnmapBuffer(GL_DRAW_INDIRECT_BUFFER);

    // Draw indirect!
//    for (GLsizei i = 0; i < primcount; ++i) {
//        const GLvoid* offset = reinterpret_cast<GLvoid*>(i * sizeof(draw_elements_indirect_command_t));
//        GLES.glDrawElementsIndirect(mode, type, offset);
//    }


    // Multidraw indirect!
    GLES.glMultiDrawElementsIndirectEXT(mode, type, (void*)0, primcount, 0);

    CHECK_GL_ERROR
}

void glMultiDrawElements(GLenum mode, const GLsizei* count, GLenum type, const void* const* indices, GLsizei primcount) {
    LOG()

    LOAD_GLES_FUNC(glDrawElements)

    for (GLsizei i = 0; i < primcount; ++i) {
        const GLsizei c = count[i];
        if (c > 0) {
            gles_glDrawElements(mode, c, type, indices[i]);
        }
    }
}

//_Thread_local static bool unexpected_error = false; // solve the crash error for ANGLE

void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
    LOG_D("glDrawElements, mode: %d, count: %d, type: %d, indices: %p", mode, count, type, indices)
    LOAD_GLES_FUNC(glDrawElements)
    //LOAD_GLES_FUNC(glGetError)
    //GLenum pre_err = gles_glGetError();
    //if(pre_err != GL_NO_ERROR) {
    //    LOG_D("Skipping due to prior error: 0x%04X", pre_err)
    //    return;
    //}
    //if (!unexpected_error) {
    //    LOG_D("es_glDrawElements, mode: %d, count: %d, type: %d, indices: %p", mode, count, type, indices)
    gles_glDrawElements(mode, count, type, indices);
    CHECK_GL_ERROR
    //} else {
    //    unexpected_error = false;
    //}
}

void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) {
    LOG_D("glBindImageTexture, unit: %d, texture: %d, level: %d, layered: %d, layer: %d, access: %d, format: %d",
          unit, texture, level, layered, layer, access, format)
    LOAD_GLES_FUNC(glBindImageTexture)
    //LOAD_GLES_FUNC(glGetError)
    gles_glBindImageTexture(unit, texture, level, layered, layer, access, format);
    CHECK_GL_ERROR
    //GLenum err;
    //while((err = gles_glGetError()) != GL_NO_ERROR) {
    //    LOG_D("GL Error: 0x%04X", err)
    //    unexpected_error = true;
    //}
}

void glUniform1i(GLint location, GLint v0) {
    LOG_D("glUniform1i, location: %d, v0: %d", location, v0)
    LOAD_GLES_FUNC(glUniform1i)
    //LOAD_GLES_FUNC(glGetError)
    gles_glUniform1i(location, v0);
    CHECK_GL_ERROR
    //GLenum err;
    //while((err = gles_glGetError()) != GL_NO_ERROR) {
    //    LOG_D("GL Error: 0x%04X", err)
    //    unexpected_error = true;
    //}
}

void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) {
    LOG_D("glDispatchCompute, num_groups_x: %d, num_groups_y: %d, num_groups_z: %d",
          num_groups_x, num_groups_y, num_groups_z)
    LOAD_GLES_FUNC(glDispatchCompute)
    //LOAD_GLES_FUNC(glGetError)
    //GLenum pre_err = gles_glGetError();
    //if(pre_err != GL_NO_ERROR) {
    //    LOG_D("Skipping due to prior error: 0x%04X", pre_err)
    //    return;
    //}
    //if (!unexpected_error) {
    //    LOG_D("es_glDispatchCompute, num_groups_x: %d, num_groups_y: %d, num_groups_z: %d",
    //          num_groups_x, num_groups_y, num_groups_z)
    gles_glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    CHECK_GL_ERROR
    //} else {
    //    unexpected_error = false;
    //}
}