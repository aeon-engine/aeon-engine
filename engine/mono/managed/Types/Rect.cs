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

namespace AeonEngineMono.Types
{
    public struct Rect
    {
        public float Left;
        public float Top;
        public float Right;
        public float Bottom;

        public Rect(float left, float top, float right, float bottom)
        {
            Left = left;
            Top = top;
            Right = right;
            Bottom = bottom;
        }

        public Rect(Vector2F position, Vector2F size)
        {
            Left = position.X;
            Top = position.Y;
            Right = position.X + size.X;
            Bottom = position.Y + size.Y;
        }

        public static Rect Empty => new Rect(0, 0, 0, 0);
        public static Rect One => new Rect(0, 0, 1, 1);

        public float Width => Right - Left;
        public float Height => Bottom - Top;
        public Vector2F Position => new Vector2F(Left, Top);
        public Vector2F Size => new Vector2F(Width, Height);

        public bool IsEmpty()
        {
            return Width == 0 || Height == 0;
        }
    }
}
