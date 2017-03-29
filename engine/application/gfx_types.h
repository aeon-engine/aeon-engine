/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <build_config.h>

#ifdef AEON_GFX_GL
#include <aeon/gfx/gl/gfx_gl_device.h>
using selected_gfx_device = aeon::gfx::gl::gfx_gl_device;
#endif // AEON_GFX_GL

#ifdef AEON_GFX_GLES2
#include <aeon/gfx/gles2/gfx_gles2_device.h>
using selected_gfx_device = aeon::gfx::gles2::gfx_gles2_device;
#endif // AEON_GFX_GLES2

#ifdef AEON_GFX_NULL
#include <gfx/null/gfx_null_device.h>
using selected_gfx_device = aeon::gfx::null::gfx_null_device;
#endif // AEON_GFX_NULL

///////////////////////////////////////////////////////////////////////////////

#ifdef AEON_PLATFORM_GLFW
#include <aeon/platform/glfw/glfw_platform_manager.h>
using selected_platform = aeon::platform::glfw::glfw_platform_manager;
#endif // AEON_PLATFORM_GLFW

#ifdef AEON_PLATFORM_SDL
#include <aeon/platform/sdl/sdl_platform_manager.h>
using selected_platform = aeon::platform::sdl::sdl_platform_manager;
#endif // AEON_PLATFORM_SDL

#ifdef AEON_PLATFORM_RPI
#include <aeon/platform/rpi/rpi_platform_manager.h>
using selected_platform = aeon::platform::rpi::rpi_platform_manager;
#endif // AEON_PLATFORM_RPI

