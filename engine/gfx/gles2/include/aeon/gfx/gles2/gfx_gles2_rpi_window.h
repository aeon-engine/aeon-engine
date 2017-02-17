/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
#include <EGL/egl.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_device;

class gfx_gles2_rpi_window : public gfx_window
{
public:
    explicit gfx_gles2_rpi_window(gfx_gles2_device &device, platform::platform_interface &,
                                  const gfx_window_settings &settings);
    ~gfx_gles2_rpi_window() override;

    void make_current() override;

    glm::vec2 get_framebuffer_size() const override;

    void set_mouse_cursor_mode(const mouse_cursor_mode mode) override;

    mouse_cursor_mode get_mouse_cursor_mode() const override;

private:
    void __reset_scissor() const;

    bool __on_frame_start(float dt) override;

    bool __on_frame_end(float dt) override;

    void __create_window();
    void __create_native_window();
    void __create_egl_context(EGLint attribList[]);

    aeon::logger::logger logger_;

    gfx_gles2_device &device_;

    EGL_DISPMANX_WINDOW_T window_;
    EGLDisplay display_;
    EGLContext context_;
    EGLSurface surface_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
