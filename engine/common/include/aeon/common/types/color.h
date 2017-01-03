/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
    explicit color_yuv(float y_, float u_, float v_, float a_ = 1.0f)
        : y(y_)
        , u(u_)
        , v(v_)
        , a(a_)
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
    explicit color_hsv(float h_, float s_, float v_, float a_ = 1.0f)
        : h(h_)
        , s(s_)
        , v(v_)
        , a(a_)
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

    explicit color(float red, float green, float blue, float alpha = 1.0f)
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
color convert_to_rgb(const color_yuv &c);

/*!
 * Convert HSV to RGB.
 */
color convert_to_rgb(const color_hsv &c);

/*!
 * Convert RGB to YUV
 */
color_yuv convert_to_yuv(const color &c);

/*!
* Convert RGB to HSV.
*/
color_hsv convert_to_hsv(const color &c);

/*!
 * Stream operator overload for rectangle. This allows rectangle to be used with std streams
 * like std::cout and std::stringstream.
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const color &c)
{
    return os << "color(" << c.r << "," << c.g << "," << c.b << "," << c.a << ")";
}

} // namespace types
} // namespace common
} // namespace aeon
