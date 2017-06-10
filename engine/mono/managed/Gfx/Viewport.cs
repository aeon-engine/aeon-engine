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

using System.Runtime.CompilerServices;
using AeonEngineMono.Core;
using AeonEngineMono.Scene;
using AeonEngineMono.Types;

namespace AeonEngineMono.Gfx
{
    public class Viewport : Object
    {
        public Viewport(Camera camera, string name, int zOrder = 0)
        {
            _camera = camera;
            _rectangle = Rect.One;
            _name = name;
            CreateInternal(camera, name, zOrder);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void CreateInternal(Camera camera, string name, int zOrder);

        public Viewport(Camera camera, Rect rectangle, string name, int zOrder = 0)
        {
            _camera = camera;
            _rectangle = rectangle;
            _name = name;
            CreateInternal(camera, rectangle, name, zOrder);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void CreateInternal(Camera camera, Rect rectangle, string name, int zOrder);

        public extern int ZOrder
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;

            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public Camera Camera
        {
            get => _camera;
            set
            {
                _camera = value;
                SetCameraInternal(_camera);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetCameraInternal(Camera camera);

        public Rect Rectangle
        {
            get => _rectangle;
            set
            {
                _rectangle = value;
                SetRectangleInternal(_rectangle);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetRectangleInternal(Rect rectangle);

        public string Name => _name;

        private Camera _camera;
        private Rect _rectangle;
        private string _name;
    }
}
