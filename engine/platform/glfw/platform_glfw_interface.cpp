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

#include <platform/glfw/platform_glfw_interface.h>
#include <platform/glfw/platform_glfw_monitor.h>
#include <platform/glfw/platform_glfw_window.h>
#include <platform/generic/platform_generic_filesystem_interface.h>
#include <GLFW/glfw3.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

platform_interface::platform_interface()
    : platform::platform_interface(std::make_unique<generic::platform_filesystem_interface>())
    , logger_(common::logger::get_singleton(), "Platform::GLFW")
    , initialized_(false)
    , running_(false)
    , previous_time_(0.0)
{
}

platform_interface::~platform_interface()
{
    if (initialized_)
        glfwTerminate();

    initialized_ = false;
}

void platform_interface::initialize()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing GLFW." << std::endl;

    int result = glfwInit();

    if (result == GL_FALSE)
    {
        AEON_LOG_FATAL(logger_) << "Could not initialize GLFW." << std::endl;
        throw platform_interface_initialize_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Successfully initialized GLFW." << std::endl;

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

    previous_time_ = glfwGetTime();

    running_ = true;

    while (running_)
    {
        double current_time = glfwGetTime();
        double delta_time = current_time - previous_time_;
        previous_time_ = current_time;

        glfwPollEvents();

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
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error getting monitors. Platform not initialized." << std::endl;
        throw platform_interface_initialize_exception();
    }

    int count;
    GLFWmonitor **glfw_monitors = glfwGetMonitors(&count);
    GLFWmonitor *glfw_primary_monitor = glfwGetPrimaryMonitor();

    platform_monitors monitors;

    for (int i = 0; i < count; ++i)
    {
        GLFWmonitor *m = glfw_monitors[i];

        int physical_width;
        int physical_height;
        glfwGetMonitorPhysicalSize(m, &physical_width, &physical_height);

        int x;
        int y;
        glfwGetMonitorPos(m, &x, &y);

        bool primary = (glfw_primary_monitor == m);

        const char *name = glfwGetMonitorName(m);

        monitors.emplace_back(
            std::make_shared<platform_monitor>(m, physical_width, physical_height, x, y, primary, name));
    }

    return monitors;
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

    GLFWmonitor *glfw_monitor = nullptr;

    if (monitor)
    {
        std::shared_ptr<platform_monitor> m = std::dynamic_pointer_cast<platform_monitor>(monitor);
        glfw_monitor = m->get_internal_handle();
    }

    platform_window_ptr window = std::make_shared<glfw::platform_window>(this, width, height, name, glfw_monitor);

    render_targets_.push_back(window);

    return window;
}

} // namespace glfw
} // namespace platform
} // namespace aeon
