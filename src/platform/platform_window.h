/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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
#include <gfx/gfx_render_target.h>
#include <string>
#include <memory>

namespace aeon
{
namespace platform
{

class platform_window : public gfx::render_target
{
public:
    platform_window(int width, int height, const std::string &title) :
        width_(width),
        height_(height),
        title_(title)
    {
    }

    virtual ~platform_window() = default;

    void get_size(int &width, int &height) const
    {
        width = width_;
        height = height_;
    }

    const std::string &get_title() const
    {
        return title_;
    }

private:
    int width_;
    int height_;
    std::string title_;
};

using platform_window_ptr = std::shared_ptr<platform_window>;

} // namespace platform
} // namespace aeon
