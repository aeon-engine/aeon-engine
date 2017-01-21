/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
#include <aeon/scene/scene_manager.h>
#include <aeon/scene/camera.h>
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

auto scene_manager::create_child_scene_node(const std::string &name) const -> std::shared_ptr<scene_node>
{
    return root_node_->create_child_scene_node(name);
}

auto scene_manager::create_detached_scene_node(const std::string &name) const -> std::shared_ptr<scene_node>
{
    return std::shared_ptr<scene_node>(new scene_node(name));
}

void scene_manager::detach_child_scene_node(const std::shared_ptr<scene_node> &node) const
{
    root_node_->detach_child(node);
}

void scene_manager::cleanup_scene()
{
    root_node_->cleanup_children();
    queue_.clear_render_objects();
}

void scene_manager::__render_scene(camera &cam, gfx::render_target &rt, gfx::viewport &vp, const float dt)
{
    device_.set_viewport(rt, vp);
    device_.clear_buffer(gfx::buffer_clear_flag::depth_buffer);

    __prepare_render_queue(&cam);

    queue_.sort();

    for (auto &render_object : queue_)
    {
        render_object.object->render(cam.get_projection_matrix(), glm::inverse(cam.get_scene_matrix()),
                                     render_object.matrix, dt);
    }
}

} // namespace scene
} // namespace aeon
