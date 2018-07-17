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

#pragma once

#include <aeon/scene/exceptions.h>
#include <aeon/math/mat4.h>
#include <aeon/math/vector3.h>
#include <aeon/math/quaternion.h>

namespace aeon
{
namespace scene
{

DEFINE_EXCEPTION_OBJECT(scene_transform_space_exception, scene_exception, "Unknown or unsupported transform space.");

enum class transform_space
{
    local,
    parent
};

class movable_object
{
public:
    /*!
     * Destructor
     */
    virtual ~movable_object() = default;

    /*!
     * Set the position and rotation to 0. Sets the internal matrix to an identity matrix.
     * Sets the dirty flag.
     */
    void set_identity();

    /*!
     * Translate the internal matrix (relative to the current position).
     * Sets the dirty flag.
     */
    void set_position(const float x, const float y, const float z = 0);

    /*!
     * Translate the internal matrix (relative to the current position).
     * Sets the dirty flag.
     */
    void set_position(const math::vector3<float> &vector);

    /*!
     * Move relative to the current position.
     * Sets the dirty flag.
     */
    void translate(const float x, const float y, const float z = 0);

    /*!
     * Move relative to the current position.
     * Sets the dirty flag.
     */
    void translate(const math::vector3<float> &vector);

    /*!
     * Set the rotation of this object. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void set_rotation(const float x, const float y, const float z);

    /*!
     * Set the rotation of this object. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void set_rotation(const math::vector3<float> &vector);

    /*!
     * Set the rotation of this object. Angles must be given in radians.
     * This method is intended for rotating 2D objects such as sprites, as it only really makes sense for orthographic
     * views.
     * Sets the dirty flag.
     */
    void set_rotation(const float angle);

    /*!
     * Set the rotation of this object. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void set_rotation(const math::quaternion &quaternion);

    /*!
     * Rotate relative to the current rotation. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void rotate(const float x, const float y, const float z);

    /*!
     * Rotate relative to the current rotation. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void rotate(const math::vector3<float> &vector);

    /*!
     * Rotate relative to the current rotation over the Z axis. Angles must be given in radians.
     * This method is intended for rotating 2D objects such as sprites, as it only really makes sense for orthographic
     * views.
     * Sets the dirty flag.
     */
    void rotate(const float angle);

    /*!
     * Rotate relative to the current rotation. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void rotate(const math::quaternion &quaternion);

    /*!
     * Set the scale.
     * Sets the dirty flag.
     */
    void set_scale(const float x, const float y, const float z);

    /*!
     * Set the scale uniformly across all axis.
     * Sets the dirty flag.
     */
    void set_scale(const float xyz);

    /*!
     * Set the scale.
     * Sets the dirty flag.
     */
    void set_scale(const math::vector3<float> &vector);

    /*!
     * Scale relative to the current scale.
     * Sets the dirty flag.
     */
    void scale(const float x, const float y, const float z);

    /*!
     * Scale uniformly across all axis relative to the current scale.
     * Sets the dirty flag.
     */
    void scale(const float xyz);

    /*!
     * Scale relative to the current scale.
     * Sets the dirty flag.
     */
    void scale(const math::vector3<float> &vector);

    /*!
     * Get the internal matrix.
     */
    const auto &get_matrix() const
    {
        return matrix_;
    }

    /*!
     * Get the position of this object
     */
    const auto &get_position() const
    {
        return position_;
    }

    /*!
     * Get the rotation of this object as quaternion.
     */
    const auto &get_rotation() const
    {
        return rotation_;
    }

    /*!
     * Get the scale of this object
     */
    const auto &get_scale() const
    {
        return scale_;
    }

    /*!
     * Get the rotation of this object as euler angles.
     */
    auto get_rotation_euler() const
    {
        return math::euler(rotation_);
    }

    /*!
     * Returns true if this object was modified in any way
     */
    auto is_dirty() const
    {
        return dirty_;
    }

    /*!
     * Set the internal matrix.
     * Warning: Methods like translate may not work correctly anymore after manually changing the internal matrix.
     * An attempt is made to decompose the given matrix, but this may not always work.
     * Sets the dirty flag.
     */
    void set_matrix(const math::mat4 &matrix);

    /*!
     * Multiply the internal matrix with another matrix.
     * Warning: Methods like translate may not work correctly anymore after manually changing the internal matrix.
     * An attempt is made to decompose the given matrix, but this may not always work.
     * Sets the dirty flag.
     */
    void multiply_matrix(const math::mat4 &matrix);

protected:
    /*!
     * Construtor
     */
    movable_object();

    void update_matrix();

    void decompose_matrix();

    math::mat4 matrix_;

    /*!
     * True if this object has changed in any way. This means things need to be recalculated.
     */
    bool dirty_;
    math::vector3<float> position_;
    math::quaternion rotation_;
    math::vector3<float> scale_;
};

} // namespace scene
} // namespace aeon
