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

namespace aeon
{
namespace scene
{

scene_manager::scene_manager(gfx::device &device)
    : root_node_(new scene_node())
    , device_(device)
{
}

scene_node_ptr scene_manager::create_child_scene_node()
{
    return root_node_->create_child_scene_node();
}

void scene_manager::detach_child_scene_node(scene_node_ptr node)
{
    root_node_->detach_child(node);
}

void scene_manager::attach_viewport(viewport_ptr vp)
{
    viewports_.push_back(vp);
}

void scene_manager::detach_viewport(viewport_ptr vp)
{
    viewports_.erase(std::remove(viewports_.begin(), viewports_.end(), vp), viewports_.end());
}

void scene_manager::remove_all_viewports()
{
    viewports_.clear();
}

void scene_manager::__render_scene(camera* cam, viewport* vp)
{
    __prepare_render_queue(cam);
}

} // namespace scene
} // namespace aeon
