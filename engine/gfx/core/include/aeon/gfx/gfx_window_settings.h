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

namespace aeon
{
namespace gfx
{

enum class buffer_mode
{
    single_buffer,
    double_buffer
};

class gfx_window_settings
{
public:
    gfx_window_settings(const int width, const int height, const std::string &title)
        : width_(width)
        , height_(height)
        , title_(title)
        , multisample_(0)
        , buffer_mode_(buffer_mode::double_buffer)
    {
    }

    ~gfx_window_settings() = default;

    int get_width() const
    {
        return width_;
    }

    int get_height() const
    {
        return height_;
    }

    const std::string &get_title() const
    {
        return title_;
    }

    void set_multisample(const unsigned int samples)
    {
        multisample_ = samples;
    }

    int get_multisample() const
    {
        return multisample_;
    }

    void set_buffer_mode(const buffer_mode mode)
    {
        buffer_mode_ = mode;
    }

    buffer_mode get_buffer_mode() const
    {
        return buffer_mode_;
    }

private:
    int width_;
    int height_;
    std::string title_;

    unsigned int multisample_;
    buffer_mode buffer_mode_;
};

} // namespace gfx
} // namespace aeon
