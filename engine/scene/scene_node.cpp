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

#include <scene/scene_node.h>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

namespace aeon
{
namespace scene
{

scene_node::scene_node() :
    dirty_(true)
{
}

scene_node::~scene_node()
{
}

scene_node_ptr scene_node::create_child_scene_node()
{
    return scene_node_ptr(new scene_node());
}

void scene_node::attach_child(scene_node_ptr node)
{
    if (node->parent_ != nullptr)
        node->parent_->detach_child(node);

    node->parent_ = shared_from_this();
    node->parent_matrix_ = total_matrix_;
    children_.push_back(node);

    dirty_ = true;
}

void scene_node::detach_child(scene_node_ptr node)
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

void scene_node::attach_render_object(render_object_ptr object)
{
    render_objects_.push_back(object);
}

void scene_node::detach_render_object(render_object_ptr object)
{
    render_objects_.erase(std::remove(render_objects_.begin(), render_objects_.end(), object), render_objects_.end());
}

void scene_node::detach_all_render_objects()
{
    render_objects_.clear();
}

void scene_node::recalculate_matrices()
{
    if (!parent_)
        return;

    if (dirty_ || parent_->dirty_)
        total_matrix_ = matrix_ * parent_matrix_;

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

void scene_node::translate(float x, float y, float z)
{
    matrix_ = glm::translate(matrix_, glm::vec3(x, y, z));
    dirty_ = true;
}

void scene_node::translate(const glm::vec3 &vector)
{
    matrix_ = glm::translate(matrix_, vector);
    dirty_ = true;
}

void scene_node::rotate(float x, float y, float z)
{
    matrix_ = glm::rotate(matrix_, x, glm::vec3(1.0f, 0.0f, 0.0f));
    matrix_ = glm::rotate(matrix_, y, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix_ = glm::rotate(matrix_, z, glm::vec3(0.0f, 0.0f, 1.0f));
    dirty_ = true;
}

void scene_node::rotate(const glm::vec3 &vector)
{
    matrix_ = glm::rotate(matrix_, vector.x, glm::vec3(1.0f, 0.0f, 0.0f));
    matrix_ = glm::rotate(matrix_, vector.y, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix_ = glm::rotate(matrix_, vector.z, glm::vec3(0.0f, 0.0f, 1.0f));
    dirty_ = true;
}

void scene_node::rotate(float angle, const glm::vec3 &vector)
{
    matrix_ = glm::rotate(matrix_, angle, vector);
    dirty_ = true;
}

void scene_node::multiply(const glm::mat4 &matrix)
{
    matrix_ *= matrix;
    dirty_ = true;
}

} // namespace scene
} // namespace aeon
