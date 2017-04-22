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

#pragma once

#include <aeon/utility/listener_subject.h>
#include <aeon/input/input_keyboard_keys.h>
#include <aeon/input/input_mouse_buttons.h>
#include <aeon/input/input_listener.h>
#include <memory>

namespace aeon
{
namespace input
{

class input_handler : public utility::listener_subject<input_listener>
{
public:
    input_handler() = default;
    virtual ~input_handler() = default;

    void handle_keyboard_key_state_changed_event(const keyboard_key key, const keyboard_key_state key_state,
                                                 const int modifier);

    void handle_mouse_move_event(const float x, const float y);
    void handle_mouse_button_event(const mouse_button button, const mouse_button_state button_state);
    void handle_mouse_scroll_event(const float x, const float y);
};

} // namespace input
} // namespace aeon
