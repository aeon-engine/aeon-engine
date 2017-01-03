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

#include <aeon/input/input_keyboard_keys.h>
#include <aeon/input/input_mouse_buttons.h>

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
    virtual void on_mouse_button_event(const mouse_button /*button*/, const mouse_button_state /*button_state*/)
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
