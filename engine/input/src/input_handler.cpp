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

#include <aeon/input/input_handler.h>

namespace aeon
{
namespace input
{

input_handler::input_handler()
    : mouse_cursor_position_(0, 0)
    , mouse_button_states_()
    , keystates_()
{
}

input_handler::~input_handler() = default;

void input_handler::handle_keyboard_key_state_changed_event(const keyboard_key key, const keyboard_key_state key_state,
                                                            const int modifier)
{
    keystates_[key] = key_state;

    for (auto listener : listeners_)
    {
        listener->on_keyboard_key_state_changed_event(key, key_state, modifier);
    }
}

void input_handler::handle_mouse_move_event(const float x, const float y)
{
    mouse_cursor_position_ = glm::vec2(x, y);

    for (auto listener : listeners_)
    {
        listener->on_mouse_move_event(x, y);
    }
}

void input_handler::handle_mouse_button_event(const mouse_button button, const mouse_button_state button_state)
{
    mouse_button_states_[button] = button_state;

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

auto input_handler::get_mouse_cursor_position() const -> glm::vec2
{
    return mouse_cursor_position_;
}

auto input_handler::get_mouse_button_state(const mouse_button button) const -> mouse_button_state
{
    auto result = mouse_button_states_.find(button);

    if (result == mouse_button_states_.end())
        return mouse_button_state::released;

    return result->second;
}

auto input_handler::get_keystate(const keyboard_key key) const -> keyboard_key_state
{
    auto result = keystates_.find(key);

    if (result == keystates_.end())
        return keyboard_key_state::released;

    return result->second;
}

auto input_handler::is_any_mouse_button_down() const -> bool
{
    for (auto buttonstate : mouse_button_states_)
    {
        if (buttonstate.second == mouse_button_state::pressed)
            return true;
    }

    return false;
}

auto input_handler::is_any_key_down() const -> bool
{
    for (auto keystate : keystates_)
    {
        if (keystate.second == keyboard_key_state::pressed)
            return true;
    }

    return false;
}

} // namespace input
} // namespace aeon
