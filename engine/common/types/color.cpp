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

#include <common/types/color.h>

// Workaround for Visual Studio's polluted headers.
#define NOMINMAX
#include <algorithm>

namespace aeon
{
namespace common
{
namespace types
{

color convert_to_rgb(const color_yuv& c)
{
    float r = c.y + (1.140f * c.v);
    float g = c.y - (0.395f * c.u) - (0.581f * c.v);
    float b = c.y + (2.032f * c.u);

    return color(r, g, b, c.a);
}

// Taken and modified from https://www.cs.rit.edu/~ncs/color/t_convert.html
color convert_to_rgb(const color_hsv& c)
{
    // achromatic (grey)
    if (c.s == 0)
        return color(c.v, c.v, c.v, c.a);

    float h = c.h;

    h /= 60.0f; // sector 0 to 5
    int i = static_cast<int>(floor(h));
    float f = h - i;			// factorial part of h
    float p = c.v * (1 - c.s);
    float q = c.v * (1 - c.s * f);
    float t = c.v * (1 - c.s * (1 - f));

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

color_yuv convert_to_yuv(const color& c)
{
    float y = (0.299f * c.r) + (0.587f * c.g) + (0.114f * c.b);
    float u = 0.492f * (c.b - y);
    float v = 0.877f * (c.r - y);

    return color_yuv(y, u, v, c.a);
}

// Taken and modified from https://www.cs.rit.edu/~ncs/color/t_convert.html
color_hsv convert_to_hsv(const color& c)
{
    float min = std::min<float>(std::min<float>(c.r, c.g), c.b);
    float max = std::max<float>(std::max<float>(c.r, c.g), c.b);
    float delta = max - min;

    float s = 0.0f;
    float h = 0.0f;
    float v = max;

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
