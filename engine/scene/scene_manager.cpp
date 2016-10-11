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

#include <algorithm>
#include <scene/scene_manager.h>
#include <glm/gtc/type_ptr.hpp>

namespace aeon
{
namespace scene
{

scene_manager::scene_manager(gfx::device &device)
    : root_node_(new scene_node())
    , device_(device)
{
    root_node_->is_root_ = true;
}

scene_manager::~scene_manager()
{
    cleanup_scene();
}

scene_node_ptr scene_manager::get_root_scene_node() const
{
    return root_node_;
}

scene_node_ptr scene_manager::create_child_scene_node() const
{
    return root_node_->create_child_scene_node();
}

scene_node_ptr scene_manager::create_detached_scene_node() const
{
    return scene_node_ptr(new scene_node());
}

void scene_manager::detach_child_scene_node(scene_node_ptr node) const
{
    root_node_->detach_child(node);
}

void scene_manager::cleanup_scene() const
{
    root_node_->cleanup_children();
}

gfx::device &scene_manager::get_device() const
{
    return device_;
}

void scene_manager::__render_scene(camera *cam, gfx::viewport &vp, float dt)
{
    device_.set_viewport(vp);

    __prepare_render_queue(cam);

    queue_.sort();

    device_.clear_buffer(gfx::buffer_clear_flag::color_buffer | gfx::buffer_clear_flag::depth_buffer);

    for (auto render_object : queue_)
    {
        render_object.object->render(cam->get_projection_matrix(), cam->get_view_matrix(), render_object.matrix, dt);
    }
}

} // namespace scene
} // namespace aeon
