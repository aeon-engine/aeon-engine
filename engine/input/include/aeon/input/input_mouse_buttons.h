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

#include <cstdint>
#include <cstddef>

namespace aeon
{
namespace input
{

enum class mouse_button_state : std::uint32_t
{
    released = 0,
    pressed = 1
};

enum class mouse_button : std::uint32_t
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

static constexpr auto mouse_button_count = static_cast<std::size_t>(mouse_button::mouse_button_last) + 1;

} // namespace input
} // namespace aeon
