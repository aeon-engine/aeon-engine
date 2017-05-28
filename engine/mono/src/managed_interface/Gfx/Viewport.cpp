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

#include <managed_interface/gfx/Viewport.h>
#include <managed_interface/Scene/Camera.h>
#include <managed_interface/core/Types.h>
#include <aeon/mono/mono_jit_manager.h>
#include <aeon/mono/mono_string.h>
#include <aeon/mono/mono_jit.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

static void Viewport_CreateInternal(MonoObject *this_ptr, MonoObject *camera, MonoString *name, int zOrder)
{
    auto camera_ptr = Object::get_managed_object_as<Camera>(camera).camera;
    auto &main_window = mono_jit_manager::get_application().get_main_window();
    auto viewport = main_window.create_viewport(camera_ptr, mono_string(name).str(), zOrder);

    std::make_unique<Viewport>(this_ptr, viewport).release();
}

static void Viewport_CreateInternal2(MonoObject *this_ptr, MonoObject *camera, Rect rectangle, MonoString *name,
                                     int zOrder)
{
    auto camera_ptr = Object::get_managed_object_as<Camera>(camera).camera;
    auto &main_window = mono_jit_manager::get_application().get_main_window();
    auto viewport =
        main_window.create_viewport(camera_ptr, {rectangle.left, rectangle.top, rectangle.right, rectangle.bottom},
                                    mono_string(name).str(), zOrder);

    std::make_unique<Viewport>(this_ptr, viewport).release();
}

static void Viewport_set_ZOrder(MonoObject *this_ptr, int value)
{
    // Object::get_managed_object_as<Sprite>(this_ptr).set_Size({value.x, value.y});
}

static int Viewport_get_ZOrder(MonoObject *this_ptr)
{
    return 0;
}

static void Viewport_set_Camera(MonoObject *this_ptr, MonoObject *camera)
{
    // Object::get_managed_object_as<Sprite>(this_ptr).set_Size({value.x, value.y});
}

static void Viewport_set_Rectangle(MonoObject *this_ptr, Rect rectangle)
{
    // Object::get_managed_object_as<Sprite>(this_ptr).set_Size({value.x, value.y});
}

void Viewport::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::CreateInternal(AeonEngineMono.Scene.Camera,string,int)",
                                Viewport_CreateInternal);
    mono_jit::add_internal_call(
        "AeonEngineMono.Gfx.Viewport::CreateInternal(AeonEngineMono.Scene.Camera,AeonEngineMono.Types.Rect,string,int)",
        Viewport_CreateInternal2);

    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::set_ZOrder(int)", Viewport_set_ZOrder);
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::get_ZOrder", Viewport_get_ZOrder);
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::set_Camera(AeonEngineMono.Scene.Camera)",
                                Viewport_set_Camera);
    mono_jit::add_internal_call("AeonEngineMono.Gfx.Viewport::set_Rectangle(AeonEngineMono.Types.Rect)",
                                Viewport_set_Rectangle);
}

Viewport::Viewport(MonoObject *object, std::shared_ptr<gfx::viewport> viewport)
    : Object(object)
{
}

Viewport::~Viewport() = default;

} // namespace managed_interface
} // namespace mono
} // namespace aeon
