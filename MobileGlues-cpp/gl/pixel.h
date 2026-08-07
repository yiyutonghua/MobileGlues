// MobileGlues - gl/pixel.h
// Copyright (c) 2025-2026 MobileGL-Dev
// Licensed under the GNU Lesser General Public License v2.1:
//   https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
// SPDX-License-Identifier: LGPL-2.1-only
// End of Source File Header

#ifndef MOBILEGLUES_PIXEL_H
#define MOBILEGLUES_PIXEL_H

#include <GL/gl.h>
#include "../gles/gles.h"
#include "log.h"

// Round up to a pixel-store alignment boundary.
#define widthalign(width, align) ((((uintptr_t)(width)) + ((uintptr_t)(align) - 1)) & (~((uintptr_t)(align) - 1)))

GLsizei gl_sizeof(GLenum type);

GLsizei pixel_sizeof(GLenum format, GLenum type);

GLboolean is_type_packed(GLenum type);


#endif // MOBILEGLUES_PIXEL_H
