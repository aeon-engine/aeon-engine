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

#pragma once

#include <aeon/scene/scene_object.h>
#include <aeon/scene/exceptions.h>
#include <aeon/utility.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <memory>

namespace aeon
{
namespace scene
{

DEFINE_EXCEPTION_OBJECT(scene_transform_space_exception, scene_exception, "Unknown or unsupported transform space.");

class scene_node;
using scene_node_ptr = std::shared_ptr<scene_node>;

enum class transform_space
{
    local,
    parent
};

class scene_node : public std::enable_shared_from_this<scene_node>, public utility::noncopyable
{
    friend class scene_manager;

public:
    /*!
     * Destructor
     */
    virtual ~scene_node() = default;

    /*!
     * Create a new scene node attached to this scene node.
     */
    scene_node_ptr create_child_scene_node();

    /*!
     * Attach a scene node to this node. This will automatically detach the given node from it's current parent,
     * if any.
     */
    void attach_child(scene_node_ptr node);

    /*!
     * Detach a scene node. The given scene node will have it's parent set to nullptr.
     * Will result in undefined (dangerous!) behavior if the given scene node was not a child of
     * this node.
     */
    void detach_child(scene_node_ptr node);

    /*!
     * Detach all children scene_nodes that were attached to this one.
     */
    void detach_all_children();

    /*!
     * Attach an object to this scene node.
     * TODO: Can the same object be attached to multiple scene nodes? What are the implications of this?
     */
    void attach_scene_object(scene_object_ptr object);

    /*!
     * Detach an object from this scene node.
     */
    void detach_scene_object(scene_object_ptr object);

    /*!
     * Detach all objects from this scene node.
     */
    void detach_all_scene_objects();

    /*!
     * Recalculate the total matrix of this scenenode if either this or the parent node is marked as dirty. If neither
     * is marked as dirty, no recalculation is done. This also triggers a call to recalculate_matrices for each of the
     * children.
     */
    void recalculate_matrices();

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
    void translate(float x, float y, float z = 0);

    /*!
     * Translate the internal matrix.
     * Sets the dirty flag.
     */
    void translate(const glm::vec3 &vector);

    /*!
     * Rotate the internal matrix. Angles are in radians.
     * Sets the dirty flag.
     */
    void rotate(float x, float y, float z, const transform_space space = transform_space::local);

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
    void rotate(float angle, const transform_space space = transform_space::local);

    /*!
     * Rotate the internal matrix through a quaternion. The transform space determines how the rotation is applied.
     * Sets the dirty flag.
     */
    void rotate(const glm::quat &quat, const transform_space space = transform_space::local);

    /*!
     * Scale the internal matrix.
     * Sets the dirty flag.
     */
    void scale(float x, float y, float z);

    /*!
     * Scale the internal matrix.
     * Sets the dirty flag.
     */
    void scale(const glm::vec3 &vector);

    /*!
     * Scale the internal matrix uniformly across all axis.
     * Sets the dirty flag.
     */
    void scale(float xyz);

    /*!
     * Multiply the internal matrix with another matrix.
     * Sets the dirty flag.
     */
    void multiply(const glm::mat4 &matrix);

    /*!
     * Get the internal matrix of this scene node. This matrix is not multiplied with any parent nodes; use
     * get_total_matrix() for that.
     */
    const glm::mat4 &get_matrix() const
    {
        return matrix_;
    }

    /*!
     * Get the calculated matrix, which are all the matrix multiplications of everything up until the root node.
     * If this node is flagged is dirty (see: is_dirty()), this value may be incorrect. Use recalculate_matrices() if
     * you want to be sure of a correct value;
     */
    const glm::mat4 &get_total_matrix() const
    {
        return total_matrix_;
    }

    /*!
     * Get the center point of this scene node.
     * If this node is flagged is dirty (see: is_dirty()), this value may be incorrect. Use recalculate_matrices() if
     * you want to be sure of a correct value;
     */
    glm::vec4 get_center_point() const
    {
        return total_matrix_ * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    /*!
     * Get the parent this scene node is attached to. Equals nullptr if this node isn't attached to anything.
     */
    scene_node_ptr get_parent() const
    {
        return parent_;
    }

    /*!
     * Returns true if this scene node was modified in any way since the last call to recalculate_matrices.
     */
    bool is_dirty() const
    {
        return dirty_;
    }

    /*!
     * Recursively detach and cleanup all scene nodes and their children from this node.
     */
    void cleanup_children();

    /*!
     * Make a deepcopy of this scene node and all it's children so that it can be attached somewhere else.
     */
    scene_node_ptr clone();

    /*!
     * Begin iterator for c++11 "foreach".
     */
    std::vector<scene_node_ptr>::const_iterator begin() const;

    /*!
     * End iterator for c++11 "foreach".
     */
    std::vector<scene_node_ptr>::const_iterator end() const;

    /*!
     * Get all attached objects to this node
     */
    std::vector<scene_object_ptr> get_scene_objects() const;

private:
    /*!
     * Construtor
     * A scene node is marked as dirty by default.
     */
    scene_node();

    /*!
     * The scene node that this node is attached to, or nullptr if not attached to anything.
     */
    scene_node_ptr parent_;

    /*!
     * All attached scene nodes.
     */
    std::vector<scene_node_ptr> children_;

    /*!
     * All attached render objects
     */
    std::vector<scene_object_ptr> scene_objects_;

    /*!
     * The matrix for this node.
     */
    glm::mat4 matrix_;

    /*!
     * The precalculated matrix multiplications of everything up until the root node.
     */
    glm::mat4 parent_matrix_;

    /*!
     * The calculated matrix for this node (matrix_ * parent_matrix_)
     */
    glm::mat4 total_matrix_;

    /*!
     * True if this node has changed in any way. This means things need to be recalculated.
     */
    bool dirty_;

    /*!
     * True if this is the root node
     */
    bool is_root_;
};

} // namespace scene
} // namespace aeon