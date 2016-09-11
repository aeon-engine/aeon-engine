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

#include <scene/perspective_camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace aeon
{
namespace scene
{

perspective_camera::perspective_camera(scene_manager *scene_manager, float fov_y, float aspect_ratio, float near,
                                       float far)
    : camera(scene_manager)
{
    projection_matrix_ = glm::perspective(glm::radians(fov_y), aspect_ratio, near, far);
}

perspective_camera::perspective_camera(scene_manager *scene_manager, float fov, float width, float height, float near,
                                       float far)
    : camera(scene_manager)
{
    projection_matrix_ = glm::perspectiveFov(fov, width, height, near, far);
}

} // namespace scene
} // namespace aeon
