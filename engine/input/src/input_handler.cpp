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

#include <aeon/input/input_handler.h>

namespace aeon::input
{

input_handler::input_handler()
    : mouse_cursor_position_(0, 0)
    , mouse_button_states_(mouse_button_state::released)
    , keystates_(keyboard_key_state::released)
{
}

input_handler::~input_handler() = default;

void input_handler::handle_keyboard_key_state_changed_event(const keyboard_key key, const keyboard_key_state key_state,
                                                            const int modifier)
{
    keystates_.update_state(key, key_state);

    for (auto listener : listeners_)
    {
        listener->on_keyboard_key_state_changed_event(key, key_state, modifier);
    }
}

void input_handler::handle_mouse_move_event(const float x, const float y)
{
    mouse_cursor_position_ = math::vector2<float>{x, y};

    for (auto listener : listeners_)
    {
        listener->on_mouse_move_event(x, y);
    }
}

void input_handler::handle_mouse_button_event(const mouse_button button, const mouse_button_state button_state)
{
    mouse_button_states_.update_state(button, button_state);

    for (auto listener : listeners_)
    {
        listener->on_mouse_button_event(button, button_state, mouse_cursor_position_);
    }
}

void input_handler::handle_mouse_scroll_event(const float x, const float y)
{
    for (auto listener : listeners_)
    {
        listener->on_mouse_scroll_event(x, y);
    }
}

void input_handler::handle_end_of_frame()
{
    mouse_button_states_.reset_first_of_frame();
    keystates_.reset_first_of_frame();
}

auto input_handler::get_mouse_cursor_position() const -> math::vector2<float>
{
    return mouse_cursor_position_;
}

auto input_handler::get_mouse_button_state(const mouse_button button) const -> mouse_button_state
{
    return mouse_button_states_.get_state(button);
}

auto input_handler::get_key_state(const keyboard_key key) const -> keyboard_key_state
{
    return keystates_.get_state(key);
}

auto input_handler::is_any_mouse_button_down() const -> bool
{
    return mouse_button_states_.is_any_in_state(mouse_button_state::pressed);
}

auto input_handler::is_any_key_down() const -> bool
{
    return keystates_.is_any_in_state(keyboard_key_state::pressed);
}

auto input_handler::get_mouse_button_up(const mouse_button button) -> bool
{
    return mouse_button_states_.get_frame_state(button, mouse_button_state::released);
}

auto input_handler::get_mouse_button_down(const mouse_button button) -> bool
{
    return mouse_button_states_.get_frame_state(button, mouse_button_state::pressed);
}

auto input_handler::get_key_up(const keyboard_key key) -> bool
{
    return keystates_.get_frame_state(key, keyboard_key_state::released);
}

auto input_handler::get_key_down(const keyboard_key key) -> bool
{
    return keystates_.get_frame_state(key, keyboard_key_state::pressed);
}
} // namespace aeon::input
