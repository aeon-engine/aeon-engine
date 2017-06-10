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

#include <managed_interface/gfx/viewport.h>
#include <managed_interface/core/types.h>
#include <managed_interface/mono_object_wrapper.h>
#include <managed_interface/scene/camera.h>
#include <managed_interface/core/types_conversion.h>
#include <aeon/mono/mono_jit_manager.h>
#include <aeon/mono/mono_string.h>
#include <aeon/mono/mono_jit.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void viewport::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::CreateInternal(AeonEngineMono.Scene.Camera,string,int)",
                                &viewport::create_internal);
    mono_jit::add_internal_call(
        "AeonEngineMono.Gfx.Viewport::CreateInternal(AeonEngineMono.Scene.Camera,AeonEngineMono.Types.Rect,string,int)",
        &viewport::create_internal2);

    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::set_ZOrder(int)", &viewport::set_zorder);
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::get_ZOrder", &viewport::get_zorder);
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::SetCameraInternal(AeonEngineMono.Scene.Camera)",
                                &viewport::set_camera_internal);
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::SetRectangleInternal(AeonEngineMono.Types.Rect)",
                                &viewport::set_rectangle_internal);
}

auto viewport::get_viewport_from_mono_object(MonoObject *object) -> std::shared_ptr<gfx::viewport>
{
    return mono_object_wrapper<std::shared_ptr<gfx::viewport>>::get_native_object(object);
}

void viewport::create_internal(MonoObject *this_ptr, MonoObject *camera, MonoString *name, int zOrder)
{
    auto camera_ptr = camera::get_camera_from_mono_object(camera);
    auto &main_window = mono_jit_manager::get_application().get_main_window();

    auto viewport = main_window.create_viewport(camera_ptr, mono_string(name).str(), zOrder);
    mono_object_wrapper<std::shared_ptr<gfx::viewport>>::create(this_ptr, viewport);
}

void viewport::create_internal2(MonoObject *this_ptr, MonoObject *camera, rect rectangle, MonoString *name, int zOrder)
{
    auto camera_ptr = camera::get_camera_from_mono_object(camera);
    auto &main_window = mono_jit_manager::get_application().get_main_window();

    auto viewport =
        main_window.create_viewport(camera_ptr, converter::convert(rectangle), mono_string(name).str(), zOrder);
    mono_object_wrapper<std::shared_ptr<gfx::viewport>>::create(this_ptr, viewport);
}

void viewport::set_zorder(MonoObject *this_ptr, int value)
{
    auto viewport = get_viewport_from_mono_object(this_ptr);
    viewport->set_zorder(value);
}

int viewport::get_zorder(MonoObject *this_ptr)
{
    auto viewport = get_viewport_from_mono_object(this_ptr);
    return viewport->get_zorder();
}

void viewport::set_camera_internal(MonoObject *this_ptr, MonoObject *camera)
{
    auto camera_ptr = camera::get_camera_from_mono_object(camera);
    auto viewport = get_viewport_from_mono_object(this_ptr);
    viewport->set_camera(camera_ptr);
}

void viewport::set_rectangle_internal(MonoObject *this_ptr, rect rectangle)
{
    auto viewport = get_viewport_from_mono_object(this_ptr);
    viewport->set_rectangle(converter::convert(rectangle));
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
