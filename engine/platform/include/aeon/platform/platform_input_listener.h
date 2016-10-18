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

#pragma once

#include <aeon/platform/platform_keyboard_keys.h>
#include <aeon/platform/platform_mouse_buttons.h>

namespace aeon
{
namespace platform
{

class platform_window;
class platform_input_listener
{
public:
    platform_input_listener() = default;
    virtual ~platform_input_listener() = default;

    /*!
     * Called every time the state of a keyboard key changes.
     */
    virtual void on_keyboard_key_state_changed_event(keyboard_key /*key*/, keyboard_key_state /*key_state*/,
                                                     int /*modifier*/)
    {
    }

    /*!
     * Called whenever the mouse is moved. If mouse capturing is turned on, these values will keep
     * increasing/decreasing on movement.
     */
    virtual void on_mouse_move_event(float /*x*/, float /*y*/)
    {
    }

    /*!
     * Called whenever the state of a mouse button changes.
     */
    virtual void on_mouse_button_event(mouse_button /*button*/, mouse_button_state /*button_state*/)
    {
    }

    /*!
     * Called whenever the mouse is scrolled.
     */
    virtual void on_mouse_scroll_event(float /*x*/, float /*y*/)
    {
    }
};

} // namespace platform
} // namespace aeon
