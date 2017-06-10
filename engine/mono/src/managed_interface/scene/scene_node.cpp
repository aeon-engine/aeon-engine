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
#include <managed_interface/core/types_conversion.h>
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
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetIdentity", &scene_node::set_identity);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::set_Position(AeonEngineMono.Types.Vector3f)",
                                &scene_node::set_position);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::get_Position", &scene_node::get_position);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Translate(AeonEngineMono.Types.Vector3f)",
                                &scene_node::translate);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetRotation(AeonEngineMono.Types.Vector3f)",
                                &scene_node::set_rotation_vec);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetRotation(single)",
                                &scene_node::set_rotation_angle);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetRotation(AeonEngineMono.Types.Quaternion)",
                                &scene_node::set_rotation_quat);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Rotate(AeonEngineMono.Types.Vector3f)",
                                &scene_node::rotate_vec);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Rotate(single)", &scene_node::rotate_angle);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Rotate(AeonEngineMono.Types.Quaternion)",
                                &scene_node::rotate_quat);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetScale(AeonEngineMono.Types.Vector3f)",
                                &scene_node::set_scale);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Scale(AeonEngineMono.Types.Vector3f)",
                                &scene_node::scale);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::get_Matrix", &scene_node::get_matrix);
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::set_Matrix(AeonEngineMono.Types.Matrix4)",
                                &scene_node::set_matrix);
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

void scene_node::set_identity(MonoObject *this_ptr)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->set_identity();
}

void scene_node::set_position(MonoObject *this_ptr, vector3f position)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->set_position({position.x, position.y, position.z});
}

auto scene_node::get_position(MonoObject *this_ptr) -> vector3f
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    auto position = this_scene_node->get_position();
    return {position.x, position.y, position.z};
}

void scene_node::translate(MonoObject *this_ptr, vector3f vec)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->translate(converter::convert(vec));
}

void scene_node::set_rotation_vec(MonoObject *this_ptr, vector3f vec)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->set_rotation(converter::convert(vec));
}

void scene_node::set_rotation_angle(MonoObject *this_ptr, float angle)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->set_rotation(angle);
}

void scene_node::set_rotation_quat(MonoObject *this_ptr, quaternion quat)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->set_rotation(converter::convert(quat));
}

void scene_node::rotate_vec(MonoObject *this_ptr, vector3f vec)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->rotate(converter::convert(vec));
}

void scene_node::rotate_angle(MonoObject *this_ptr, float angle)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->rotate(angle);
}

void scene_node::rotate_quat(MonoObject *this_ptr, quaternion quat)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->rotate(converter::convert(quat));
}

void scene_node::set_scale(MonoObject *this_ptr, vector3f vec)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->set_scale(converter::convert(vec));
}

void scene_node::scale(MonoObject *this_ptr, vector3f vec)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->scale(converter::convert(vec));
}

void scene_node::set_matrix(MonoObject *this_ptr, matrix4x4 mat)
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    this_scene_node->set_matrix(converter::convert(mat));
}

auto scene_node::get_matrix(MonoObject *this_ptr) -> matrix4x4
{
    auto this_scene_node = get_scene_node_from_mono_object(this_ptr);
    return converter::convert(this_scene_node->get_matrix());
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
