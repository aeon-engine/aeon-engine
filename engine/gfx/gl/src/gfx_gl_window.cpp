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

#include <aeon/gfx/gl/gfx_gl_window.h>
#include <aeon/gfx/gl/gfx_gl_device.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_window::gfx_gl_window(gfx_gl_device &device, platform::platform_interface &interface,
                             const gfx_window_settings &settings, GLFWmonitor *monitor)
    : gfx_window(settings)
    , logger_(common::logger::get_singleton(), "Gfx::GL::Window")
    , window_(nullptr)
    , device_(device)
    , interface_(interface)
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

    AEON_LOG_DEBUG(logger_) << "Setting user pointer." << std::endl;

    glfwSetWindowUserPointer(window_, this);

    AEON_LOG_DEBUG(logger_) << "Setting GLFW callbacks" << std::endl;

    glfwSetKeyCallback(window_, &gfx_gl_window::__static_keyboard_key_handler);
    glfwSetCursorPosCallback(window_, &gfx_gl_window::__static_mouse_move_handler);
    glfwSetMouseButtonCallback(window_, &gfx_gl_window::__static_mouse_button_handler);
    glfwSetScrollCallback(window_, &gfx_gl_window::__static_mouse_scroll_handler);

    AEON_LOG_DEBUG(logger_) << "Calling glfwMakeContextCurrent" << std::endl;

    glfwMakeContextCurrent(window_);

    AEON_LOG_DEBUG(logger_) << "Setting swap interval to 1." << std::endl;

    glfwSwapInterval(1);
}

gfx_gl_window::~gfx_gl_window()
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

void gfx_gl_window::make_current()
{
    glfwMakeContextCurrent(window_);
}

glm::vec2 gfx_gl_window::get_framebuffer_size() const
{
    int width, height;
    glfwGetFramebufferSize(window_, &width, &height);
    return glm::vec2(width, height);
}

void gfx_gl_window::set_mouse_cursor_mode(const mouse_cursor_mode mode)
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
            throw gfx_gl_cursor_mode_exception();
    }

    glfwSetInputMode(window_, GLFW_CURSOR, glfw_cursor_mode);
    cursor_mode_ = mode;
}

mouse_cursor_mode gfx_gl_window::get_mouse_cursor_mode() const
{
    return cursor_mode_;
}

GLFWwindow *gfx_gl_window::get_glfw_window_ptr() const
{
    return window_;
}

void gfx_gl_window::__reset_scissor() const
{
    glm::vec2 framebuffer_size = get_framebuffer_size();
    common::types::rectangle<float> rect(0.0f, 0.0f, framebuffer_size.x, framebuffer_size.y);
    device_.set_scissor(rect);
}

bool gfx_gl_window::__on_frame_start(float /*dt*/)
{
    make_current();

    if (glfwWindowShouldClose(window_))
        return false;

    return true;
}

bool gfx_gl_window::__on_frame_end(float /*dt*/)
{
    __reset_scissor();

    glFinish();
    glfwSwapBuffers(window_);
    return true;
}

void gfx_gl_window::__static_keyboard_key_handler(GLFWwindow *window, int key, int /*scancode*/, int action, int mods)
{
    gfx_gl_window *window_ptr = static_cast<gfx_gl_window *>(glfwGetWindowUserPointer(window));
    window_ptr->device_.get_input_handler().handle_keyboard_key_state_changed_event(
        static_cast<input::keyboard_key>(key),
        action == GLFW_RELEASE ? input::keyboard_key_state::released : input::keyboard_key_state::pressed, mods);
}

void gfx_gl_window::__static_mouse_move_handler(GLFWwindow *window, double x, double y)
{
    gfx_gl_window *window_ptr = static_cast<gfx_gl_window *>(glfwGetWindowUserPointer(window));
    window_ptr->device_.get_input_handler().handle_mouse_move_event(static_cast<float>(x), static_cast<float>(y));
}

void gfx_gl_window::__static_mouse_button_handler(GLFWwindow *window, int button, int action, int /*mods*/)
{
    gfx_gl_window *window_ptr = static_cast<gfx_gl_window *>(glfwGetWindowUserPointer(window));
    window_ptr->device_.get_input_handler().handle_mouse_button_event(
        static_cast<input::mouse_button>(button),
        action == GLFW_RELEASE ? input::mouse_button_state::released : input::mouse_button_state::pressed);
}

void gfx_gl_window::__static_mouse_scroll_handler(GLFWwindow *window, double xoffset, double yoffset)
{
    gfx_gl_window *window_ptr = static_cast<gfx_gl_window *>(glfwGetWindowUserPointer(window));
    window_ptr->device_.get_input_handler().handle_mouse_scroll_event(static_cast<float>(xoffset),
                                                                      static_cast<float>(yoffset));
}

} // namespace gl
} // namespace gfx
} // namespace aeon
