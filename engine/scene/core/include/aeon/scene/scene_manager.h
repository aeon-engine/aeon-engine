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

#include <aeon/scene/scene_node.h>
#include <aeon/gfx/gfx_viewport.h>
#include <aeon/scene/render_queue.h>
#include <aeon/gfx/gfx_device.h>
#include <aeon/logger/logger.h>
#include <vector>
#include <type_traits>
#include <utility>
#include <memory>

namespace aeon
{
namespace scene
{

class camera;

class scene_manager
{
    friend class camera;

public:
    explicit scene_manager(gfx::device &device);
    virtual ~scene_manager();

    auto get_root_scene_node() const
    {
        return root_node_;
    }

    /*!
     * Create a child scene node attached to the root scene node.
     */
    auto create_child_scene_node(const std::string &name = "") const -> std::shared_ptr<scene_node>;

    /*!
     * Create a scene node that is not attached to anything. This scene node must be attached to another node
     * through scene_node::attach_child().
     */
    auto create_detached_scene_node(const std::string &name = "") const -> std::shared_ptr<scene_node>;

    void detach_child_scene_node(const std::shared_ptr<scene_node> &node) const;

    /*!
     * Recursively detach and cleanup all scene nodes and their children from the entire scene.
     */
    void cleanup_scene();

    template <typename T, class... U>
    auto create_component(U &&... u)
    {
        static_assert(std::is_base_of<component, T>::value, "T must be derived from component.");

        return std::make_shared<T>(*this, std::forward<U>(u)...);
    }

    auto &get_device() const
    {
        return device_;
    }

protected:
    virtual void __render_scene(camera &cam, gfx::render_target &rt, gfx::viewport &vp, const float dt);

    virtual void __prepare_render_queue(camera *cam) = 0;

    logger::logger logger_;

    std::shared_ptr<scene_node> root_node_;
    render_queue queue_;
    gfx::device &device_;
};

} // namespace scene
} // namespace aeon
