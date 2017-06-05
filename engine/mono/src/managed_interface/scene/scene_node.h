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

#pragma once

#include <managed_interface/core/types.h>
#include <mono/metadata/object.h>
#include <aeon/scene/scene_node.h>
#include <memory>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

class scene_node
{
public:
    static void register_internal_calls();

    static auto get_scene_node_from_mono_object(MonoObject *object) -> std::shared_ptr<scene::scene_node>;

private:
    static void ctor(MonoObject *this_ptr, MonoString *name);
    static void attach_child(MonoObject *this_ptr, MonoObject *child);
    static void attach_component(MonoObject *this_ptr, MonoObject *component);
    static void set_position(MonoObject *this_ptr, vector3f position);
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
