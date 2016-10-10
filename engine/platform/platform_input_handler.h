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

#include <aeon/utility.h>
#include <platform/platform_keyboard_keys.h>
#include <platform/platform_mouse_buttons.h>
#include <platform/platform_input_listener.h>
#include <memory>

namespace aeon
{
namespace platform
{

class platform_window;
class platform_input_handler : public utility::listener_subject<platform_input_listener>
{
public:
    platform_input_handler() = default;
    virtual ~platform_input_handler() = default;

    void handle_keyboard_event(keyboard_key key, keyboard_key_state key_state, int modifier);

    void handle_mouse_move_event(float x, float y);
    void handle_mouse_button_event(mouse_button button, mouse_button_state button_state);
    void handle_mouse_scroll_event(float x, float y);
};

using platform_input_handler_ptr = std::unique_ptr<platform_input_handler>;

} // namespace platform
} // namespace aeon
