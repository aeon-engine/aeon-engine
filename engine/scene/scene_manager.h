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

#pragma once

#include <scene/scene_node.h>
#include <scene/viewport.h>
#include <scene/render_queue.h>
#include <gfx/gfx_device.h>
#include <vector>
#include <type_traits>
#include <utility>

namespace aeon
{
namespace scene
{

class scene_manager
{
    friend class camera;

public:
    explicit scene_manager(gfx::device &device);
    virtual ~scene_manager() = default;

    scene_node_ptr get_root_scene_node();

    scene_node_ptr create_child_scene_node();

    void detach_child_scene_node(scene_node_ptr node);

    template<typename T, class... U>
    std::shared_ptr<T> create_render_object(U&&... u)
    {
        static_assert(std::is_base_of<render_object, T>::value,
            "T must be derived from render_object.");

        return std::make_shared<T>(this, std::forward<U>(u)...);
    }

    gfx::device &get_device() const;

protected:
    virtual void __render_scene(camera *cam, viewport *vp);

    virtual void __prepare_render_queue(camera *cam) = 0;

    scene_node_ptr root_node_;
    render_queue queue_;
    gfx::device &device_;
};

} // namespace scene
} // namespace aeon
