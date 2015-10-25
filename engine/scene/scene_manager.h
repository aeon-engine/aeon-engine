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

#include <scene/scene_node.h>
#include <scene/render_queue.h>

namespace aeon
{
namespace scene
{

class scene_manager
{
public:
    scene_manager();
    virtual ~scene_manager();

    /*!
     * Create a new scene node attached to this scene node.
     */
    scene_node_ptr create_child_scene_node();

    /*!
     * Get the rood scene node. Do not attach this root to anything else! This will lead to unexpected behavior.
     */
    scene_node_ptr get_root_scene_node() const
    {
        return root_node_;
    }

protected:
    /*!
     * The root of the scene node tree.
     */
    scene_node_ptr root_node_;

};

} // namespace scene
} // namespace aeon
