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

using System.Collections.Generic;

namespace AeonEngineMono.Input
{
    internal class KeyBindingGroup
    {
        public void AddBind(KeyBinding binding)
        {
            _bindings.Add(binding);
        }

        public void ClearBinds()
        {
            _bindings.Clear();
        }

        public bool GetUp()
        {
            foreach (var bind in _bindings)
            {
                if (bind.GetUp())
                    return true;
            }

            return false;
        }

        public bool GetDown()
        {
            foreach (var bind in _bindings)
            {
                if (bind.GetDown())
                    return true;
            }

            return false;
        }

        public bool GetIsPressed()
        {
            foreach (var bind in _bindings)
            {
                if (bind.GetIsPressed())
                    return true;
            }

            return false;
        }

        private readonly List<KeyBinding> _bindings = new List<KeyBinding>();
    }
}
