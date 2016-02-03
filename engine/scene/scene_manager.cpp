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
#include <GL/glew.h>
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

scene_node_ptr scene_manager::get_root_scene_node()
{
    return root_node_;
}

scene_node_ptr scene_manager::create_child_scene_node()
{
    return root_node_->create_child_scene_node();
}

void scene_manager::detach_child_scene_node(scene_node_ptr node)
{
    root_node_->detach_child(node);
}

void scene_manager::__render_scene(camera *cam, viewport *vp)
{
    device_.set_viewport(vp);

    __prepare_render_queue(cam);

    queue_.sort();

    // Render the queue
    // TODO: This is a temporary implementation
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(cam->get_matrix()));
    glMatrixMode(GL_MODELVIEW);

    for (auto render_object : queue_)
    {
        glLoadMatrixf(glm::value_ptr(render_object.matrix));
        render_object.object->render();
    }
}

} // namespace scene
} // namespace aeon
