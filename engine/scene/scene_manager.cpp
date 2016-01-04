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

#include <scene/scene_manager.h>
#include <algorithm>

namespace aeon
{
namespace scene
{

scene_manager::scene_manager()
{
}

scene_manager::~scene_manager()
{
}

scene_layer_ptr scene_manager::create_scene_layer(int priority)
{
    scene_layer_ptr layer = std::make_shared<scene_layer>(priority);
    layers_.push_back(layer);
    __sort_layers_by_priority();
    return layer;
}

void scene_manager::remove_scene_layer(scene_layer_ptr layer)
{
    layers_.erase(std::remove(layers_.begin(), layers_.end(), layer), layers_.end());
    __sort_layers_by_priority();
}

void scene_manager::remove_all_scene_layers()
{
    layers_.clear();
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

void scene_manager::__sort_layers_by_priority()
{
    std::sort(layers_.begin(), layers_.end(), [](const scene_layer_ptr &a, const scene_layer_ptr &b)
              {
                  return a->get_priority() < b->get_priority();
              });
}

} // namespace scene
} // namespace aeon
