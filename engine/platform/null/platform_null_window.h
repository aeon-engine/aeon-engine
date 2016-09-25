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
#include <aeon/common/logger.h>
#include <memory>

namespace aeon
{
namespace platform
{
namespace null
{

class platform_interface;
class platform_window : public platform::platform_window
{
public:
    explicit platform_window(platform_interface *interface, const platform_window_settings &settings);
    ~platform_window() override;

    void make_current() override;

    glm::vec2 get_framebuffer_size() override;

    void set_mouse_cursor_mode(const mouse_cursor_mode mode) override;

    mouse_cursor_mode get_mouse_cursor_mode() const override;

private:
    bool __on_frame_start(float dt) override;

    bool __on_frame_end(float dt) override;

    aeon::logger::logger logger_;

    platform_interface *interface_;
};

using platform_window_ptr = std::shared_ptr<platform_window>;

} // namespace null
} // namespace platform
} // namespace aeon
