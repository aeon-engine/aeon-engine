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

#include <aeon/scene/movable_object.h>
#include <glm/gtc/matrix_transform.hpp>

namespace aeon
{
namespace scene
{

movable_object::movable_object()
    : dirty_(true)
    , matrix_()
{
}

void movable_object::set_identity()
{
    matrix_ = glm::mat4(1.0f);
    dirty_ = true;
}

void movable_object::set_matrix(const glm::mat4 &matrix)
{
    matrix_ = matrix;
    dirty_ = true;
}

void movable_object::translate(const float x, const float y, const float z /* = 0 */)
{
    matrix_ = glm::translate(matrix_, glm::vec3(x, y, z));
    dirty_ = true;
}

void movable_object::translate(const glm::vec3 &vector)
{
    matrix_ = glm::translate(matrix_, vector);
    dirty_ = true;
}

void movable_object::rotate(const float x, const float y, const float z, const transform_space space)
{
    rotate(glm::quat(glm::vec3(x, y, z)), space);
}

void movable_object::rotate(const glm::vec3 &vector, const transform_space space)
{
    rotate(glm::quat(vector), space);
}

void movable_object::rotate(const float angle, const transform_space space)
{
    rotate(glm::quat(glm::vec3(0.0f, 0.0f, angle)), space);
}

void movable_object::rotate(const glm::quat &quat, const transform_space space)
{
    switch (space)
    {
        case transform_space::local:
            matrix_ = matrix_ * glm::mat4_cast(quat);
            break;
        case transform_space::parent:
            matrix_ = glm::mat4_cast(quat) * matrix_;
            break;
        default:
            throw scene_transform_space_exception();
    }

    dirty_ = true;
}

void movable_object::scale(const float x, const float y, const float z)
{
    auto scale_vector = glm::vec3(x, y, z);
    scale(scale_vector);
}

void movable_object::scale(const glm::vec3 &vector)
{
    matrix_ = glm::scale(matrix_, vector);
}

void movable_object::scale(const float xyz)
{
    auto scale_vector = glm::vec3(xyz, xyz, xyz);
    scale(scale_vector);
}

void movable_object::multiply(const glm::mat4 &matrix)
{
    matrix_ *= matrix;
    dirty_ = true;
}

} // namespace scene
} // namespace aeon
