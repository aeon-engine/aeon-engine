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

#include <aeon/scene/scene_object.h>
#include <aeon/scene/scene_node.h>

namespace aeon
{
namespace scene
{

auto scene_object::get_scene_matrix() const -> glm::mat4
{
    if (!scene_node_)
        return glm::mat4(1.0f);

    return scene_node_->get_total_matrix();
}

} // namespace scene
} // namespace aeon
