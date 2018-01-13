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

using AeonEngineMono.Core;

namespace AeonEngineMono.Types
{
    public struct Vector4f
    {
        public float x;
        public float y;
        public float z;
        public float w;

        public Vector4f(float wxyz)
        {
            this.w = wxyz;
            this.x = wxyz;
            this.y = wxyz;
            this.z = wxyz;
        }

        public Vector4f(float x, float y)
        {
            this.x = x;
            this.y = y;
            this.z = 0;
            this.w = 0;
        }

        public Vector4f(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = 0;
        }

        public Vector4f(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public static Vector4f Zero
        {
            get { return new Vector4f(0, 0, 0, 0); }
        }

        public float Magnitude
        {
            get { return Mathf.Sqrt(Dot(this, this)); }
        }

        public Vector4f Normalized
        {
            get
            {
                var result = new Vector4f(this.x, this.y, this.z, this.w);
                result.Normalize();
                return result;
            }
        }

        public static float Distance(Vector4f a, Vector4f b)
        {
            var vec = a - b;
            return vec.Magnitude;
        }

        public static float Dot(Vector4f a, Vector4f b)
        {
            return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
        }

        public void Normalize()
        {
            var m = this.Magnitude;
            if (m > Mathf.Epsilon)
            {
                this /= m;
            }
            else
            {
                this = Vector4f.Zero;
            }
        }

        public void Scale(Vector4f scale)
        {
            this.x *= scale.x;
            this.y *= scale.y;
            this.z *= scale.z;
            this.w *= scale.w;
        }

        public void Set(float newX, float newY, float newZ, float newW)
        {
            this.x = newX;
            this.y = newY;
            this.z = newZ;
            this.w = newW;
        }

        public static Vector4f operator+(Vector4f lhs, Vector4f rhs)
        {
            return new Vector4f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
        }

        public static Vector4f operator-(Vector4f lhs, Vector4f rhs)
        {
            return new Vector4f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        }

        public static Vector4f operator-(Vector4f a)
        {
            return new Vector4f(-a.x, -a.y, -a.z, -a.w);
        }

        public static Vector4f operator*(Vector4f lhs, float rhs)
        {
            return new Vector4f(
                lhs.x * rhs,
                lhs.y * rhs,
                lhs.z * rhs,
                lhs.w * rhs);
        }

        public static Vector4f operator*(float lhs, Vector4f rhs)
        {
            return new Vector4f(
                rhs.x * lhs,
                rhs.y * lhs,
                rhs.z * lhs,
                rhs.w * lhs);
        }

        public static Vector4f operator/(Vector4f lhs, float rhs)
        {
            return new Vector4f(
                lhs.x / rhs,
                lhs.y / rhs,
                lhs.z / rhs,
                lhs.w / rhs);
        }

        public static bool operator==(Vector4f lhs, Vector4f rhs)
        {
            return (lhs.x == rhs.x) &&
                   (lhs.y == rhs.y) &&
                   (lhs.z == rhs.z) &&
                   (lhs.w == rhs.w);
        }

        public static bool operator!=(Vector4f lhs, Vector4f rhs)
        {
            return !(lhs == rhs);
        }
    }
}
