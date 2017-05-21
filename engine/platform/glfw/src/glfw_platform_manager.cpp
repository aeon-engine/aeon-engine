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

#include <aeon/platform/glfw/glfw_platform_manager.h>
#include <aeon/platform/glfw/glfw_platform_window.h>
#include <aeon/platform/platform_window_settings.h>
#include <GLFW/glfw3.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

const auto PLATFORM_MANAGER_LOGGER_NAME = "Platform::GLFW::Manager";

glfw_platform_manager::glfw_platform_manager(input::input_handler &input_handler, gfx::device &device)
    : platform_manager(input_handler, device)
    , logger_(common::logger::get_singleton(), PLATFORM_MANAGER_LOGGER_NAME)
    , initialized_(false)
    , running_(false)
    , previous_time_(0.0)
{
    __initialize_glfw();
    initialized_ = true;
}

glfw_platform_manager::~glfw_platform_manager()
{
    if (initialized_)
        glfwTerminate();
}

void glfw_platform_manager::run()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error starting message loop. Platform not initialized." << std::endl;
        throw platform_exception();
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

        if (!get_device().render(static_cast<float>(delta_time)))
            break;
    }

    AEON_LOG_DEBUG(logger_) << "Message loop stopped." << std::endl;
}

void glfw_platform_manager::stop()
{
    AEON_LOG_DEBUG(logger_) << "Stopping GLFW message loop." << std::endl;
    running_ = false;
}

auto glfw_platform_manager::get_monitors() -> std::vector<monitor *>
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error getting monitors. Platform not initialized." << std::endl;
        throw platform_exception();
    }

    if (!monitors_.empty())
    {
        return utility::container::unique_ptr_to_raw_ptr<monitor>(monitors_);
    }

    int count;
    GLFWmonitor **glfw_monitors = glfwGetMonitors(&count);
    GLFWmonitor *glfw_primary_monitor = glfwGetPrimaryMonitor();

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

        monitors_.emplace_back(std::make_unique<glfw_monitor>(m, physical_width, physical_height, x, y, primary, name));
    }

    return utility::container::unique_ptr_to_raw_ptr<monitor>(monitors_);
}

auto glfw_platform_manager::create_window(const window_settings &settings, monitor *monitor) -> std::shared_ptr<window>
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error creating window. Platform not initialized." << std::endl;
        throw platform_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Creating window: " << settings.get_width() << "x" << settings.get_height() << " '"
                            << settings.get_title() << "'." << std::endl;

    GLFWmonitor *glfw_monitor_ptr = nullptr;

    if (monitor)
    {
        auto m = dynamic_cast<glfw_monitor *>(monitor);
        glfw_monitor_ptr = m->get_internal_handle();
    }

    auto window = std::make_shared<glfw_window>(*this, settings, glfw_monitor_ptr);

    // Register this window as render target to the gfx device.
    // TODO: ownership? The device should not own this render target.
    get_device().add_render_target(window);

    return window;
}

void glfw_platform_manager::__initialize_glfw() const
{
    AEON_LOG_MESSAGE(logger_) << "Initializing GLFW." << std::endl;

    glfwSetErrorCallback(&glfw_platform_manager::__static_glfw_error_handler);

    int result = glfwInit();

    if (result == GL_FALSE)
    {
        AEON_LOG_FATAL(logger_) << "Could not initialize GLFW." << std::endl;
        throw platform_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Successfully initialized GLFW." << std::endl;
}

void glfw_platform_manager::__static_glfw_error_handler(int error, const char *description)
{
    // TODO: Handle this better.
    auto logger = logger::logger(common::logger::get_singleton(), PLATFORM_MANAGER_LOGGER_NAME);

    AEON_LOG_ERROR(logger) << "GLFW reported an error (ID: " << error << "): " << description << std::endl;
    throw platform_exception();
}

} // namespace glfw
} // namespace platform
} // namespace aeon
