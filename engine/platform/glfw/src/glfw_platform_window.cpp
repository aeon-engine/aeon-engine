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

#include <aeon/platform/glfw/glfw_platform_window.h>
#include <aeon/platform/glfw/glfw_platform_manager.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

glfw_window::glfw_window(glfw_platform_manager &platform_manager, const window_settings &settings, GLFWmonitor *monitor)
    : window(settings)
    , logger_(common::logger::get_singleton(), "Platform::GLFW::Window")
    , window_(nullptr)
    , platform_manager_(platform_manager)
    , cursor_mode_(mouse_cursor_mode::normal)
{
    AEON_LOG_DEBUG(logger_) << "Creating OpenGL 3.3 core profile context with forward compatibility." << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, settings.get_buffer_mode() == buffer_mode::double_buffer ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_FOCUSED, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, settings.get_multisample());

    window_ =
        glfwCreateWindow(settings.get_width(), settings.get_height(), settings.get_title().c_str(), monitor, nullptr);

    if (window_ == nullptr)
    {
        AEON_LOG_FATAL(logger_) << "Creating GLFW window failed." << std::endl;
    }

    AEON_LOG_DEBUG(logger_) << "Setting user pointer." << std::endl;

    glfwSetWindowUserPointer(window_, this);

    AEON_LOG_DEBUG(logger_) << "Setting GLFW callbacks" << std::endl;

    glfwSetKeyCallback(window_, &glfw_window::__static_keyboard_key_handler);
    glfwSetCursorPosCallback(window_, &glfw_window::__static_mouse_move_handler);
    glfwSetMouseButtonCallback(window_, &glfw_window::__static_mouse_button_handler);
    glfwSetScrollCallback(window_, &glfw_window::__static_mouse_scroll_handler);

    AEON_LOG_DEBUG(logger_) << "Calling glfwMakeContextCurrent" << std::endl;

    glfwMakeContextCurrent(window_);

    AEON_LOG_DEBUG(logger_) << "Setting swap interval to 1." << std::endl;

    glfwSwapInterval(1);

    platform_manager_.get_device().add_render_target(this);
}

glfw_window::~glfw_window()
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

    platform_manager_.get_device().remove_render_target(this);
}

void glfw_window::make_current()
{
    glfwMakeContextCurrent(window_);
}

auto glfw_window::get_framebuffer_size() const -> glm::vec2
{
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    return glm::vec2(width, height);
}

void glfw_window::set_mouse_cursor_mode(const mouse_cursor_mode mode)
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
            throw platform_exception();
    }

    glfwSetInputMode(window_, GLFW_CURSOR, glfw_cursor_mode);
    cursor_mode_ = mode;
}

auto glfw_window::get_mouse_cursor_mode() const -> mouse_cursor_mode
{
    return cursor_mode_;
}

auto glfw_window::get_glfw_window_ptr() const -> GLFWwindow *
{
    return window_;
}

void glfw_window::__reset_scissor() const
{
    glm::vec2 framebuffer_size = get_framebuffer_size();
    common::types::rectangle<float> rect(0.0f, 0.0f, framebuffer_size.x, framebuffer_size.y);
    platform_manager_.get_device().set_scissor(rect);
}

auto glfw_window::__on_frame_start(float /*dt*/) -> bool
{
    make_current();

    if (glfwWindowShouldClose(window_))
        return false;

    return true;
}

auto glfw_window::__on_frame_end(float /*dt*/) -> bool
{
    __reset_scissor();

    glFinish();
    glfwSwapBuffers(window_);

    return true;
}

void glfw_window::__static_keyboard_key_handler(GLFWwindow *window, int key, int /*scancode*/, int action, int mods)
{
    glfw_window *window_ptr = static_cast<glfw_window *>(glfwGetWindowUserPointer(window));
    window_ptr->get_platform_manager().get_input_handler().handle_keyboard_key_state_changed_event(
        static_cast<input::keyboard_key>(key),
        action == GLFW_RELEASE ? input::keyboard_key_state::released : input::keyboard_key_state::pressed, mods);
}

void glfw_window::__static_mouse_move_handler(GLFWwindow *window, double x, double y)
{
    glfw_window *window_ptr = static_cast<glfw_window *>(glfwGetWindowUserPointer(window));
    window_ptr->get_platform_manager().get_input_handler().handle_mouse_move_event(static_cast<float>(x),
                                                                                   static_cast<float>(y));
}

void glfw_window::__static_mouse_button_handler(GLFWwindow *window, int button, int action, int /*mods*/)
{
    glfw_window *window_ptr = static_cast<glfw_window *>(glfwGetWindowUserPointer(window));
    window_ptr->get_platform_manager().get_input_handler().handle_mouse_button_event(
        static_cast<input::mouse_button>(button),
        action == GLFW_RELEASE ? input::mouse_button_state::released : input::mouse_button_state::pressed);
}

void glfw_window::__static_mouse_scroll_handler(GLFWwindow *window, double xoffset, double yoffset)
{
    glfw_window *window_ptr = static_cast<glfw_window *>(glfwGetWindowUserPointer(window));
    window_ptr->get_platform_manager().get_input_handler().handle_mouse_scroll_event(static_cast<float>(xoffset),
                                                                                     static_cast<float>(yoffset));
}

} // namespace glfw
} // namespace platform
} // namespace aeon
