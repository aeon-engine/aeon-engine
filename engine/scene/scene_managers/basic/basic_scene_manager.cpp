/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <scene/scene_managers/basic/basic_scene_manager.h>

namespace aeon
{
namespace scene
{

basic_scene_manager::basic_scene_manager(gfx::device &device)
    : scene_manager(device)
{
}

basic_scene_manager::~basic_scene_manager()
{
}

void basic_scene_manager::__prepare_render_queue(camera *)
{
    queue_.clear_render_objects();

    root_node_->recalculate_matrices();
    __traverse_scene_node(root_node_);
}

void basic_scene_manager::__traverse_scene_node(scene_node_ptr node)
{
    auto objects = node->get_render_objects();

    // Add all renderables to the queue
    for (auto o : objects)
    {
        queue_.add_render_object(node->get_total_matrix(), o, render_layer::world_geometry);
    }

    for (auto n : *node)
    {
        __traverse_scene_node(n);
    }
}

} // namespace scene
} // namespace aeon
