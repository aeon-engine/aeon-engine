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

#include <managed_interface/scene/perspective_camera.h>
#include <managed_interface/mono_object_wrapper.h>
#include <aeon/scene/components/perspective_camera.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_string.h>
#include <aeon/mono/mono_jit_manager.h>
#include <memory>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void perspective_camera::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Scene.PerspectiveCamera::.ctor(single,single,single,single,string)",
                                aeon_mono_auto_wrap(perspective_camera::ctor));
    mono_jit::add_internal_call(
        "AeonEngineMono.Scene.PerspectiveCamera::.ctor(single,single,single,single,single,string)",
        aeon_mono_auto_wrap(perspective_camera::ctor2));
}

void perspective_camera::ctor(MonoObject *this_ptr, float fovY, float aspectRatio, float near, float far,
                              std::string name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto camera = std::make_shared<scene::perspective_camera>(scene_manager, fovY, aspectRatio, near, far, name);
    mono_object_wrapper<std::shared_ptr<scene::camera>>::create(this_ptr, camera);
}

void perspective_camera::ctor2(MonoObject *this_ptr, float fov, float width, float height, float near, float far,
                               std::string name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto camera = std::make_shared<scene::perspective_camera>(scene_manager, fov, width, height, near, far, name);
    mono_object_wrapper<std::shared_ptr<scene::camera>>::create(this_ptr, camera);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
