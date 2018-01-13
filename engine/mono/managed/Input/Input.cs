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

using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using AeonEngineMono.Types;

namespace AeonEngineMono.Input
{
    public static class Input
    {
        private static readonly Dictionary<string, KeyBindingGroup> ButtonKeyBindings = new Dictionary<string, KeyBindingGroup>();

        private static void CreateBindGroupIfNeeded(string button)
        {
            if (!ButtonKeyBindings.ContainsKey(button))
                ButtonKeyBindings[button] = new KeyBindingGroup();
        }

        public static void BindButton(string button, KeyboardKey key)
        {
            CreateBindGroupIfNeeded(button);
            ButtonKeyBindings[button].AddBind(new KeyboardKeyBinding(key));
        }

        public static void BindButton(string button, MouseButton mouseButton)
        {
            CreateBindGroupIfNeeded(button);
            ButtonKeyBindings[button].AddBind(new MouseKeyBinding(mouseButton));
        }

        public static bool GetButtonUp(string button)
        {
            return ButtonKeyBindings[button].GetUp();
        }

        public static bool GetButtonDown(string button)
        {
            return ButtonKeyBindings[button].GetDown();
        }

        public static bool GetButtonState(string button)
        {
            return ButtonKeyBindings[button].GetIsPressed();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Vector2f GetMouseCursorPosition();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern MouseButtonState GetMouseButtonState(MouseButton button);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern KeyboardKeyState GetKeystate(KeyboardKey key);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool IsAnyKeyDown();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool IsAnyMouseButtonDown();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool GetMouseButtonUp(MouseButton button);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool GetMouseButtonDown(MouseButton button);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool GetKeyUp(KeyboardKey key);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool GetKeyDown(KeyboardKey key);

        public static extern MouseCursorMode CursorMode
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;

            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
    }
}
