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

#include <algorithm>
#include <aeon/scene/scene_manager.h>
#include <aeon/scene/camera.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace scene
{

scene_manager::scene_manager(gfx::device &device)
    : logger_(common::logger::get_singleton(), "Scene::SceneManager")
    , root_node_(new scene_node("root"))
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
    AEON_LOG_TRACE(logger_) << "Created child scene node '" << name << "' on root." << std::endl;
    return root_node_->create_child_scene_node(name);
}

auto scene_manager::create_detached_scene_node(const std::string &name) const -> std::shared_ptr<scene_node>
{
    AEON_LOG_TRACE(logger_) << "Created detached child scene node '" << name << "'." << std::endl;
    return std::shared_ptr<scene_node>(new scene_node(name));
}

void scene_manager::detach_child_scene_node(const std::shared_ptr<scene_node> &node) const
{
    AEON_LOG_TRACE(logger_) << "Detaching child scene node scene node '" << node->get_name() << "' from root."
                            << std::endl;
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
        render_object.object->render(cam.get_projection_matrix(), math::inverse(cam.get_scene_matrix()),
                                     render_object.matrix, dt);
    }
}

} // namespace scene
} // namespace aeon
