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

#include <aeon/common/types/color.h>

#include <algorithm>
#include <cmath>

namespace aeon
{
namespace common
{
namespace types
{

auto convert_to_rgb(const color_yuv &c) -> color
{
    auto r = c.y + (1.140f * c.v);
    auto g = c.y - (0.395f * c.u) - (0.581f * c.v);
    auto b = c.y + (2.032f * c.u);

    return color(r, g, b, c.a);
}

// Taken and modified from https://www.cs.rit.edu/~ncs/color/t_convert.html
auto convert_to_rgb(const color_hsv &c) -> color
{
    // achromatic (grey)
    if (c.s == 0)
        return color(c.v, c.v, c.v, c.a);

    auto h = c.h;

    h /= 60.0f; // sector 0 to 5
    auto i = static_cast<int>(std::floor(h));
    auto f = h - i; // factorial part of h
    auto p = c.v * (1 - c.s);
    auto q = c.v * (1 - c.s * f);
    auto t = c.v * (1 - c.s * (1 - f));

    switch (i)
    {
        case 0:
            return color(c.v, t, p, c.a);
        case 1:
            return color(q, c.v, p, c.a);
        case 2:
            return color(p, c.v, t, c.a);
        case 3:
            return color(p, q, c.v, c.a);
        case 4:
            return color(t, p, c.v, c.a);
        case 5:
        default:
            return color(c.v, p, q, c.a);
    }
}

auto convert_to_yuv(const color &c) -> color_yuv
{
    auto y = (0.299f * c.r) + (0.587f * c.g) + (0.114f * c.b);
    auto u = 0.492f * (c.b - y);
    auto v = 0.877f * (c.r - y);

    return color_yuv(y, u, v, c.a);
}

// Taken and modified from https://www.cs.rit.edu/~ncs/color/t_convert.html
auto convert_to_hsv(const color &c) -> color_hsv
{
    auto min = std::min<float>(std::min<float>(c.r, c.g), c.b);
    auto max = std::max<float>(std::max<float>(c.r, c.g), c.b);
    auto delta = max - min;

    auto s = 0.0f;
    auto h = 0.0f;
    auto v = max;

    if (max != 0.0f)
    {
        s = delta / max;
    }
    else
    {
        // r = g = b = 0
        // s = 0, v is undefined
        return color_hsv(-1.0f, 0.0f, v, c.a);
    }

    if (c.r == max)
        h = (c.g - c.b) / delta; // between yellow & magenta
    else if (c.g == max)
        h = 2.0f + (c.b - c.r) / delta; // between cyan & yellow
    else
        h = 4.0f + (c.r - c.g) / delta; // between magenta & cyan

    h *= 60.0f; // degrees
    if (h < 0.0f)
        h += 360.0f;

    return color_hsv(h, s, v, c.a);
}

} // namespace types
} // namespace common
} // namespace aeon
