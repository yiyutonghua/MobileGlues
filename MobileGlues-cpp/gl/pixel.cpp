// MobileGlues - gl/pixel.cpp
// Copyright (c) 2025-2026 MobileGL-Dev
// Licensed under the GNU Lesser General Public License v2.1:
//   https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
// SPDX-License-Identifier: LGPL-2.1-only
// End of Source File Header

#include "pixel.h"
#include "log.h"
#include "mg.h"

#define DEBUG 0

GLsizei gl_sizeof(GLenum type) {
    // types
    switch (type) {
    case GL_DOUBLE:
        return 8;
    case GL_FLOAT:
    case GL_INT:
    case GL_UNSIGNED_INT:
    case GL_UNSIGNED_INT_10_10_10_2:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
    case GL_UNSIGNED_INT_8_8_8_8:
    case GL_UNSIGNED_INT_8_8_8_8_REV:
    case GL_UNSIGNED_INT_24_8:
    case GL_4_BYTES:
        return 4;
    case GL_3_BYTES:
        return 3;
    case GL_LUMINANCE_ALPHA:
    case GL_SHORT:
    case GL_HALF_FLOAT:
    case GL_UNSIGNED_SHORT:
    case GL_UNSIGNED_SHORT_1_5_5_5_REV:
    case GL_UNSIGNED_SHORT_4_4_4_4:
    case GL_UNSIGNED_SHORT_4_4_4_4_REV:
    case GL_UNSIGNED_SHORT_5_5_5_1:
    case GL_UNSIGNED_SHORT_5_6_5:
    case GL_UNSIGNED_SHORT_5_6_5_REV:
    case GL_2_BYTES:
        return 2;
    case GL_ALPHA:
    case GL_LUMINANCE:
    case GL_BYTE:
    case GL_UNSIGNED_BYTE:
    case GL_UNSIGNED_BYTE_2_3_3_REV:
    case GL_UNSIGNED_BYTE_3_3_2:
    case GL_DEPTH_COMPONENT:
    case GL_COLOR_INDEX:
        return 1;
    default:
        LOG_D("Unsupported pixel data type: %s\n", glEnumToString(type))
        return 0;
    }
}

GLboolean is_type_packed(GLenum type) {
    switch (type) {
    case GL_4_BYTES:
    case GL_3_BYTES:
    case GL_2_BYTES:
    case GL_UNSIGNED_BYTE_2_3_3_REV:
    case GL_UNSIGNED_BYTE_3_3_2:
    case GL_UNSIGNED_INT_10_10_10_2:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
    case GL_UNSIGNED_INT_8_8_8_8:
    case GL_UNSIGNED_INT_8_8_8_8_REV:
    case GL_UNSIGNED_SHORT_1_5_5_5_REV:
    case GL_UNSIGNED_SHORT_4_4_4_4:
    case GL_UNSIGNED_SHORT_4_4_4_4_REV:
    case GL_UNSIGNED_SHORT_5_5_5_1:
    case GL_UNSIGNED_SHORT_5_6_5:
    case GL_UNSIGNED_SHORT_5_6_5_REV:
    case GL_DEPTH_STENCIL:
        return true;
    default:
        return false;
    }
}

GLsizei pixel_sizeof(GLenum format, GLenum type) {
    GLsizei width = 0;
    switch (format) {
    case GL_R:
    case GL_RED:
    case GL_ALPHA:
    case GL_LUMINANCE:
    case GL_DEPTH_COMPONENT:
    case GL_DEPTH_STENCIL:
    case GL_COLOR_INDEX:
        width = 1;
        break;
    case GL_RG:
    case GL_LUMINANCE_ALPHA:
        width = 2;
        break;
    case GL_RGB:
    case GL_BGR:
    case GL_RGB8:
        width = 3;
        break;
    case GL_RGBA:
    case GL_BGRA:
    case GL_RGBA8:
    case GL_R11F_G11F_B10F:
    case GL_R32F:
        width = 4;
        break;
    default:
        LOG_D("unsupported pixel format %s\n", glEnumToString(format))
        return 0;
    }

    if (is_type_packed(type)) width = 1;

    return width * gl_sizeof(type);
}
