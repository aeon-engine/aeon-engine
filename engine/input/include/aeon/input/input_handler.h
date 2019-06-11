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

#include <aeon/input/input_state.h>
#include <aeon/input/input_keyboard_keys.h>
#include <aeon/input/input_mouse_buttons.h>
#include <aeon/input/input_listener.h>
#include <aeon/common/listener_subject.h>
#include <aeon/math/vector2.h>
#include <array>

namespace aeon::input
{

class input_handler : public common::listener_subject<input_listener>
{
public:
    input_handler();
    virtual ~input_handler();

    void handle_keyboard_key_state_changed_event(const keyboard_key key, const keyboard_key_state key_state,
                                                 const int modifier);

    void handle_mouse_move_event(const float x, const float y);
    void handle_mouse_button_event(const mouse_button button, const mouse_button_state button_state);
    void handle_mouse_scroll_event(const float x, const float y);
    void handle_end_of_frame();

    auto get_mouse_cursor_position() const -> math::vector2<float>;
    auto get_mouse_button_state(const mouse_button button) const -> mouse_button_state;
    auto get_key_state(const keyboard_key key) const -> keyboard_key_state;

    auto is_any_mouse_button_down() const -> bool;
    auto is_any_key_down() const -> bool;

    auto get_mouse_button_up(const mouse_button button) -> bool;
    auto get_mouse_button_down(const mouse_button button) -> bool;

    auto get_key_up(const keyboard_key key) -> bool;
    auto get_key_down(const keyboard_key key) -> bool;

private:
    math::vector2<float> mouse_cursor_position_;
    input_state<mouse_button, mouse_button_state, mouse_button_count> mouse_button_states_;
    input_state<keyboard_key, keyboard_key_state, keyboard_key_count> keystates_;
};

} // namespace aeon::input
