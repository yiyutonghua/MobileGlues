//
// Created by BZLZHH on 2025/1/28.
//

#include "buffer.h"
#include <unordered_map>

#define DEBUG 0

std::unordered_map<GLuint, GLuint> g_gen_buffers;
std::unordered_map<GLenum, GLuint> g_binded_buffers;

std::unordered_map<GLuint, BufferMapping> g_active_mappings;

static GLuint gen_buffer() {
    GLuint max_key = 0;
    if (!g_gen_buffers.empty()) {
        for (const auto& pair : g_gen_buffers) {
            if (pair.first > max_key)
                max_key = pair.first;
        }
    }
    GLuint key = max_key + 1;
    g_gen_buffers[key] = 0;
    return key;
}

static GLboolean has_buffer(GLuint key) {
    auto it = g_gen_buffers.find(key);
    return it != g_gen_buffers.end();
}

static void modify_buffer(GLuint key, GLuint value) {
    g_gen_buffers[key] = value;
}

static void remove_buffer(GLuint key) {
    if (g_gen_buffers.find(key) != g_gen_buffers.end())
        g_gen_buffers.erase(key);
}

static GLuint find_real_buffer(GLuint key) {
    auto it = g_gen_buffers.find(key);
    if (it != g_gen_buffers.end())
        return it->second;
    else
        return 0;
}

static void bind_buffer(GLenum target, GLuint buffer) {
    g_binded_buffers[target] = buffer;
}

static GLuint find_buffer(GLenum target) {
    auto it = g_binded_buffers.find(target);
    if (it != g_binded_buffers.end())
        return it->second;
    else
        return 0;
}

static GLenum find_buffer_target(GLuint buffer) {
    GLenum target;
    if (!g_binded_buffers.empty()) {
        for (const auto& pair : g_binded_buffers) {
            if (pair.second == buffer)
                target = pair.first;
        }
    }
    return target;
}

static void real_bind_buffer(GLenum target, GLuint buffer) {
    LOG()
    LOG_D("real_bind_buffer, target = %s, buffer = %d", glEnumToString(target), buffer)
    GLES.glBindBuffer(target, buffer);
    CHECK_GL_ERROR
}

static GLenum get_binding_query(GLenum target) {
    switch(target) {
        case GL_ARRAY_BUFFER:          return GL_ARRAY_BUFFER_BINDING;
        case GL_ELEMENT_ARRAY_BUFFER:  return GL_ELEMENT_ARRAY_BUFFER_BINDING;
        case GL_PIXEL_PACK_BUFFER:     return GL_PIXEL_PACK_BUFFER_BINDING;
        case GL_PIXEL_UNPACK_BUFFER:   return GL_PIXEL_UNPACK_BUFFER_BINDING;
        default:                       return 0;
    }
}

void glGenBuffers(GLsizei n, GLuint *buffers) {
    LOG()
    LOG_D("glGenBuffers(%i, %p)", n, buffers)
    for (int i = 0; i < n; ++i) {
        buffers[i] = gen_buffer();
    }
}

void glDeleteBuffers(GLsizei n, const GLuint *buffers) {
    LOG()
    LOG_D("glDeleteBuffers(%i, %p)", n, buffers)
    for (int i = 0; i < n; ++i) {
        if (find_real_buffer(buffers[i])) {
            GLuint real_buff = find_real_buffer(buffers[i]);
            GLES.glDeleteBuffers(1, &real_buff);
            CHECK_GL_ERROR
        }
        remove_buffer(buffers[i]);
    }
}

GLboolean glIsBuffer(GLuint buffer) {
    return has_buffer(buffer);
}

void glBindBuffer(GLenum target, GLuint buffer) {
    LOG()
    LOG_D("glBindBuffer, target = %s, buffer = %d", glEnumToString(target), buffer)
    bind_buffer(target, buffer);
    if (find_real_buffer(buffer)) {
        GLES.glBindBuffer(target, find_real_buffer(buffer));
        CHECK_GL_ERROR
    }
}

void glBufferData(GLenum target, GLsizeiptr size, const void *data, GLenum usage) {
    LOG()
    LOG_D("glBufferData, target = %s, size = %d, data = 0x%x, usage = %s",
          glEnumToString(target), size, data, glEnumToString(usage))
    GLuint real_buff = find_real_buffer(find_buffer(target));
    if (!real_buff) {
        GLES.glGenBuffers(1, &real_buff);
        modify_buffer(find_buffer(target), real_buff);
        CHECK_GL_ERROR
    }
    if (real_buff) {
        real_bind_buffer(target, real_buff);
        GLES.glBufferData(target, size, data, usage);
        CHECK_GL_ERROR
    } else {
        LOG_E("real buffer is null!")
    }
}

void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void *data) {
    LOG()
    LOG_D("glBufferSubData, target = %s, offset = %p, size = %d, data = 0x%x",
          glEnumToString(target), (void*) offset, size, data)
    GLuint real_buff = find_real_buffer(find_buffer(target));
    if (real_buff) {
        real_bind_buffer(target, real_buff);
        GLES.glBufferSubData(target, offset, size, data);
        CHECK_GL_ERROR
    } else {
        LOG_E("real buffer is null!")
    }
}

void* glMapBuffer(GLenum target, GLenum access) {
    LOG()
    LOG_D("glMapBuffer, target = %s, access = %s", glEnumToString(target), glEnumToString(access))
    if(g_gles_caps.GL_OES_mapbuffer) {
        return GLES.glMapBufferOES(target, access);
    }
    if (get_binding_query(target) == 0) {
        return nullptr;
    }
    GLint current_buffer;
    GLES.glGetIntegerv(get_binding_query(target), &current_buffer);
    if (current_buffer == 0) {
        return nullptr;
    }
    if (g_active_mappings[current_buffer].mapped_ptr != nullptr) {
        return nullptr;
    }
    GLint buffer_size;
    GLES.glGetBufferParameteriv(target, GL_BUFFER_SIZE, &buffer_size);
    if (buffer_size <= 0 || glGetError() != GL_NO_ERROR) {
        return nullptr;
    }
    GLbitfield flags = 0;
    switch (access) {
        case GL_READ_ONLY:  flags = GL_MAP_READ_BIT; break;
        case GL_WRITE_ONLY: flags = GL_MAP_WRITE_BIT /*| GL_MAP_INVALIDATE_BUFFER_BIT*/; break;
        case GL_READ_WRITE: flags = GL_MAP_READ_BIT | GL_MAP_WRITE_BIT; break;
        default:
            return nullptr;
    }
    void* ptr = GLES.glMapBufferRange(target, 0, buffer_size, flags);
    if (!ptr) return nullptr;
    BufferMapping mapping;
    mapping.target = target;
    mapping.buffer_id = (GLuint)current_buffer;
    mapping.mapped_ptr = ptr;
#if GLOBAL_DEBUG || DEBUG
    if (target == GL_PIXEL_UNPACK_BUFFER) {
        mapping.client_ptr = malloc(buffer_size);
        memset(mapping.client_ptr, 0xFF, buffer_size);
    }
#endif
    mapping.size = buffer_size;
    mapping.flags = flags;
    mapping.is_dirty = (flags & GL_MAP_WRITE_BIT) ? GL_TRUE : GL_FALSE;
    g_active_mappings[current_buffer] = mapping;
    CHECK_GL_ERROR
#if GLOBAL_DEBUG || DEBUG
    if (target == GL_PIXEL_UNPACK_BUFFER)
        return mapping.client_ptr;
    else
        return ptr;
#else
    return ptr;
#endif
}

#if GLOBAL_DEBUG || DEBUG
#include <fstream>
#define BIN_FILE_PREFIX "/sdcard/MG/buf/"
#endif

#ifdef __cplusplus
extern "C" {
#endif
GLAPI GLAPIENTRY void *glMapBufferARB(GLenum target, GLenum access) __attribute__((alias("glMapBuffer")));
GLAPI GLAPIENTRY void *glBufferDataARB(GLenum target, GLenum access) __attribute__((alias("glBufferData")));
GLAPI GLAPIENTRY GLboolean glUnmapBufferARB(GLenum target) __attribute__((alias("glUnmapBuffer")));
GLAPI GLAPIENTRY void glBufferStorageARB(GLenum target, GLsizeiptr size, const void* data, GLbitfield flags) __attribute__((alias("glBufferStorage")));
GLAPI GLAPIENTRY void glBindBufferARB(GLenum target, GLuint buffer) __attribute__((alias("glBindBuffer")));

#ifdef __cplusplus
}
#endif

GLboolean glUnmapBuffer(GLenum target) {
    LOG()
    if(g_gles_caps.GL_OES_mapbuffer)
        return GLES.glUnmapBuffer(target);

    GLint buffer;
    GLenum binding_query = get_binding_query(target);
    GLES.glGetIntegerv(binding_query, &buffer);

    if (buffer == 0)
        return GL_FALSE;

#if GLOBAL_DEBUG || DEBUG
//     Blit data from client side to OpenGL here
    if (target == GL_PIXEL_UNPACK_BUFFER) {
        auto &mapping = g_active_mappings[buffer];

        std::fstream fs(std::string(BIN_FILE_PREFIX) + "buf" + std::to_string(buffer) + ".bin", std::ios::out | std::ios::binary | std::ios::trunc);
        fs.write((const char*)mapping.client_ptr, mapping.size);
        fs.close();

//        memset(mapping.mapped_ptr, 0xFF, mapping.size);
        memcpy(mapping.mapped_ptr, mapping.client_ptr, mapping.size);
        free(mapping.client_ptr);
        mapping.client_ptr = nullptr;
    }
#endif

    GLboolean result = GLES.glUnmapBuffer(target);
    g_active_mappings.erase(buffer);
    CHECK_GL_ERROR
    return result;
}

void glBufferStorage(GLenum target, GLsizeiptr size, const void* data, GLbitfield flags) {
    LOG()
    if(GLES.glBufferStorageEXT)
        GLES.glBufferStorageEXT(target,size,data,flags);
    CHECK_GL_ERROR
}