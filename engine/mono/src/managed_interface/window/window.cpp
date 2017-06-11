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

#include <managed_interface/window/window.h>
#include <managed_interface/core/types_conversion.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_jit_manager.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void window::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Window.Window::get_Size", &window::get_size);
    mono_jit::add_internal_call("AeonEngineMono.Window.Window::get_FramebufferSize", &window::get_framebuffer_size);
    mono_jit::add_internal_call("AeonEngineMono.Window.Window::get_Title", &window::get_title);
}

auto window::get_size() -> vector2f
{
    auto &window = mono_jit_manager::get_application().get_main_window();
    return converter::convert(window.get_size());
}

auto window::get_framebuffer_size() -> vector2f
{
    auto &window = mono_jit_manager::get_application().get_main_window();
    return converter::convert(window.get_framebuffer_size());
}

auto window::get_title() -> MonoString *
{
    auto &window = mono_jit_manager::get_application().get_main_window();
    return mono_jit_manager::engine_assembly.new_string(window.get_title()).get_mono_string();
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
