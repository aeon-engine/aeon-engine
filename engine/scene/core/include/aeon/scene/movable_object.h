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
     * Set the internal matrix to an identity matrix.
     * Sets the dirty flag.
     */
    void set_identity();

    /*!
     * Set the internal matrix.
     * Sets the dirty flag.
     */
    void set_matrix(const glm::mat4 &matrix);

    /*!
     * Translate the internal matrix.
     * Sets the dirty flag.
     */
    void translate(const float x, const float y, const float z = 0);

    /*!
     * Translate the internal matrix.
     * Sets the dirty flag.
     */
    void translate(const glm::vec3 &vector);

    /*!
     * Rotate the internal matrix. Angles are in radians.
     * Sets the dirty flag.
     */
    void rotate(const float x, const float y, const float z, const transform_space space = transform_space::local);

    /*!
     * Rotate the internal matrix. Angles given in the vector are in radians.
     * Sets the dirty flag.
     */
    void rotate(const glm::vec3 &vector, const transform_space space = transform_space::local);

    /*!
     * Rotate the internal matrix over the Z axis. The given angle must be in radians.
     * This method is intended for rotating 2D objects such as sprites, as it only really makes sense for
     * orthographic views.
     * Sets the dirty flag.
     */
    void rotate(const float angle, const transform_space space = transform_space::local);

    /*!
     * Rotate the internal matrix through a quaternion. The transform space determines how the rotation is applied.
     * Sets the dirty flag.
     */
    void rotate(const glm::quat &quat, const transform_space space = transform_space::local);

    /*!
     * Scale the internal matrix.
     * Sets the dirty flag.
     */
    void scale(const float x, const float y, const float z);

    /*!
     * Scale the internal matrix.
     * Sets the dirty flag.
     */
    void scale(const glm::vec3 &vector);

    /*!
     * Scale the internal matrix uniformly across all axis.
     * Sets the dirty flag.
     */
    void scale(const float xyz);

    /*!
     * Multiply the internal matrix with another matrix.
     * Sets the dirty flag.
     */
    void multiply(const glm::mat4 &matrix);

    /*!
     * Get the internal matrix.
     */
    const auto &get_matrix() const
    {
        return matrix_;
    }

    /*!
     * Returns true if this object was modified in any way
     */
    auto is_dirty() const
    {
        return dirty_;
    }

protected:
    /*!
     * Construtor
     */
    movable_object();

    /*!
     * True if this object has changed in any way. This means things need to be recalculated.
     */
    bool dirty_;

    /*!
     * The matrix for this movable object.
     */
    glm::mat4 matrix_;
};

} // namespace scene
} // namespace aeon
