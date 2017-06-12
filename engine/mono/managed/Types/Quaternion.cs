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

using AeonEngineMono.Core;

namespace AeonEngineMono.Types
{
    public struct Quaternion
    {
        public float w;
        public float x;
        public float y;
        public float z;

        public Quaternion(float w, float x, float y, float z)
        {
            this.w = w;
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public Quaternion(Vector3f eulerAngles)
        {
            var c = Mathf.Cos(eulerAngles * 0.5f);
            var s = Mathf.Sin(eulerAngles * 0.5f);

            this.w = c.x * c.y * c.z + s.x * s.y * s.z;
            this.x = s.x * c.y * c.z - c.x * s.y * s.z;
            this.y = c.x * s.y * c.z + s.x * c.y * s.z;
            this.z = c.x * c.y * s.z - s.x * s.y * c.z;
        }

        public Vector3f Euler
        {
            get { return new Vector3f(this.Pitch, this.Yaw, this.Roll); }
        }

        public float Pitch
        {
            get
            {
                return Mathf.Atan2(2f * (this.y * this.z + this.w * this.x), this.w * this.w - this.x * this.x - this.y * this.y + this.z * this.z);
            }
        }

        public float Roll
        {
            get
            {
                return Mathf.Atan2(2f * (this.x * this.y + this.w * this.z), this.w * this.w + this.x * this.x - this.y * this.y - this.z * this.z);
            }
        }

        public float Yaw
        {
            get { return Mathf.Asin(Mathf.Clamp(-2f * (this.x * this.z - this.w * this.y), -1f, 1f)); }
        }
    }
}
