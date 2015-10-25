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

namespace aeon
{
namespace scene
{

scene_manager::scene_manager() :
    root_node_(scene_node_ptr(new scene_node()))
{
}

scene_manager::~scene_manager()
{
}

scene_node_ptr scene_manager::create_child_scene_node()
{
    return root_node_->create_child_scene_node();
}

} // namespace scene
} // namespace aeon
