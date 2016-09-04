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
#include <application/base_application.h>
#include <resources/providers/filesystem_provider.h>

#ifdef AEON_PLATFORM_GLFW
#include <platform/glfw/platform_glfw_interface.h>
using selected_platform_interface = aeon::platform::glfw::platform_interface;
#endif // AEON_PLATFORM_GLFW

#ifdef AEON_PLATFORM_RPI
#include <platform/rpi/platform_rpi_interface.h>
using selected_platform_interface = aeon::platform::rpi::platform_interface;
#endif // AEON_PLATFORM_RPI

#ifdef AEON_PLATFORM_QT
#include <platform/qt/platform_qt_interface.h>
using selected_platform_interface = aeon::platform::qt::platform_interface;
#endif

#ifdef AEON_GFX_GL
#include <gfx/gl/gfx_gl_device.h>
using selected_gfx_device = aeon::gfx::gl::gfx_gl_device;
#endif // AEON_GFX_GL

#ifdef AEON_GFX_GLES2
#include <gfx/gles2/gfx_gles2_device.h>
using selected_gfx_device = aeon::gfx::gles2::device;
#endif // AEON_GFX_GLES2

#ifdef AEON_GFX_NULL
#include <gfx/null/gfx_null_device.h>
using selected_gfx_device = aeon::gfx::null::gfx_null_device;
#endif // AEON_GFX_NULL

namespace aeon
{

template <typename scene_manager_t>
class desktop_application
    : public base_application<selected_platform_interface, selected_gfx_device, scene_manager_t>
{
public:
    explicit desktop_application(int argc, char *argv[], int width, int height, const std::string &window_title)
        : base_application<selected_platform_interface, selected_gfx_device, scene_manager_t>(argc, argv, width, height, window_title)
    {
    }

    virtual ~desktop_application() = default;
};

} // namespace aeon
