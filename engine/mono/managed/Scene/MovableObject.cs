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

using System.Runtime.CompilerServices;
using AeonEngineMono.Core;
using AeonEngineMono.Types;

namespace AeonEngineMono.Scene
{
    public abstract class MovableObject : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetIdentity();

        public void SetPosition(float x, float y, float z = 0)
        {
            Position = new Vector3f(x, y, z);
        }

        public extern Vector3f Position
        { 
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;

            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public void Translate(float x, float y, float z = 0)
        {
            Translate(new Vector3f(x, y, z));
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Translate(Vector3f vec);

        public void SetRotation(float x, float y, float z)
        {
            SetRotation(new Vector3f(x, y, z));
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetRotation(Vector3f vec);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetRotation(float angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetRotation(Quaternion quat);

        public void Rotate(float x, float y, float z)
        {
            Rotate(new Vector3f(x, y, z));
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Rotate(Vector3f vec);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Rotate(float angle);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Rotate(Quaternion quat);

        public void SetScale(float x, float y, float z)
        {
            SetScale(new Vector3f(x, y, z));
        }

        public void SetScale(float xyz)
        {
            SetScale(new Vector3f(xyz));
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetScale(Vector3f vec);

        public void Scale(float x, float y, float z)
        {
            Scale(new Vector3f(x, y, z));
        }

        public void Scale(float xyz)
        {
            Scale(new Vector3f(xyz));
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Scale(Vector3f vec);

        public extern Matrix4 Matrix
        { 
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;

            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
