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

#include <scene/scene_layer.h>

namespace aeon
{
namespace scene
{

scene_layer::scene_layer(int priority) :
    priority_(priority),
    root_node_(scene_node_ptr(new scene_node()))
{
}

scene_layer::~scene_layer()
{
}

scene_node_ptr scene_layer::create_child_scene_node()
{
    return root_node_->create_child_scene_node();
}

void scene_layer::detach_child_scene_node(scene_node_ptr node)
{
    root_node_->detach_child(node);
}

} // namespace scene
} // namespace aeon
