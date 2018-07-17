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

#pragma once

#include <managed_interface/mono_object_wrapper.h>
#include <managed_interface/core/types.h>
#include <managed_interface/scene/component.h>
#include <aeon/scene/scene_node.h>
#include <mono/metadata/object.h>
#include <memory>

namespace aeon
{
namespace mono
{

register_basic_mono_converter_for_wrapper(std::shared_ptr<scene::scene_node>);

namespace managed_interface
{

class scene_node
{
public:
    static void register_internal_calls();

private:
    static void ctor(MonoObject *this_ptr, std::string name);
    static void attach_child(std::shared_ptr<scene::scene_node> this_ptr, std::shared_ptr<scene::scene_node> child);
    static void attach_component(std::shared_ptr<scene::scene_node> this_ptr,
                                 std::shared_ptr<scene::component> component);

    static void set_identity(std::shared_ptr<scene::scene_node> this_ptr);
    static void set_position(std::shared_ptr<scene::scene_node> this_ptr, math::vector3<float> position);
    static auto get_position(std::shared_ptr<scene::scene_node> this_ptr) -> math::vector3<float>;

    static void translate(std::shared_ptr<scene::scene_node> this_ptr, math::vector3<float> vec);

    static void set_rotation_vec(std::shared_ptr<scene::scene_node> this_ptr, math::vector3<float> vec);
    static void set_rotation_angle(std::shared_ptr<scene::scene_node> this_ptr, float angle);
    static void set_rotation_quat(std::shared_ptr<scene::scene_node> this_ptr, math::quaternion quat);

    static void rotate_vec(std::shared_ptr<scene::scene_node> this_ptr, math::vector3<float> vec);
    static void rotate_angle(std::shared_ptr<scene::scene_node> this_ptr, float angle);
    static void rotate_quat(std::shared_ptr<scene::scene_node> this_ptr, math::quaternion quat);

    static void set_scale(std::shared_ptr<scene::scene_node> this_ptr, math::vector3<float> vec);
    static void scale(std::shared_ptr<scene::scene_node> this_ptr, math::vector3<float> vec);

    static void set_matrix(std::shared_ptr<scene::scene_node> this_ptr, math::mat4 mat);
    static auto get_matrix(std::shared_ptr<scene::scene_node> this_ptr) -> math::mat4;
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
