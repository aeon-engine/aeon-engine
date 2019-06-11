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
    public struct Vector3f
    {
        public float x { get; set; }
        public float y { get; set; }
        public float z { get; set; }

        public Vector3f(float xyz)
        {
            this.x = xyz;
            this.y = xyz;
            this.z = xyz;
        }

        public Vector3f(float x, float y)
        {
            this.x = x;
            this.y = y;
            this.z = 0;
        }

        public Vector3f(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public static Vector3f Zero
        {
            get { return new Vector3f(0, 0, 0); }
        }

        public float Magnitude
        {
            get { return Mathf.Sqrt((this.x * this.x) + (this.y * this.y) + (this.z * this.z)); }
        }

        public Vector3f Normalized
        {
            get
            {
                var result = new Vector3f(this.x, this.y, this.z);
                result.Normalize();
                return result;
            }
        }

        public static Vector3f Cross(Vector3f a, Vector3f b)
        {
            return new Vector3f(
                (a.y * b.z) - (a.z * b.y),
                (a.z * b.x) - (a.x * b.z),
                (a.x * b.y) - (a.y * b.x));
        }

        public static float Dot(Vector3f a, Vector3f b)
        {
            return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
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
                this = Vector3f.Zero;
            }
        }

        public void Set(float newX, float newY, float newZ)
        {
            this.x = newX;
            this.y = newY;
            this.z = newZ;
        }

        public void Scale(Vector3f scale)
        {
            this.x *= scale.x;
            this.y *= scale.y;
            this.z *= scale.z;
        }

        public static Vector3f operator+(Vector3f lhs, Vector3f rhs)
        {
            return new Vector3f(
                lhs.x + rhs.x,
                lhs.y + rhs.y,
                lhs.z + rhs.z);
        }

        public static Vector3f operator-(Vector3f lhs, Vector3f rhs)
        {
            return new Vector3f(
                lhs.x - rhs.x,
                lhs.y - rhs.y,
                lhs.z - rhs.z);
        }

        public static Vector3f operator-(Vector3f a)
        {
            return new Vector3f(-a.x, -a.y, -a.z);
        }

        public static Vector3f operator*(Vector3f lhs, float rhs)
        {
            return new Vector3f(
                lhs.x * rhs,
                lhs.y * rhs,
                lhs.z * rhs);
        }

        public static Vector3f operator*(float lhs, Vector3f rhs)
        {
            return new Vector3f(
                rhs.x * lhs,
                rhs.y * lhs,
                rhs.z * lhs);
        }

        public static Vector3f operator/(Vector3f lhs, float rhs)
        {
            return new Vector3f(
                lhs.x / rhs,
                lhs.y / rhs,
                lhs.z / rhs);
        }

        public static bool operator==(Vector3f lhs, Vector3f rhs)
        {
            return (lhs.x == rhs.x) &&
                   (lhs.y == rhs.y) &&
                   (lhs.z == rhs.z);
        }

        public static bool operator!=(Vector3f lhs, Vector3f rhs)
        {
            return !(lhs == rhs);
        }

        public static implicit operator Vector3f(Vector2f v)
        {
            return new Vector3f(v.x, v.y, 0);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is Vector3f))
            {
                return false;
            }

            var f = (Vector3f)obj;
            return x == f.x &&
                   y == f.y &&
                   z == f.z;
        }

        public override int GetHashCode()
        {
            var hashCode = 373119288;
            hashCode = hashCode * -1521134295 + x.GetHashCode();
            hashCode = hashCode * -1521134295 + y.GetHashCode();
            hashCode = hashCode * -1521134295 + z.GetHashCode();
            return hashCode;
        }
    }
}
