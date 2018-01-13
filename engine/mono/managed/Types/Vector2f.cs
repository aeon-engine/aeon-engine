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
    public struct Vector2f
    {
        public float x;
        public float y;

        public Vector2f(float xy)
        {
            this.x = xy;
            this.y = xy;
        }

        public Vector2f(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        public static Vector2f Zero
        {
            get { return new Vector2f(0, 0); }
        }

        public float Magnitude
        {
            get { return Mathf.Sqrt((this.x * this.x) + (this.y * this.y)); }
        }

        public Vector2f Normalized
        {
            get
            {
                var result = new Vector2f(this.x, this.y);
                result.Normalize();
                return result;
            }
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
                this = Vector2f.Zero;
            }
        }

        public void Set(float newX, float newY)
        {
            this.x = newX;
            this.y = newY;
        }

        public void Scale(Vector2f scale)
        {
            this.x *= scale.x;
            this.y *= scale.y;
        }

        public static float Dot(Vector2f lhs, Vector2f rhs)
        {
            return (lhs.x * rhs.x) + (lhs.y * rhs.y);
        }

        public static Vector2f operator +(Vector2f lhs, Vector2f rhs)
        {
            return new Vector2f(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        public static Vector2f operator -(Vector2f lhs, Vector2f rhs)
        {
            return new Vector2f(lhs.x - rhs.x, lhs.y - rhs.y);
        }

        public static Vector2f operator -(Vector2f a)
        {
            return new Vector2f(-a.x, -a.y);
        }

        public static Vector2f operator *(Vector2f lhs, float rhs)
        {
            return new Vector2f(lhs.x * rhs, lhs.y * rhs);
        }

        public static Vector2f operator *(float lhs, Vector2f rhs)
        {
            return new Vector2f(rhs.x * lhs, rhs.y * lhs);
        }

        public static Vector2f operator /(Vector2f lhs, float rhs)
        {
            return new Vector2f(lhs.x / rhs, lhs.y / rhs);
        }

        public static bool operator ==(Vector2f lhs, Vector2f rhs)
        {
            return (lhs.x == rhs.x) && (lhs.y == rhs.y);
        }

        public static bool operator !=(Vector2f lhs, Vector2f rhs)
        {
            return !(lhs == rhs);
        }

        public static implicit operator Vector2f(Vector3f v)
        {
            return new Vector2f(v.x, v.y);
        }
    }
}
