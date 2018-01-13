/*
 * Copyright (c) 2012-2018 Robin Degen
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

#pragma once

#include <iostream>

namespace aeon
{
namespace common
{
namespace types
{

/*!
 * Color class for YUV in floating point.
 */
class color_yuv
{
public:
    explicit color_yuv(const float y, const float u, const float v, const float a = 1.0f)
        : y(y)
        , u(u)
        , v(v)
        , a(a)
    {
    }

    ~color_yuv() = default;

    float y;
    float u;
    float v;
    float a;
};

/*!
 * Color class for Hue, Saturation, Value in floating point.
 */
class color_hsv
{
public:
    explicit color_hsv(const float h, const float s, const float v, const float a = 1.0f)
        : h(h)
        , s(s)
        , v(v)
        , a(a)
    {
    }

    ~color_hsv() = default;

    float h;
    float s;
    float v;
    float a;
};

/*!
 * Color class for floating point RGB colors (0.0f - 1.0f).
 */
class color
{
public:
    color()
        : r(0.0f)
        , g(0.0f)
        , b(0.0f)
        , a(1.0f)
    {
    }

    explicit color(const float red, const float green, const float blue, const float alpha = 1.0f)
        : r(red)
        , g(green)
        , b(blue)
        , a(alpha)
    {
    }

    ~color() = default;

    float r;
    float g;
    float b;
    float a;
};

/*!
 * Convert YUV to RGB.
 */
auto convert_to_rgb(const color_yuv &c) -> color;

/*!
 * Convert HSV to RGB.
 */
auto convert_to_rgb(const color_hsv &c) -> color;

/*!
 * Convert RGB to YUV
 */
auto convert_to_yuv(const color &c) -> color_yuv;

/*!
 * Convert RGB to HSV.
 */
auto convert_to_hsv(const color &c) -> color_hsv;

/*!
 * Stream operator overload for rectangle. This allows rectangle to be used with std streams
 * like std::cout and std::stringstream.
 */
template <typename T>
inline auto &operator<<(std::ostream &os, const color &c)
{
    return os << "color(" << c.r << "," << c.g << "," << c.b << "," << c.a << ")";
}

} // namespace types
} // namespace common
} // namespace aeon
