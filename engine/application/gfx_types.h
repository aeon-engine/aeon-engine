/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

#include <build_config.h>

#ifdef AEON_GFX_GL
#include <aeon/gfx/gl/gfx_gl_device.h>
using selected_gfx_device = aeon::gfx::gl::gfx_gl_device;
#endif // AEON_GFX_GL

#ifdef AEON_GFX_GLES2
#include <gfx/gles2/gfx_gles2_device.h>
using selected_gfx_device = aeon::gfx::gles2::gfx_gles2_device;
#endif // AEON_GFX_GLES2

#ifdef AEON_GFX_NULL
#include <gfx/null/gfx_null_device.h>
using selected_gfx_device = aeon::gfx::null::gfx_null_device;
#endif // AEON_GFX_NULL
