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
#include <aeon/gfx/gfx_window.h>
#include <aeon/gfx/gfx_exception.h>
#include <aeon/io/io_interface.h>
#include <aeon/common/logger.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gl
{

DEFINE_EXCEPTION_OBJECT(gfx_gl_cursor_mode_exception, gfx_exception,
                        "Unknown or invalid mouse cursor mode given to GLFW.");

class gfx_gl_device;

class gfx_gl_window : public gfx_window
{
public:
    explicit gfx_gl_window(gfx_gl_device &device, io::io_interface &, const gfx_window_settings &settings,
                           GLFWmonitor *monitor);
    ~gfx_gl_window() override;

    void make_current() override;

    glm::vec2 get_framebuffer_size() const override;

    void set_mouse_cursor_mode(const mouse_cursor_mode mode) override;

    mouse_cursor_mode get_mouse_cursor_mode() const override;

    GLFWwindow *get_glfw_window_ptr() const;

private:
    void __reset_scissor() const;

    bool __on_frame_start(float dt) override;

    bool __on_frame_end(float dt) override;

    static void __static_keyboard_key_handler(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void __static_mouse_move_handler(GLFWwindow *window, double x, double y);
    static void __static_mouse_button_handler(GLFWwindow *window, int button, int action, int mods);
    static void __static_mouse_scroll_handler(GLFWwindow *window, double xoffset, double yoffset);

    aeon::logger::logger logger_;

    GLFWwindow *window_;
    gfx_gl_device &device_;
    mouse_cursor_mode cursor_mode_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
