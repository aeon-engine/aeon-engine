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

#pragma once

#include <aeon/input/input_keyboard_keys.h>
#include <aeon/input/input_mouse_buttons.h>
#include <aeon/math/vector2.h>

namespace aeon
{
namespace input
{

class input_listener
{
public:
    input_listener() = default;
    virtual ~input_listener() = default;

    /*!
     * Called every time the state of a keyboard key changes. The modifier can be any or multiple of
     * the modifiers in keyboard_modifier_key.
     * \see keyboard_modifier_key::keyboard_modifier_key_enum
     */
    virtual void on_keyboard_key_state_changed_event(const keyboard_key /*key*/, const keyboard_key_state /*key_state*/,
                                                     const int /*modifier*/)
    {
    }

    /*!
     * Called whenever the mouse is moved. If mouse capturing is turned on, these values will keep
     * increasing/decreasing on movement.
     */
    virtual void on_mouse_move_event(const float /*x*/, const float /*y*/)
    {
    }

    /*!
     * Called whenever the state of a mouse button changes.
     */
    virtual void on_mouse_button_event(const mouse_button /*button*/, const mouse_button_state /*button_state*/,
                                       const math::vector2<float> position)
    {
    }

    /*!
     * Called whenever the mouse is scrolled.
     */
    virtual void on_mouse_scroll_event(const float /*x*/, const float /*y*/)
    {
    }
};

} // namespace input
} // namespace aeon
