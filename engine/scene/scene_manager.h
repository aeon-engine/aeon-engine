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

#include <vector>
#include <scene/scene_node.h>
#include <scene/scene_layer.h>
#include <scene/viewport.h>

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
     * Create a new scene layer
     */
    scene_layer_ptr create_scene_layer(int priority);

    /*!
     * Remove a scene layer
     */
    void remove_scene_layer(scene_layer_ptr layer);

    /*!
     * Remove all scene layers
     */
    void remove_all_scene_layers();

    void attach_viewport(viewport_ptr vp);

    void detach_viewport(viewport_ptr vp);

    void remove_all_viewports();

protected:
    void __sort_layers_by_priority();

    std::vector<scene_layer_ptr> layers_;
    std::vector<viewport_ptr> viewports_;
};

} // namespace scene
} // namespace aeon
