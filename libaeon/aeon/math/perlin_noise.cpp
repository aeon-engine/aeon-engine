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

#include <aeon/math.h>

namespace aeon
{
namespace math
{

perlin_noise::perlin_noise()
    : persistence_(0)
    , frequency_(0)
    , amplitude_(0)
    , octaves_(0)
    , randomseed_(0)
{
}

perlin_noise::perlin_noise(double _persistence, double _frequency, double _amplitude, int _octaves, int _randomseed)
    : persistence_(_persistence)
    , frequency_(_frequency)
    , amplitude_(_amplitude)
    , octaves_(_octaves)
    , randomseed_(2 + _randomseed * _randomseed)
{
}

void perlin_noise::set(double persistance, double frequency, double amplitude, int octaves, int randomseed)
{
    persistence_ = persistance;
    frequency_ = frequency;
    amplitude_ = amplitude;
    octaves_ = octaves;
    randomseed_ = 2 + randomseed * randomseed;
}

double perlin_noise::get_height(double x, double y) const
{
    return amplitude_ * total(x, y);
}

double perlin_noise::total(double i, double j) const
{
    // properties of one octave (changing each loop)
    double t = 0.0f;
    double _amplitude = 1;
    double freq = frequency_;

    for (int k = 0; k < octaves_; ++k)
    {
        t += get_value(j * freq + randomseed_, i * freq + randomseed_) * _amplitude;
        _amplitude *= persistence_;
        freq *= 2;
    }

    return t;
}

double perlin_noise::get_value(double x, double y) const
{
    int Xint = static_cast<int>(x);
    int Yint = static_cast<int>(y);
    double Xfrac = x - Xint;
    double Yfrac = y - Yint;

    // noise values
    double n01 = noise(Xint - 1, Yint - 1);
    double n02 = noise(Xint + 1, Yint - 1);
    double n03 = noise(Xint - 1, Yint + 1);
    double n04 = noise(Xint + 1, Yint + 1);
    double n05 = noise(Xint - 1, Yint);
    double n06 = noise(Xint + 1, Yint);
    double n07 = noise(Xint, Yint - 1);
    double n08 = noise(Xint, Yint + 1);
    double n09 = noise(Xint, Yint);

    double n12 = noise(Xint + 2, Yint - 1);
    double n14 = noise(Xint + 2, Yint + 1);
    double n16 = noise(Xint + 2, Yint);

    double n23 = noise(Xint - 1, Yint + 2);
    double n24 = noise(Xint + 1, Yint + 2);
    double n28 = noise(Xint, Yint + 2);

    double n34 = noise(Xint + 2, Yint + 2);

    // find the noise values of the four corners
    double x0y0 = 0.0625 * (n01 + n02 + n03 + n04) + 0.125 * (n05 + n06 + n07 + n08) + 0.25 * (n09);
    double x1y0 = 0.0625 * (n07 + n12 + n08 + n14) + 0.125 * (n09 + n16 + n02 + n04) + 0.25 * (n06);
    double x0y1 = 0.0625 * (n05 + n06 + n23 + n24) + 0.125 * (n03 + n04 + n09 + n28) + 0.25 * (n08);
    double x1y1 = 0.0625 * (n09 + n16 + n28 + n34) + 0.125 * (n08 + n14 + n06 + n24) + 0.25 * (n04);

    // interpolate between those values according to the x and y fractions
    double v1 = interpolate(x0y0, x1y0, Xfrac); // interpolate in x direction (y)
    double v2 = interpolate(x0y1, x1y1, Xfrac); // interpolate in x direction (y+1)
    double fin = interpolate(v1, v2, Yfrac);    // interpolate in y direction

    return fin;
}

double perlin_noise::interpolate(double x, double y, double a) const
{
    double negA = 1.0 - a;
    double negASqr = negA * negA;
    double fac1 = 3.0 * (negASqr)-2.0 * (negASqr * negA);
    double aSqr = a * a;
    double fac2 = 3.0 * aSqr - 2.0 * (aSqr * a);

    return x * fac1 + y * fac2; // add the weighted factors
}

double perlin_noise::noise(int x, int y) const
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return 1.0 - double(t) * 0.931322574615478515625e-9;
}

} // namespace math
} // namespace aeon
