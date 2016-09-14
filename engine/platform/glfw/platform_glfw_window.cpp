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

#include <platform/glfw/platform_glfw_window.h>
#include <platform/glfw/platform_glfw_interface.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

platform_window::platform_window(platform_interface *interface, int width, int height, const std::string &title,
                                 GLFWmonitor *monitor)
    : platform::platform_window(width, height, title)
    , logger_(common::logger::get_singleton(), "Platform::GLFW")
    , window_(nullptr)
    , interface_(interface)
    , cursor_mode_(mouse_cursor_mode::normal)
{
    AEON_LOG_DEBUG(logger_) << "Creating OpenGL 3.3 core profile context with forward compatibility." << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);

    window_ = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);

    AEON_LOG_DEBUG(logger_) << "Setting user pointer." << std::endl;

    glfwSetWindowUserPointer(window_, this);

    AEON_LOG_DEBUG(logger_) << "Setting GLFW callbacks" << std::endl;

    glfwSetKeyCallback(window_, &platform_window::__static_keyboard_key_handler);
    glfwSetCursorPosCallback(window_, &platform_window::__static_mouse_move_handler);
    glfwSetMouseButtonCallback(window_, &platform_window::__static_mouse_button_handler);
    glfwSetScrollCallback(window_, &platform_window::__static_mouse_scroll_handler);

    AEON_LOG_DEBUG(logger_) << "Calling glfwMakeContextCurrent" << std::endl;

    glfwMakeContextCurrent(window_);

    AEON_LOG_DEBUG(logger_) << "Setting swap interval to 1." << std::endl;

    glfwSwapInterval(1);
}

platform_window::~platform_window()
{
    if (window_)
    {
        AEON_LOG_DEBUG(logger_) << "Window destructor called; Calling glfwDestroyWindow." << std::endl;
        glfwDestroyWindow(window_);
    }
    else
    {
        AEON_LOG_WARNING(logger_) << "Window destructor called with no GLFW window created." << std::endl;
    }
}

void platform_window::make_current()
{
    glfwMakeContextCurrent(window_);
}

glm::vec2 platform_window::get_framebuffer_size()
{
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    return glm::vec2(width, height);
}

void platform_window::set_mouse_cursor_mode(const mouse_cursor_mode mode)
{
    int glfw_cursor_mode = GLFW_CURSOR_NORMAL;

    switch (mode)
    {
        case normal:
            glfw_cursor_mode = GLFW_CURSOR_NORMAL;
            break;
        case capture:
            glfw_cursor_mode = GLFW_CURSOR_DISABLED;
            break;
        case hidden:
            glfw_cursor_mode = GLFW_CURSOR_HIDDEN;
            break;
        default:
            throw platform_glfw_cursor_mode_exception();
    }

    glfwSetInputMode(window_, GLFW_CURSOR, glfw_cursor_mode);
    cursor_mode_ = mode;
}

mouse_cursor_mode platform_window::get_mouse_cursor_mode() const
{
    return cursor_mode_;
}

bool platform_window::__on_frame_start(float /*dt*/)
{
    make_current();

    if (glfwWindowShouldClose(window_))
        return false;

    return true;
}

bool platform_window::__on_frame_end(float /*dt*/)
{
    glFinish();
    glfwSwapBuffers(window_);
    return true;
}

void platform_window::__static_keyboard_key_handler(GLFWwindow *window, int key, int /*scancode*/, int action, int mods)
{
    platform_window *platform_window_ptr = static_cast<platform_window *>(glfwGetWindowUserPointer(window));
    platform_window_ptr->interface_->get_input_handler()->handle_keyboard_event(
        platform_window_ptr, static_cast<keyboard_key>(key),
        action == GLFW_RELEASE ? keyboard_key_state::released : keyboard_key_state::pressed, mods);
}

void platform_window::__static_mouse_move_handler(GLFWwindow *window, double x, double y)
{
    platform_window *platform_window_ptr = static_cast<platform_window *>(glfwGetWindowUserPointer(window));
    platform_window_ptr->interface_->get_input_handler()->handle_mouse_move_event(
        platform_window_ptr, static_cast<float>(x), static_cast<float>(y));
}

void platform_window::__static_mouse_button_handler(GLFWwindow *window, int button, int action, int /*mods*/)
{
    platform_window *platform_window_ptr = static_cast<platform_window *>(glfwGetWindowUserPointer(window));
    platform_window_ptr->interface_->get_input_handler()->handle_mouse_button_event(
        platform_window_ptr, static_cast<mouse_button>(button),
        action == GLFW_RELEASE ? mouse_button_state::released : mouse_button_state::pressed);
}

void platform_window::__static_mouse_scroll_handler(GLFWwindow *window, double xoffset, double yoffset)
{
    platform_window *platform_window_ptr = static_cast<platform_window *>(glfwGetWindowUserPointer(window));
    platform_window_ptr->interface_->get_input_handler()->handle_mouse_scroll_event(
        platform_window_ptr, static_cast<float>(xoffset), static_cast<float>(yoffset));
}

} // namespace glfw
} // namespace platform
} // namespace aeon
