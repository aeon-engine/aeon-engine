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

#include <managed_interface/scene/component.h>
#include <managed_interface/mono_object_wrapper.h>
#include <aeon/mono/mono_string.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void component::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Scene.Component::get_Name", &component::get_name);
    mono_jit::add_internal_call("AeonEngineMono.Scene.Component::get_SceneMatrix", &component::get_scene_matrix);
}

auto component::get_component_from_mono_object(MonoObject *object) -> std::shared_ptr<scene::component>
{
    return mono_object_wrapper<std::shared_ptr<scene::component>>::get_native_object(object);
}

auto component::get_name(MonoObject *this_ptr) -> MonoString *
{
    auto component = get_component_from_mono_object(this_ptr);
    auto mono_str = mono_jit_manager::engine_assembly.new_string(component->get_name());
    return mono_str.get_mono_string();
}

auto component::get_scene_matrix(MonoObject *this_ptr) -> matrix4x4
{
    auto component = get_component_from_mono_object(this_ptr);
    auto m = component->get_scene_matrix();
    return {m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]};
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
