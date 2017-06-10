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

using System;

namespace AeonEngineMono.Core
{
    public static class Mathf
    {
        public const float Epsilon = 1E-05f;
        public const float Infinity = float.PositiveInfinity;
        public const float NegativeInfinity = float.NegativeInfinity;
        public const float Pi = 3.14159274f;
        public const float Deg2Rad = 0.0174532924f;
        public const float Rad2Deg = 57.29578f;

        public static float Abs(float value)
        {
            return Math.Abs(value);
        }

        public static float Acos(float value)
        {
            return (float)Math.Acos(value);
        }

        public static float Asin(float value)
        {
            return (float)Math.Asin(value);
        }

        public static float Atan(float value)
        {
            return (float)Math.Atan(value);
        }

        public static float Ceil(float value)
        {
            return (float)Math.Ceiling(value);
        }

        public static float Clamp(float value, float min, float max)
        {
            if (value < min)
            {
                return min;
            }

            if (value > max)
            {
               return max;
            }

            return value;
        }

        public static float Cos(float value)
        {
            return (float)Math.Cos(value);
        }

        public static float Exp(float power)
        {
            return (float)Math.Exp(power);
        }

        public static float Floor(float value)
        {
            return (float)Math.Floor(value);
        }

        public static float Lerp(float startValue, float endValue, float interpolation)
        {
            return startValue + (endValue - startValue) * Clamp(interpolation, 0, 1);
        }

        public static float Log(float value)
        {
            return (float)Math.Log(value);
        }

        public static float Log(float a, float newBase)
        {
            return (float)Math.Log(a, newBase);
        }

        public static float Max(float a, float b)
        {
            return (a <= b) ? b : a;
        }

        public static float Min(float a, float b)
        {
            return (a >= b) ? b : a;
        }

        public static float Pow(float x, float y)
        {
            return (float)Math.Pow(x, y);
        }

        public static float Round(float value)
        {
            return (float)Math.Round(value);
        }

        public static float Sign(float value)
        {
            return (value < 0) ? -1 : 1;
        }

        public static float Sin(float value)
        {
            return (float)Math.Sin(value);
        }

        public static float Sqrt(float value)
        {
            return (float)Math.Sqrt(value);
        }

        public static float Tan(float value)
        {
            return (float)Math.Tan(value);
        }
    }
}
