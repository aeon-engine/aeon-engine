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

#include <managed_interface/scene/scene_node.h>
#include <managed_interface/scene/component.h>
#include <managed_interface/mono_object_wrapper.h>
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

void scene_node::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Scene.SceneNode::.ctor(string)", &scene_node::ctor);
    mono_jit::add_internal_call("AeonEngineMono.Scene.SceneNode::AttachChild(AeonEngineMono.Scene.SceneNode)",
                                &scene_node::attach_child);
    mono_jit::add_internal_call("AeonEngineMono.Scene.SceneNode::AttachComponent(AeonEngineMono.Scene.Component)",
                                &scene_node::attach_component);
    // TODO: should be handled and called on baseclass
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::set_Position(AeonEngineMono.Types.Vector3F)",
                                &scene_node::set_position);
}

auto scene_node::get_scene_node_from_mono_object(MonoObject *object) -> std::shared_ptr<scene::scene_node>
{
    return mono_object_wrapper<std::shared_ptr<scene::scene_node>>::get_native_object(object);
}

void scene_node::ctor(MonoObject *this_ptr, MonoString *name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto scene_node = scene_manager.create_detached_scene_node(mono_string(name).str());

    mono_object_wrapper<std::shared_ptr<scene::scene_node>>::create(this_ptr, scene_node);
}

void scene_node::attach_child(MonoObject *this_ptr, MonoObject *child)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    auto child_scene_node = get_scene_node_from_mono_object(child);

    this_scene_node->attach_child(child_scene_node);
}

void scene_node::attach_component(MonoObject *this_ptr, MonoObject *component)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    auto component_ptr = component::get_component_from_mono_object(component);
    this_scene_node->attach_component(component_ptr);
}

void scene_node::set_position(MonoObject *this_ptr, vector3f position)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->set_position({position.x, position.y, position.z});
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
