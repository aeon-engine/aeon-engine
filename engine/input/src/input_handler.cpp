/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/input/input_handler.h>

namespace aeon
{
namespace input
{

void input_handler::handle_keyboard_key_state_changed_event(keyboard_key key, keyboard_key_state key_state,
                                                            int modifier)
{
    for (auto listener : listeners_)
    {
        listener->on_keyboard_key_state_changed_event(key, key_state, modifier);
    }
}

void input_handler::handle_mouse_move_event(float x, float y)
{
    for (auto listener : listeners_)
    {
        listener->on_mouse_move_event(x, y);
    }
}

void input_handler::handle_mouse_button_event(mouse_button button, mouse_button_state button_state)
{
    for (auto listener : listeners_)
    {
        listener->on_mouse_button_event(button, button_state);
    }
}

void input_handler::handle_mouse_scroll_event(float x, float y)
{
    for (auto listener : listeners_)
    {
        listener->on_mouse_scroll_event(x, y);
    }
}

} // namespace input
} // namespace aeon
