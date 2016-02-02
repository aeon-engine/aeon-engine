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

namespace aeon
{
namespace scene
{

camera::camera(scene_manager *scene_manager)
    : render_object(render_layer::special, scene_manager)
    , projection_matrix_(1.0f)
    , view_matrix_(1.0f)
{
}

int camera::get_priority()
{
    return 0;
}

void camera::render_scene(viewport* vp)
{
}

} // namespace scene
} // namespace aeon
