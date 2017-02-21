/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/scene/movable_object.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace aeon
{
namespace scene
{

movable_object::movable_object()
    : dirty_(true)
    , position_()
    , rotation_()
    , scale_(1.0f, 1.0f, 1.0f)
    , matrix_()
{
}

void movable_object::set_identity()
{
    matrix_ = glm::mat4(1.0f);
    position_ = glm::vec3();
    rotation_ = glm::quat();
    scale_ = glm::vec3();
    dirty_ = true;
}

void movable_object::set_position(const float x, const float y, const float z)
{
    set_position(glm::vec3(x, y, z));
}

void movable_object::set_position(const glm::vec3 &vector)
{
    position_ = vector;
    update_matrix();
    dirty_ = true;
}

void movable_object::translate(const float x, const float y, const float z /* = 0 */)
{
    translate(glm::vec3(x, y, z));
}

void movable_object::translate(const glm::vec3 &vector)
{
    position_ += vector;
    update_matrix();
    dirty_ = true;
}

void movable_object::set_rotation(const float x, const float y, const float z)
{
    set_rotation(glm::quat(glm::vec3(x, y, z)));
}

void movable_object::set_rotation(const glm::vec3 &vector)
{
    set_rotation(glm::quat(vector));
}

void movable_object::set_rotation(const float angle)
{
    set_rotation(glm::quat(glm::vec3(0.0f, 0.0f, angle)));
}

void movable_object::set_rotation(const glm::quat &quaternion)
{
    rotation_ = quaternion;
    update_matrix();
    dirty_ = true;
}

void movable_object::rotate(const float x, const float y, const float z)
{
    rotate(glm::quat(glm::vec3(x, y, z)));
}

void movable_object::rotate(const glm::vec3 &vector)
{
    rotate(glm::quat(vector));
}

void movable_object::rotate(const float angle)
{
    rotate(glm::quat(glm::vec3(0.0f, 0.0f, angle)));
}

void movable_object::rotate(const glm::quat &quaternion)
{
    rotation_ *= quaternion;
    update_matrix();
    dirty_ = true;
}

void movable_object::set_scale(const float x, const float y, const float z)
{
    set_scale(glm::vec3(x, y, z));
}

void movable_object::set_scale(const float xyz)
{
    set_scale(glm::vec3(xyz, xyz, xyz));
}

void movable_object::set_scale(const glm::vec3 &vector)
{
    scale_ = vector;
    update_matrix();
    dirty_ = true;
}

void movable_object::scale(const float x, const float y, const float z)
{
    scale(glm::vec3(x, y, z));
}

void movable_object::scale(const float xyz)
{
    scale(glm::vec3(xyz, xyz, xyz));
}

void movable_object::scale(const glm::vec3 &vector)
{
    scale_ *= vector;
    update_matrix();
    dirty_ = true;
}

void movable_object::set_matrix(const glm::mat4 &matrix)
{
    matrix_ = matrix;
    decompose_matrix();
    dirty_ = true;
}

void movable_object::multiply_matrix(const glm::mat4 &matrix)
{
    matrix_ *= matrix;
    decompose_matrix();
    dirty_ = true;
}

void movable_object::update_matrix()
{
    matrix_ = glm::mat4(1.0f);
    matrix_ = glm::scale(matrix_, scale_);
    matrix_ = glm::translate(matrix_, position_);
    matrix_ = matrix_ * glm::mat4_cast(rotation_);
}

void movable_object::decompose_matrix()
{
    glm::vec3 dummy_skew;
    glm::vec4 dummy_perspective;
    glm::decompose(matrix_, scale_, rotation_, position_, dummy_skew, dummy_perspective);
}

} // namespace scene
} // namespace aeon
