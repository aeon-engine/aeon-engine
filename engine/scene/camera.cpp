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

#include <scene/camera.h>
#include <scene/scene_manager.h>

namespace aeon
{
namespace scene
{

camera::camera(scene_manager *scene_manager)
    : scene_object(render_layer::overlay, scene_object_type::spatial, scene_manager)
    , projection_matrix_(1.0f)
    , view_matrix_(1.0f)
{
}

void camera::render_scene(viewport *vp, float dt)
{
    scene_manager_->__render_scene(this, vp, dt);
}

void camera::reset_view()
{
    view_matrix_ = glm::mat4(1.0f);
}

} // namespace scene
} // namespace aeon
