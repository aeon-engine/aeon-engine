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

#pragma once

#include <aeon/scene/component.h>
#include <aeon/scene/movable_object.h>
#include <aeon/common/noncopyable.h>
#include <glm/mat4x4.hpp>
#include <vector>
#include <memory>

namespace aeon
{
namespace scene
{

enum find_method
{
    single,
    recursive
};

class scene_node : public std::enable_shared_from_this<scene_node>, public movable_object, public common::noncopyable
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
    auto create_child_scene_node(const std::string &name = "") -> std::shared_ptr<scene_node>;

    /*!
     * Attach a scene node to this node. This will automatically detach the given node from it's current parent,
     * if any.
     */
    void attach_child(const std::shared_ptr<scene_node> &node);

    /*!
     * Detach a scene node. The given scene node will have it's parent set to nullptr.
     * Will result in undefined (dangerous!) behavior if the given scene node was not a child of
     * this node.
     */
    void detach_child(const std::shared_ptr<scene_node> &node);

    /*!
     * Detach all children scene_nodes that were attached to this one.
     */
    void detach_all_children();

    /*!
     * Attach an object to this scene node.
     * TODO: Can the same object be attached to multiple scene nodes? What are the implications of this?
     */
    void attach_component(const std::shared_ptr<component> &object);

    /*!
     * Detach an object from this scene node.
     */
    void detach_component(const std::shared_ptr<component> &object);

    /*!
     * Detach all objects from this scene node.
     */
    void detach_all_components();

    /*!
     * Recalculate the total matrix of this scenenode if either this or the parent node is marked as dirty. If neither
     * is marked as dirty, no recalculation is done. This also triggers a call to recalculate_matrices for each of the
     * children.
     */
    void recalculate_matrices();

    /*!
     * Get the calculated matrix, which are all the matrix multiplications of everything up until the root node.
     * If this node is flagged is dirty (see: is_dirty()), this value may be incorrect. Use recalculate_matrices() if
     * you want to be sure of a correct value;
     */
    const auto &get_total_matrix() const
    {
        return total_matrix_;
    }

    /*!
     * Get the center point of this scene node.
     * If this node is flagged is dirty (see: is_dirty()), this value may be incorrect. Use recalculate_matrices() if
     * you want to be sure of a correct value;
     */
    auto get_center_point() const
    {
        return total_matrix_ * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    }

    /*!
     * Get the parent this scene node is attached to. Equals nullptr if this node isn't attached to anything.
     */
    auto get_parent() const
    {
        return parent_;
    }

    /*!
     * Recursively detach and cleanup all scene nodes and their children from this node.
     */
    void cleanup_children();

    /*!
     * Make a deepcopy of this scene node and all it's children so that it can be attached somewhere else.
     */
    auto clone() -> std::shared_ptr<scene_node>;

    /*!
     * Get a vector of references to all children.
     */
    auto get_children_refs() const -> std::vector<std::reference_wrapper<scene_node>>;

    /*!
     * Get all attached objects to this node
     */
    const auto &get_components() const
    {
        return components_;
    }

    /*!
     * Get the name of this scene node. This could be an empty string if no name was given on creation.
     */
    const auto &get_name() const
    {
        return name_;
    }

    /*!
     * Find a scene node by name. This method will return the first scene node that matches the given name.
     * The given name should not be an empty string.
     * The find method can be single (only search within this scene node) or resursive (also search the
     * children of this node; default).
     */
    auto find_child_by_name(const std::string &name, const find_method method = find_method::recursive) const
        -> scene_node *;

    /*!
     * Find a scene object by name. This method will return the first scene object that matches the given name.
     * The given name should not be an empty string.
     * The find method can be single (only search within this scene node) or resursive (also search the
     * children of this node; default).
     */
    template <typename T>
    auto find_component_by_name(const std::string &name, const find_method method = find_method::recursive) const
        -> std::shared_ptr<T>
    {
        return std::dynamic_pointer_cast<T>(__find_component_by_name(name, method));
    }

private:
    /*!
     * Construtor
     * A scene node is marked as dirty by default.
     */
    explicit scene_node(const std::string &name = "");

    /*!
     * Internal non-template version of find scene object. The public interface version will perform a dynamic
     * pointer cast on the given scene object.
     */
    auto __find_component_by_name(const std::string &name, const find_method method = find_method::recursive) const
        -> std::shared_ptr<component>;

    /*!
     * The scene node that this node is attached to, or nullptr if not attached to anything.
     */
    std::shared_ptr<scene_node> parent_;

    /*!
     * All attached scene nodes.
     */
    std::vector<std::shared_ptr<scene_node>> children_;

    /*!
     * All attached render objects
     */
    std::vector<std::shared_ptr<component>> components_;

    /*!
     * The precalculated matrix multiplications of everything up until the root node.
     */
    glm::mat4 parent_matrix_;

    /*!
     * The calculated matrix for this node (matrix_ * parent_matrix_)
     */
    glm::mat4 total_matrix_;

    /*!
     * True if this is the root node
     */
    bool is_root_;

    /*!
     * The name of this scene node (can be empty)
     */
    std::string name_;
};

} // namespace scene
} // namespace aeon
