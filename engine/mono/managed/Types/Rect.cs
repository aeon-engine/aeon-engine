﻿/*
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

namespace AeonEngineMono.Types
{
    public struct Rect
    {
        public float left { get; set; }
        public float top { get; set; }
        public float right { get; set; }
        public float bottom { get; set; }

        public Rect(float left, float top, float right, float bottom)
        {
            this.left = left;
            this.top = top;
            this.right = right;
            this.bottom = bottom;
        }

        public Rect(Vector2f position, Vector2f size)
        {
            this.left = position.x;
            this.top = position.y;
            this.right = position.x + size.x;
            this.bottom = position.y + size.y;
        }

        public static Rect Empty
        {
            get { return new Rect(0, 0, 0, 0); }
        }

        public static Rect One
        {
            get { return new Rect(0, 0, 1, 1); }
        }

        public float Width
        {
            get { return right - left; }
        }

        public float Height
        {
            get { return bottom - top; }
        }

        public Vector2f Position
        {
            get { return new Vector2f(left, top); }
        }

        public Vector2f Size
        {
            get { return new Vector2f(this.Width, this.Height); }
        }

        public bool IsEmpty()
        {
            return this.Width == 0 || this.Height == 0;
        }

        public override bool Equals(object obj)
        {
            if (!(obj is Rect))
            {
                return false;
            }

            var rect = (Rect)obj;
            return left == rect.left &&
                   top == rect.top &&
                   right == rect.right &&
                   bottom == rect.bottom;
        }

        public override int GetHashCode()
        {
            var hashCode = -971476797;
            hashCode = hashCode * -1521134295 + left.GetHashCode();
            hashCode = hashCode * -1521134295 + top.GetHashCode();
            hashCode = hashCode * -1521134295 + right.GetHashCode();
            hashCode = hashCode * -1521134295 + bottom.GetHashCode();
            return hashCode;
        }
    }
}
