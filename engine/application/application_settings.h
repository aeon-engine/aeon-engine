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

#include <string>
#include <build_config.h>

namespace aeon
{

class application_settings
{
    template <typename scene_manager_t>
    friend class aeon_application;
public:
    application_settings()
        : window_size_hint_width_(AEON_DEFAULT_WINDOW_WIDTH_HINT)
        , window_size_hint_height_(AEON_DEFAULT_WINDOW_HEIGHT_HINT)
        , window_title_hint_(AEON_DEFAULT_WINDOW_TITLE_HINT)
    {
    }

    virtual ~application_settings() = default;

    void set_window_size_hint(int width, int height)
    {
        window_size_hint_width_ = width;
        window_size_hint_height_ = height;
    }

    void set_window_title_hint(const std::string &title)
    {
        window_title_hint_ = title;
    }

private:
    int window_size_hint_width_;
    int window_size_hint_height_;
    std::string window_title_hint_;
};

} // namespace aeon
