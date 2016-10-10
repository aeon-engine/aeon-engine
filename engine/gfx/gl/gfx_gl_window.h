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
#include <gfx/gfx_window.h>
#include <gfx/gfx_exception.h>
#include <platform/platform_interface.h>
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

class gfx_gl_window : public gfx_window
{
public:
    explicit gfx_gl_window(platform::platform_interface &interface, const gfx_window_settings &settings,
                             GLFWmonitor *monitor);
    ~gfx_gl_window() override;

    void make_current() override;

    glm::vec2 get_framebuffer_size() override;

    void set_mouse_cursor_mode(const mouse_cursor_mode mode) override;

    mouse_cursor_mode get_mouse_cursor_mode() const override;

private:
    bool __on_frame_start(float dt) override;

    bool __on_frame_end(float dt) override;

    static void __static_keyboard_key_handler(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void __static_mouse_move_handler(GLFWwindow *window, double x, double y);
    static void __static_mouse_button_handler(GLFWwindow *window, int button, int action, int mods);
    static void __static_mouse_scroll_handler(GLFWwindow *window, double xoffset, double yoffset);

    aeon::logger::logger logger_;

    GLFWwindow *window_;
    platform::platform_interface &interface_;
    mouse_cursor_mode cursor_mode_;
};

using gfx_window_ptr = std::shared_ptr<gfx_window>;

} // namespace gl
} // namespace gfx
} // namespace aeon
