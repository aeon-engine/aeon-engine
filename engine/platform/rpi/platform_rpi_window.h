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
#include <platform/platform_window.h>
#include <common/logger.h>
#include <EGL/egl.h>
#include <memory>

namespace aeon
{
namespace platform
{
namespace rpi
{

class platform_interface;
class platform_window : public platform::platform_window
{
public:
    explicit platform_window(platform_interface *interface, int width, int height, const std::string &title);
    ~platform_window() override;

    void make_current() override;

    glm::vec2 get_framebuffer_size() override;

private:
    bool __on_frame_start(float dt) override;
    bool __on_frame_end(float dt) override;

    void __create_window();
    void __create_native_window();
    void __create_egl_context(EGLint attribList[]);

    aeon::logger::logger logger_;
    platform_interface *interface_;

    EGL_DISPMANX_WINDOW_T window_;
    EGLDisplay display_;
    EGLContext context_;
    EGLSurface surface_;
};

using platform_window_ptr = std::shared_ptr<platform_window>;

} // namespace rpi
} // namespace platform
} // namespace aeon
