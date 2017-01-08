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

#pragma once

#include <aeon/scene/scene_node.h>
#include <aeon/gfx/gfx_viewport.h>
#include <aeon/scene/render_queue.h>
#include <aeon/gfx/gfx_device.h>
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

    auto &get_root_scene_node() const
    {
        return *root_node_;
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
    void cleanup_scene() const;

    template <typename T, class... U>
    auto create_scene_object(U &&... u)
    {
        static_assert(std::is_base_of<scene_object, T>::value, "T must be derived from scene_object.");

        return std::make_shared<T>(this, std::forward<U>(u)...);
    }

    auto &get_device() const
    {
        return device_;
    }

protected:
    virtual void __render_scene(camera &cam, gfx::render_target &rt, gfx::viewport &vp, const float dt);

    virtual void __prepare_render_queue(camera *cam) = 0;

    std::shared_ptr<scene_node> root_node_;
    render_queue queue_;
    gfx::device &device_;
};

} // namespace scene
} // namespace aeon
