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

#include <aeon/scene/scene_node.h>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

namespace aeon
{
namespace scene
{

scene_node::scene_node()
    : dirty_(true)
    , is_root_(false)
{
}

auto scene_node::create_child_scene_node() -> std::shared_ptr<scene_node>
{
    auto node = std::shared_ptr<scene_node>(new scene_node());
    attach_child(node);
    return node;
}

void scene_node::attach_child(const std::shared_ptr<scene_node> &node)
{
    if (node->parent_ != nullptr)
        node->parent_->detach_child(node);

    node->parent_ = shared_from_this();
    node->parent_matrix_ = total_matrix_;
    children_.push_back(node);

    dirty_ = true;
    node->dirty_ = true;
}

void scene_node::detach_child(const std::shared_ptr<scene_node> &node)
{
    children_.erase(std::remove(children_.begin(), children_.end(), node), children_.end());
    node->parent_ = nullptr;

    dirty_ = true;
}

void scene_node::detach_all_children()
{
    for (auto &node : children_)
        node->parent_ = nullptr;

    children_.clear();

    dirty_ = true;
}

void scene_node::attach_scene_object(const std::shared_ptr<scene_object> &object)
{
    object->__set_scene_node(this);
    scene_objects_.push_back(object);
}

void scene_node::detach_scene_object(const std::shared_ptr<scene_object> &object)
{
    object->__set_scene_node(nullptr);
    scene_objects_.erase(std::remove(scene_objects_.begin(), scene_objects_.end(), object), scene_objects_.end());
}

void scene_node::detach_all_scene_objects()
{
    for (auto &obj : scene_objects_)
        obj->__set_scene_node(nullptr);

    scene_objects_.clear();
}

void scene_node::recalculate_matrices()
{
    if (!is_root_ && !parent_)
        return;

    auto parent_dirty = is_root_ ? false : parent_->dirty_;

    if (dirty_ || parent_dirty)
        total_matrix_ = parent_matrix_ * matrix_;

    dirty_ = true;

    for (auto &node : children_)
    {
        node->parent_matrix_ = total_matrix_;
        node->recalculate_matrices();
    }

    dirty_ = false;
}

void scene_node::set_identity()
{
    matrix_ = glm::mat4(1.0f);
    dirty_ = true;
}

void scene_node::set_matrix(const glm::mat4 &matrix)
{
    matrix_ = matrix;
    dirty_ = true;
}

void scene_node::translate(const float x, const float y, const float z /* = 0 */)
{
    matrix_ = glm::translate(matrix_, glm::vec3(x, y, z));
    dirty_ = true;
}

void scene_node::translate(const glm::vec3 &vector)
{
    matrix_ = glm::translate(matrix_, vector);
    dirty_ = true;
}

void scene_node::rotate(const float x, const float y, const float z, const transform_space space)
{
    rotate(glm::quat(glm::vec3(x, y, z)), space);
}

void scene_node::rotate(const glm::vec3 &vector, const transform_space space)
{
    rotate(glm::quat(vector), space);
}

void scene_node::rotate(const float angle, const transform_space space)
{
    rotate(glm::quat(glm::vec3(0.0f, 0.0f, angle)), space);
}

void scene_node::rotate(const glm::quat &quat, const transform_space space)
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

void scene_node::scale(const float x, const float y, const float z)
{
    auto scale_vector = glm::vec3(x, y, z);
    scale(scale_vector);
}

void scene_node::scale(const glm::vec3 &vector)
{
    matrix_ = glm::scale(matrix_, vector);
}

void scene_node::scale(const float xyz)
{
    auto scale_vector = glm::vec3(xyz, xyz, xyz);
    scale(scale_vector);
}

void scene_node::multiply(const glm::mat4 &matrix)
{
    matrix_ *= matrix;
    dirty_ = true;
}

std::vector<std::reference_wrapper<scene_node>> scene_node::get_children_refs() const
{
    // TODO: This method should be optimized with a cache. This will speed up the render
    // loop considerably since it doesn't need to recreate this vector each time.
    auto children = std::vector<std::reference_wrapper<scene_node>>{};

    for (auto &c : children_)
    {
        children.push_back(*c);
    }

    return children;
}

void scene_node::cleanup_children()
{
    for (auto &node : children_)
    {
        node->cleanup_children();
    }

    detach_all_scene_objects();
    detach_all_children();
}

auto scene_node::clone() -> std::shared_ptr<scene_node>
{
    auto node_copy = std::shared_ptr<scene_node>(new scene_node());
    node_copy->scene_objects_ = scene_objects_;
    node_copy->matrix_ = matrix_;
    node_copy->parent_matrix_ = parent_matrix_;
    node_copy->total_matrix_ = total_matrix_;
    node_copy->dirty_ = true;
    node_copy->is_root_ = false;

    for (auto &node : children_)
    {
        node_copy->children_.push_back(node->clone());
    }

    return node_copy;
}

} // namespace scene
} // namespace aeon
