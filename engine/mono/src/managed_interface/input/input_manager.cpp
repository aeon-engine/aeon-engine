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

#include <managed_interface/input/input_manager.h>
#include <managed_interface/core/types_conversion.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_jit_manager.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void input_manager::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::GetMouseCursorPosition",
                                aeon_mono_auto_wrap(input_manager::get_mouse_cursor_position));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::GetMouseButtonState(AeonEngineMono.Input.MouseButton)",
                                aeon_mono_auto_wrap(input_manager::get_mouse_button_state));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::GetKeystate(AeonEngineMono.Input.KeyboardKey)",
                                aeon_mono_auto_wrap(input_manager::get_key_state));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::IsAnyKeyDown",
                                aeon_mono_auto_wrap(input_manager::is_any_key_down));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::IsAnyMouseButtonDown",
                                aeon_mono_auto_wrap(input_manager::is_any_mouse_button_down));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::GetMouseButtonUp(AeonEngineMono.Input.MouseButton)",
                                aeon_mono_auto_wrap(input_manager::get_mouse_button_up));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::GetMouseButtonDown(AeonEngineMono.Input.MouseButton)",
                                aeon_mono_auto_wrap(input_manager::get_mouse_button_down));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::GetKeyUp(AeonEngineMono.Input.KeyboardKey)",
                                aeon_mono_auto_wrap(input_manager::get_key_up));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::GetKeyDown(AeonEngineMono.Input.KeyboardKey)",
                                aeon_mono_auto_wrap(input_manager::get_key_down));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::set_CursorMode(AeonEngineMono.Input.MouseCursorMode)",
                                aeon_mono_auto_wrap(input_manager::set_cursor_mode));
    mono_jit::add_internal_call("AeonEngineMono.Input.Input::get_CursorMode",
                                aeon_mono_auto_wrap(input_manager::get_cursor_mode));
}

auto input_manager::get_mouse_cursor_position() -> glm::vec2
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.get_mouse_cursor_position();
}

auto input_manager::get_mouse_button_state(input::mouse_button button) -> input::mouse_button_state
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.get_mouse_button_state(button);
}

auto input_manager::get_key_state(input::keyboard_key key) -> input::keyboard_key_state
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.get_key_state(key);
}

auto input_manager::is_any_key_down() -> bool
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.is_any_key_down();
}

auto input_manager::is_any_mouse_button_down() -> bool
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.is_any_mouse_button_down();
}

auto input_manager::get_mouse_button_up(input::mouse_button button) -> bool
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.get_mouse_button_up(button);
}

auto input_manager::get_mouse_button_down(input::mouse_button button) -> bool
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.get_mouse_button_down(button);
}

auto input_manager::get_key_up(input::keyboard_key key) -> bool
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.get_key_up(key);
}

auto input_manager::get_key_down(input::keyboard_key key) -> bool
{
    auto &input_handler = mono_jit_manager::get_application().get_input_handler();
    return input_handler.get_key_down(key);
}

void input_manager::set_cursor_mode(platform::mouse_cursor_mode mode)
{
    auto &window = mono_jit_manager::get_application().get_main_window();
    window.set_mouse_cursor_mode(mode);
}

auto input_manager::get_cursor_mode() -> platform::mouse_cursor_mode
{
    auto &window = mono_jit_manager::get_application().get_main_window();
    return window.get_mouse_cursor_mode();
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
