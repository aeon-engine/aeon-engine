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

#include <managed_interface/Scene/OrthographicCamera.h>
#include <aeon/scene/orthographic_camera.h>
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

static void OrthographicCamera_Ctor(MonoObject *this_ptr, float left, float right, float bottom, float top,
                                    MonoString *name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto camera =
        std::make_shared<scene::orthographic_camera>(scene_manager, left, right, bottom, top, mono_string(name).str());
    std::make_unique<OrthographicCamera>(this_ptr, camera).release();
}

static void OrthographicCamera_Ctor2(MonoObject *this_ptr, float left, float right, float bottom, float top, float near,
                                     float far, MonoString *name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto camera = std::make_shared<scene::orthographic_camera>(scene_manager, left, right, bottom, top, near, far,
                                                               mono_string(name).str());
    std::make_unique<OrthographicCamera>(this_ptr, camera).release();
}

static void OrthographicCamera_Ctor3(MonoObject *this_ptr, int left, int right, int bottom, int top, MonoString *name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto camera =
        std::make_shared<scene::orthographic_camera>(scene_manager, left, right, bottom, top, mono_string(name).str());
    std::make_unique<OrthographicCamera>(this_ptr, camera).release();
}

static void OrthographicCamera_Ctor4(MonoObject *this_ptr, int left, int right, int bottom, int top, float near,
                                     float far, MonoString *name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto camera = std::make_shared<scene::orthographic_camera>(scene_manager, left, right, bottom, top, near, far,
                                                               mono_string(name).str());
    std::make_unique<OrthographicCamera>(this_ptr, camera).release();
}

void OrthographicCamera::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Scene.OrthographicCamera::.ctor(float,float,float,float,string)",
                                OrthographicCamera_Ctor);
    mono_jit::add_internal_call(
        "AeonEngineMono.Scene.OrthographicCamera::.ctor(float,float,float,float,float,float,string)",
        OrthographicCamera_Ctor2);
    mono_jit::add_internal_call("AeonEngineMono.Scene.OrthographicCamera::.ctor(int,int,int,int,string)",
                                OrthographicCamera_Ctor3);
    mono_jit::add_internal_call("AeonEngineMono.Scene.OrthographicCamera::.ctor(int,int,int,int,float,float,string)",
                                OrthographicCamera_Ctor4);
}

OrthographicCamera::OrthographicCamera(MonoObject *object, std::shared_ptr<scene::camera> camera)
    : Camera(object, camera)
{
}

OrthographicCamera::~OrthographicCamera() = default;

} // namespace managed_interface
} // namespace mono
} // namespace aeon
