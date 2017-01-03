/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#pragma once

#include <aeon/utility.h>
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
