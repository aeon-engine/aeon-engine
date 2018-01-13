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
    mono_jit::add_internal_call("AeonEngineMono.Scene.SceneNode::.ctor(string)", aeon_mono_auto_wrap(scene_node::ctor));
    mono_jit::add_internal_call("AeonEngineMono.Scene.SceneNode::AttachChild(AeonEngineMono.Scene.SceneNode)",
                                aeon_mono_auto_wrap(scene_node::attach_child));
    mono_jit::add_internal_call("AeonEngineMono.Scene.SceneNode::AttachComponent(AeonEngineMono.Scene.Component)",
                                aeon_mono_auto_wrap(scene_node::attach_component));

    // TODO: should be handled and called on baseclass
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetIdentity",
                                aeon_mono_auto_wrap(scene_node::set_identity));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::set_Position(AeonEngineMono.Types.Vector3f)",
                                aeon_mono_auto_wrap(scene_node::set_position));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::get_Position",
                                aeon_mono_auto_wrap(scene_node::get_position));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Translate(AeonEngineMono.Types.Vector3f)",
                                aeon_mono_auto_wrap(scene_node::translate));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetRotation(AeonEngineMono.Types.Vector3f)",
                                aeon_mono_auto_wrap(scene_node::set_rotation_vec));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetRotation(single)",
                                aeon_mono_auto_wrap(scene_node::set_rotation_angle));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetRotation(AeonEngineMono.Types.Quaternion)",
                                aeon_mono_auto_wrap(scene_node::set_rotation_quat));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Rotate(AeonEngineMono.Types.Vector3f)",
                                aeon_mono_auto_wrap(scene_node::rotate_vec));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Rotate(single)",
                                aeon_mono_auto_wrap(scene_node::rotate_angle));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Rotate(AeonEngineMono.Types.Quaternion)",
                                aeon_mono_auto_wrap(scene_node::rotate_quat));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::SetScale(AeonEngineMono.Types.Vector3f)",
                                aeon_mono_auto_wrap(scene_node::set_scale));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::Scale(AeonEngineMono.Types.Vector3f)",
                                aeon_mono_auto_wrap(scene_node::scale));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::get_Matrix",
                                aeon_mono_auto_wrap(scene_node::get_matrix));
    mono_jit::add_internal_call("AeonEngineMono.Scene.MovableObject::set_Matrix(AeonEngineMono.Types.Matrix4)",
                                aeon_mono_auto_wrap(scene_node::set_matrix));
}

void scene_node::ctor(MonoObject *this_ptr, std::string name)
{
    auto &scene_manager = mono_jit_manager::get_application().get_scene_manager();
    auto scene_node = scene_manager.create_detached_scene_node(name);

    mono_object_wrapper<std::shared_ptr<scene::scene_node>>::create(this_ptr, scene_node);
}

void scene_node::attach_child(std::shared_ptr<scene::scene_node> this_ptr, std::shared_ptr<scene::scene_node> child)
{
    this_ptr->attach_child(child);
}

void scene_node::attach_component(std::shared_ptr<scene::scene_node> this_ptr,
                                  std::shared_ptr<scene::component> component)
{
    this_ptr->attach_component(component);
}

void scene_node::set_identity(std::shared_ptr<scene::scene_node> this_ptr)
{
    this_ptr->set_identity();
}

void scene_node::set_position(std::shared_ptr<scene::scene_node> this_ptr, glm::vec3 position)
{
    this_ptr->set_position(position);
}

auto scene_node::get_position(std::shared_ptr<scene::scene_node> this_ptr) -> glm::vec3
{
    return this_ptr->get_position();
}

void scene_node::translate(std::shared_ptr<scene::scene_node> this_ptr, glm::vec3 vec)
{
    this_ptr->translate(vec);
}

void scene_node::set_rotation_vec(std::shared_ptr<scene::scene_node> this_ptr, glm::vec3 vec)
{
    this_ptr->set_rotation(vec);
}

void scene_node::set_rotation_angle(std::shared_ptr<scene::scene_node> this_ptr, float angle)
{
    this_ptr->set_rotation(angle);
}

void scene_node::set_rotation_quat(std::shared_ptr<scene::scene_node> this_ptr, glm::quat quat)
{
    this_ptr->set_rotation(quat);
}

void scene_node::rotate_vec(std::shared_ptr<scene::scene_node> this_ptr, glm::vec3 vec)
{
    this_ptr->rotate(vec);
}

void scene_node::rotate_angle(std::shared_ptr<scene::scene_node> this_ptr, float angle)
{
    this_ptr->rotate(angle);
}

void scene_node::rotate_quat(std::shared_ptr<scene::scene_node> this_ptr, glm::quat quat)
{
    this_ptr->rotate(quat);
}

void scene_node::set_scale(std::shared_ptr<scene::scene_node> this_ptr, glm::vec3 vec)
{
    this_ptr->set_scale(vec);
}

void scene_node::scale(std::shared_ptr<scene::scene_node> this_ptr, glm::vec3 vec)
{
    this_ptr->scale(vec);
}

void scene_node::set_matrix(std::shared_ptr<scene::scene_node> this_ptr, glm::mat4x4 mat)
{
    this_ptr->set_matrix(mat);
}

auto scene_node::get_matrix(std::shared_ptr<scene::scene_node> this_ptr) -> glm::mat4x4
{
    return this_ptr->get_matrix();
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
