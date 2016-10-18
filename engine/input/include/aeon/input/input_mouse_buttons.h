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

namespace aeon
{
namespace input
{

enum class mouse_button_state
{
    released = 0,
    pressed = 1
};

enum class mouse_button
{
    mouse_button_1 = 0,
    mouse_button_2 = 1,
    mouse_button_3 = 2,
    mouse_button_4 = 3,
    mouse_button_5 = 4,
    mouse_button_6 = 5,
    mouse_button_7 = 6,
    mouse_button_8 = 7,
    mouse_button_last = mouse_button_8,
    mouse_button_left = mouse_button_1,
    mouse_button_right = mouse_button_2,
    mouse_button_middle = mouse_button_3
};

} // namespace input
} // namespace aeon
