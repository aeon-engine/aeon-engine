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

#include <aeon/platform/platform_window_settings.h>

namespace aeon
{
namespace platform
{

window_settings::window_settings(const int width, const int height, const std::string &title)
    : width_(width)
    , height_(height)
    , title_(title)
    , multisample_(0)
    , buffer_mode_(buffer_mode::double_buffer)
{
}

auto window_settings::get_width() const -> int
{
    return width_;
}

auto window_settings::get_height() const -> int
{
    return height_;
}

auto window_settings::get_title() const -> const std::string &
{
    return title_;
}

void window_settings::set_multisample(const unsigned int samples)
{
    multisample_ = samples;
}

auto window_settings::get_multisample() const -> int
{
    return multisample_;
}

void window_settings::set_buffer_mode(const buffer_mode mode)
{
    buffer_mode_ = mode;
}

auto window_settings::get_buffer_mode() const -> buffer_mode
{
    return buffer_mode_;
}

} // namespace platform
} // namespace aeon
