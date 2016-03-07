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
#include <resources/resource_manager.h>
#include <platform/platform_window.h>
#include <common/logger.h>
#include <buildinfo.h>
#include <build_config.h>
#include <aeon/utility.h>
#include <application/application_settings.h>

#ifdef AEON_PLATFORM_GLFW
#include <platform/glfw/platform_glfw_interface.h>
using selected_platform_interface = aeon::platform::glfw::platform_interface;
#endif // AEON_PLATFORM_GLFW

#ifdef AEON_PLATFORM_RPI
#include <platform/rpi/platform_rpi_interface.h>
using selected_platform_interface = aeon::platform::rpi::platform_interface;
#endif // AEON_PLATFORM_RPI

#ifdef AEON_PLATFORM_IOS
#include <platform/ios/platform_ios_interface.h>
using selected_platform_interface = aeon::platform::ios::platform_interface;
#endif

#ifdef AEON_GFX_GL
#include <gfx/gl/gfx_gl_device.h>
using selected_gfx_device = aeon::gfx::gl::device;
#endif // AEON_GFX_GL

#ifdef AEON_GFX_GLES2
#include <gfx/gles2/gfx_gles2_device.h>
using selected_gfx_device = aeon::gfx::gles2::device;
#endif // AEON_GFX_GLES2

namespace aeon
{

class aeon_application : aeon::utility::noncopyable
{
public:
    explicit aeon_application(int width, int height, const std::string &window_title)
        : logger_backend_()
        , logger_(common::logger::get_singleton(), "Application")
        , resource_manager_(platform_, device_)
        , window_(nullptr)
    {
        AEON_LOG_MESSAGE(logger_) << "Initializing Aeon Engine (" << buildinfo::full_version << ", "
                                  << buildinfo::build_date << ")." << std::endl;

        // Init the platform and window
        platform_.initialize();
        window_ = platform_.create_window(width, height, window_title);

        // Init opengl
        device_.initialize();
    }

    virtual ~aeon_application() = default;

    platform::platform_window_ptr get_main_window() const
    {
        return window_;
    }

    resources::resource_manager *get_resource_manager()
    {
        return &resource_manager_;
    }

    selected_platform_interface *get_platform_interface()
    {
        return &platform_;
    }

    selected_gfx_device *get_gfx_device()
    {
        return &device_;
    }

    aeon::logger::logger &get_logger()
    {
        return logger_;
    }

protected:
    common::logger logger_backend_;
    aeon::logger::logger logger_;

    selected_platform_interface platform_;
    selected_gfx_device device_;

    resources::resource_manager resource_manager_;

    platform::platform_window_ptr window_;
};

} // namespace aeon
