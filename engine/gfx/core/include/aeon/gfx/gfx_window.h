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

#include <aeon/gfx/gfx_window_settings.h>
#include <aeon/gfx/gfx_render_target.h>
#include <glm/vec2.hpp>
#include <string>
#include <memory>

namespace aeon
{
namespace gfx
{

/*!
 * Enum that describes the behaviour of the mouse cursor in relation to the render window.
 */
enum mouse_cursor_mode
{
    normal,  // Normal cursor
    capture, // Capture the cursor (infinite mouse movements)
    hidden,  // Normal cursor, but hidden when moved over the window
};

class gfx_window : public render_target
{
public:
    explicit gfx_window(const gfx_window_settings &settings)
        : width_(settings.get_width())
        , height_(settings.get_height())
        , title_(settings.get_title())
    {
    }

    virtual ~gfx_window() = default;

    glm::vec2 get_size() const
    {
        return glm::vec2(width_, height_);
    }

    void get_size(int &width, int &height) const
    {
        width = width_;
        height = height_;
    }

    const std::string &get_title() const
    {
        return title_;
    }

    virtual void set_mouse_cursor_mode(const mouse_cursor_mode mode) = 0;
    virtual mouse_cursor_mode get_mouse_cursor_mode() const = 0;

private:
    int width_;
    int height_;
    std::string title_;
};

} // namespace gfx
} // namespace aeon
