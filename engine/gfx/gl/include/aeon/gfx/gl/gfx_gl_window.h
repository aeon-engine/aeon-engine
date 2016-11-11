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
#include <aeon/gfx/gfx_window.h>
#include <aeon/gfx/gfx_exception.h>
#include <aeon/platform/platform_interface.h>
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
    explicit gfx_gl_window(gfx_gl_device &device, platform::platform_interface &, const gfx_window_settings &settings,
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
