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

#include <aeon/scene/basic_scene_manager/basic_scene_manager.h>

namespace aeon
{
namespace scene
{

basic_scene_manager::basic_scene_manager(gfx::device &device)
    : scene_manager(device)
{
}

void basic_scene_manager::__prepare_render_queue(camera *)
{
    queue_.clear_render_objects();

    root_node_->recalculate_matrices();
    __traverse_scene_node(*root_node_);
}

void basic_scene_manager::__traverse_scene_node(scene_node &node)
{
    auto objects = node.get_scene_objects();

    // Add all renderables to the queue
    for (auto &o : objects)
    {
        // TODO: Make distinction between 2d and 3d (z-order)
        if (o->get_type() == scene_object_type::sprite || o->get_type() == scene_object_type::mesh)
            queue_.add_render_object(node.get_total_matrix(), o, o->get_queue_group());
    }

    auto children = node.get_children_refs();
    for (auto n : children)
    {
        __traverse_scene_node(n);
    }
}

} // namespace scene
} // namespace aeon
