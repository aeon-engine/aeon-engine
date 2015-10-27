/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <scene/render_queue.h>
#include <scene/scene_node.h>
#include <memory>

namespace aeon
{
namespace scene
{

class scene_layer
{
public:
    scene_layer(int priority);
    ~scene_layer();

    scene_node_ptr create_child_scene_node();

    void detach_child_scene_node(scene_node_ptr node);

    int get_priority() const
    {
        return priority_;
    }

private:
    int priority_;
    scene_node_ptr root_node_;
    render_queue queue_;
};

using scene_layer_ptr = std::shared_ptr<scene_layer>;

} // namespace scene
} // namespace aeon
