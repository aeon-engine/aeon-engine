/*
 * Copyright (c) 2012-2018 Robin Degen
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
                                aeon_mono_auto_wrap(viewport::create_internal));
    mono_jit::add_internal_call(
        "AeonEngineMono.Gfx.Viewport::CreateInternal(AeonEngineMono.Scene.Camera,AeonEngineMono.Types.Rect,string,int)",
        aeon_mono_auto_wrap(viewport::create_internal2));

    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::set_ZOrder(int)",
                                aeon_mono_auto_wrap(viewport::set_zorder));
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::get_ZOrder", aeon_mono_auto_wrap(viewport::get_zorder));
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::SetCameraInternal(AeonEngineMono.Scene.Camera)",
                                aeon_mono_auto_wrap(viewport::set_camera_internal));
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::SetRectangleInternal(AeonEngineMono.Types.Rect)",
                                aeon_mono_auto_wrap(viewport::set_rectangle_internal));
}

void viewport::create_internal(MonoObject *this_ptr, std::shared_ptr<scene::camera> camera, std::string name,
                               int zOrder)
{
    auto &main_window = mono_jit_manager::get_application().get_main_window();

    auto viewport = main_window.create_viewport(camera, name, zOrder);
    mono_object_wrapper<std::shared_ptr<gfx::viewport>>::create(this_ptr, viewport);
}

void viewport::create_internal2(MonoObject *this_ptr, std::shared_ptr<scene::camera> camera,
                                common::types::rectangle<float> rectangle, std::string name, int zOrder)
{
    auto &main_window = mono_jit_manager::get_application().get_main_window();

    auto viewport = main_window.create_viewport(camera, rectangle, name, zOrder);
    mono_object_wrapper<std::shared_ptr<gfx::viewport>>::create(this_ptr, viewport);
}

void viewport::set_zorder(std::shared_ptr<gfx::viewport> this_ptr, int value)
{
    this_ptr->set_zorder(value);
}

int viewport::get_zorder(std::shared_ptr<gfx::viewport> this_ptr)
{
    return this_ptr->get_zorder();
}

void viewport::set_camera_internal(std::shared_ptr<gfx::viewport> this_ptr, std::shared_ptr<scene::camera> camera)
{
    this_ptr->set_camera(camera);
}

void viewport::set_rectangle_internal(std::shared_ptr<gfx::viewport> this_ptr,
                                      common::types::rectangle<float> rectangle)
{
    this_ptr->set_rectangle(rectangle);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
