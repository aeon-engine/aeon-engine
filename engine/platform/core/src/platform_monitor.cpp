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

#include <aeon/platform/platform_monitor.h>

namespace aeon
{
namespace platform
{

video_mode::video_mode(int w, int h, int r, int g, int b, int rr)
    : width(w)
    , height(h)
    , red_bits(r)
    , green_bits(g)
    , blue_bits(b)
    , refresh_rate(rr)
{
}

gamma_ramp_data::gamma_ramp_data(int r, int g, int b)
    : red(r)
    , green(g)
    , blue(b)
{
}

monitor::monitor(int width, int height, int x, int y, bool primary, const std::string &name)
    : physical_width_(width)
    , physical_height_(height)
    , x_(x)
    , y_(y)
    , primary_(primary)
    , name_(name)
{
}

void monitor::get_physical_dimensions(int &width, int &height) const
{
    width = physical_width_;
    height = physical_height_;
}

void monitor::get_position(int &x, int &y) const
{
    x = x_;
    y = y_;
}

auto monitor::is_primary() const -> bool
{
    return primary_;
}

auto monitor::get_name() const -> const std::string &
{
    return name_;
}

} // namespace platform
} // namespace aeon
