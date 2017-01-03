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

#pragma once

#include <aeon/scene/exceptions.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

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
    void set_position(const glm::vec3 &vector);

    /*!
     * Move relative to the current position.
     * Sets the dirty flag.
     */
    void translate(const float x, const float y, const float z = 0);

    /*!
     * Move relative to the current position.
     * Sets the dirty flag.
     */
    void translate(const glm::vec3 &vector);

    /*!
     * Set the rotation of this object. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void set_rotation(const float x, const float y, const float z);

    /*!
     * Set the rotation of this object. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void set_rotation(const glm::vec3 &vector);

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
    void set_rotation(const glm::quat &quaternion);

    /*!
     * Rotate relative to the current rotation. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void rotate(const float x, const float y, const float z);

    /*!
     * Rotate relative to the current rotation. Angles must be given in radians.
     * Sets the dirty flag.
     */
    void rotate(const glm::vec3 &vector);

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
    void rotate(const glm::quat &quaternion);

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
    void set_scale(const glm::vec3 &vector);

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
    void scale(const glm::vec3 &vector);

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
    const auto &get_rotation_euler() const
    {
        return glm::axis(rotation_);
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
    void set_matrix(const glm::mat4 &matrix);

    /*!
     * Multiply the internal matrix with another matrix.
     * Warning: Methods like translate may not work correctly anymore after manually changing the internal matrix.
     * An attempt is made to decompose the given matrix, but this may not always work.
     * Sets the dirty flag.
     */
    void multiply_matrix(const glm::mat4 &matrix);

protected:
    /*!
     * Construtor
     */
    movable_object();

    void update_matrix();

    void decompose_matrix();

    /*!
     * True if this object has changed in any way. This means things need to be recalculated.
     */
    bool dirty_;

    glm::vec3 position_;
    glm::quat rotation_;
    glm::vec3 scale_;
    glm::mat4 matrix_;
};

} // namespace scene
} // namespace aeon
