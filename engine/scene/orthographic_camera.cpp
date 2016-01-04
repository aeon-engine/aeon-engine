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

#include <scene/orthographic_camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace aeon
{
namespace scene
{

orthographic_camera::orthographic_camera(float left, float right, float bottom, float top)
    : camera()
{
    projection_matrix_ = glm::ortho(left, right, bottom, top);
}

orthographic_camera::orthographic_camera(float left, float right, float bottom, float top, float near, float far)
    : camera()
{
    projection_matrix_ = glm::ortho(left, right, bottom, top, near, far);
}

orthographic_camera::~orthographic_camera()
{
}

} // namespace scene
} // namespace aeon
