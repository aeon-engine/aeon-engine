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
using AeonEngineMono.Types;

namespace AeonEngineMono.Scene
{
    public enum FindMethod
    {
        Single = 0,
        Recursive = 1
    }

    public class SceneNode : MovableObject
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern SceneNode(string name);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void AttachChild(SceneNode node);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void DetachChild(SceneNode node);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void DetachAllChildren();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void AttachComponent(Component node);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void DetachComponent(Component node);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void DetachAllComponents();

        public extern Vector2F Center
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get; 
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern SceneNode[] GetChildren();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern Component[] GetAttachedComponents();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern SceneNode FindChildByName(string name, FindMethod findMethod = FindMethod.Recursive);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern Component FindComponentByName(string name, FindMethod findMethod = FindMethod.Recursive);
    }
}
