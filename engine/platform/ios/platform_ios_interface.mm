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

#include <platform/ios/platform_ios_interface.h>
#include <platform/ios/platform_ios_monitor.h>
#include <platform/ios/platform_ios_window.h>
#include <platform/ios/platform_ios_filesystem_interface.h>
#include <OpenGLES/ES2/gl.h>
#include <common/check_gl_error.h>

#import <UIKit/UIKit.h>

namespace aeon
{
namespace platform
{
namespace ios
{

platform_interface::platform_interface()
    : platform::platform_interface(std::make_unique<ios::platform_filesystem_interface>())
    , logger_(common::logger::get_singleton(), "Platform::Raspberry")
    , initialized_(false)
    , running_(false)
    , previous_time_(0.0)
{
}

platform_interface::~platform_interface()
{
}

void platform_interface::initialize()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing Raspberry Pi." << std::endl;

    initialized_ = true;
}

void platform_interface::run()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error starting message loop. Platform not initialized." << std::endl;
        throw platform_interface_initialize_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Starting message loop." << std::endl;

    //previous_time_ = glfwGetTime();

    running_ = true;

    while (running_)
    {
        //double current_time = glfwGetTime(); //TODO: calculate delta time
        double delta_time = 0.1f; //current_time - previous_time_;
        //previous_time_ = current_time;

        // TODO: handle input

        // Todo: This does not belong here. However the platform interface does not know about the gfx device.
        glClear(GL_COLOR_BUFFER_BIT);
        AEON_CHECK_GL_ERROR();

        for (gfx::render_target_ptr render_target : render_targets_)
        {
            if (!render_target->handle_frame(static_cast<float>(delta_time)))
            {
                running_ = false;
                break;
            }
        }
    }

    AEON_LOG_DEBUG(logger_) << "Message loop stopped." << std::endl;
}

void platform_interface::stop()
{
    AEON_LOG_DEBUG(logger_) << "Stopping GLFW message loop." << std::endl;
    running_ = false;
}

platform_monitors platform_interface::get_monitors()
{
    throw std::runtime_error("Not implemented.");
}

platform::platform_window_ptr platform_interface::create_window(int width, int height, const std::string &name,
                                                                platform_monitor_ptr monitor)
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error creating window. Platform not initialized." << std::endl;
        throw platform_interface_initialize_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Creating window: " << width << "x" << height << " '" << name << "'." << std::endl;

    platform_window_ptr window = std::make_shared<ios::platform_window>(this, width, height, name);

    render_targets_.push_back(window);

    return window;
}

} // namespace ios
} // namespace platform
} // namespace aeon
