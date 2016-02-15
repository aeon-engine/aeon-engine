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

#include <memory>
#include <scene/render_layer.h>
#include <glm/mat4x4.hpp>

namespace aeon
{
namespace scene
{

enum class scene_object_type
{
    spatial,    // This object is merely added for spatial information (camera's etc.)
    renderable, // This object needs to be rendered
};

class scene_node;
class scene_manager;
class scene_object
{
    friend class scene_node;

public:
    explicit scene_object(int queue_group, scene_object_type type, scene_manager *scene_manager)
        : queue_group_(queue_group)
        , type_(type)
        , scene_manager_(scene_manager)
        , scene_node_(nullptr)
    {
    }

    virtual ~scene_object() = default;

    scene_object_type get_type() const
    {
        return type_;
    }

    int get_queue_group() const
    {
        return queue_group_;
    }

    /*!
     * Called by the render queue when rendering. For some objects rendering
     * doesn't make sense (like camera's). In that case, this function must be
     * used to set up the matrices and/or buffers.
     */
    virtual void render(const glm::mat4x4 & /*projection*/, const glm::mat4x4 & /*view*/, const glm::mat4x4 & /*model*/,
                        float /*dt*/)
    {
    }

    /*!
     * Get the calculated matrix from the scene node. If this object is not attached
     * to any scene node, an identity matrix will be returned.
     */
    glm::mat4 get_matrix() const;

protected:
    void __set_scene_node(scene_node *node)
    {
        scene_node_ = node;
    }

    int queue_group_;
    scene_object_type type_;
    scene_manager *scene_manager_;
    scene_node *scene_node_;
};

using scene_object_ptr = std::shared_ptr<scene_object>;

} // namespace scene
} // namespace aeon
