/*
 * Copyright (c) 2012-2018 Robin Degen
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

namespace aeon
{
namespace scene
{

movable_object::movable_object()
    : dirty_(true)
    , position_()
    , rotation_(math::quaternion::indentity())
    , scale_(1.0f, 1.0f, 1.0f)
    , matrix_(math::mat4::indentity())
{
}

void movable_object::set_identity()
{
    matrix_ = math::mat4::indentity();
    position_ = {};
    rotation_ = math::quaternion::indentity();
    scale_ = {1.0f, 1.0f, 1.0f};
    dirty_ = true;
}

void movable_object::set_position(const float x, const float y, const float z)
{
    set_position({x, y, z});
}

void movable_object::set_position(const math::vector3<float> &vector)
{
    position_ = vector;
    update_matrix();
    dirty_ = true;
}

void movable_object::translate(const float x, const float y, const float z /* = 0 */)
{
    translate({x, y, z});
}

void movable_object::translate(const math::vector3<float> &vector)
{
    position_ += vector;
    update_matrix();
    dirty_ = true;
}

void movable_object::set_rotation(const float x, const float y, const float z)
{
    set_rotation(math::quaternion(math::vector3<float>(x, y, z)));
}

void movable_object::set_rotation(const math::vector3<float> &vector)
{
    set_rotation(math::quaternion(vector));
}

void movable_object::set_rotation(const float angle)
{
    set_rotation(math::quaternion(math::vector3<float>(0.0f, 0.0f, angle)));
}

void movable_object::set_rotation(const math::quaternion &quaternion)
{
    rotation_ = quaternion;
    update_matrix();
    dirty_ = true;
}

void movable_object::rotate(const float x, const float y, const float z)
{
    rotate(math::quaternion(math::vector3<float>(x, y, z)));
}

void movable_object::rotate(const math::vector3<float> &vector)
{
    rotate(math::quaternion(vector));
}

void movable_object::rotate(const float angle)
{
    rotate(math::quaternion(math::vector3<float>(0.0f, 0.0f, angle)));
}

void movable_object::rotate(const math::quaternion &quaternion)
{
    rotation_ *= quaternion;
    update_matrix();
    dirty_ = true;
}

void movable_object::set_scale(const float x, const float y, const float z)
{
    set_scale(math::vector3<float>(x, y, z));
}

void movable_object::set_scale(const float xyz)
{
    set_scale(math::vector3<float>(xyz, xyz, xyz));
}

void movable_object::set_scale(const math::vector3<float> &vector)
{
    scale_ = vector;
    update_matrix();
    dirty_ = true;
}

void movable_object::scale(const float x, const float y, const float z)
{
    scale(math::vector3<float>(x, y, z));
}

void movable_object::scale(const float xyz)
{
    scale(math::vector3<float>(xyz, xyz, xyz));
}

void movable_object::scale(const math::vector3<float> &vector)
{
    scale_ *= vector;
    update_matrix();
    dirty_ = true;
}

void movable_object::set_matrix(const math::mat4 &matrix)
{
    matrix_ = matrix;
    decompose_matrix();
    dirty_ = true;
}

void movable_object::multiply_matrix(const math::mat4 &matrix)
{
    matrix_ *= matrix;
    decompose_matrix();
    dirty_ = true;
}

void movable_object::update_matrix()
{
    matrix_ = math::mat4::indentity();
    matrix_ *= math::mat4::scale(scale_);
    matrix_ *= math::mat4::translate(position_);
    matrix_ *= math::mat4{rotation_};
}

void movable_object::decompose_matrix()
{
    math::decompose(matrix_, position_, scale_, rotation_);
}

} // namespace scene
} // namespace aeon
