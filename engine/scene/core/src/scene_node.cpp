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
#include <algorithm>

namespace aeon
{
namespace scene
{

scene_node::scene_node(const std::string &name)
    : movable_object()
    , is_root_(false)
    , name_(name)
{
}

auto scene_node::create_child_scene_node(const std::string &name) -> std::shared_ptr<scene_node>
{
    auto node = std::shared_ptr<scene_node>(new scene_node(name));
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

    if (is_dirty() || parent_dirty)
        total_matrix_ = parent_matrix_ * get_matrix();

    dirty_ = true;

    for (auto &node : children_)
    {
        node->parent_matrix_ = total_matrix_;
        node->recalculate_matrices();
    }

    dirty_ = false;
}

auto scene_node::get_children_refs() const -> std::vector<std::reference_wrapper<scene_node>>
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

auto scene_node::find_child_by_name(const std::string &name, const find_method method) const -> scene_node *
{
    for (auto &node : children_)
    {
        if (node->get_name() == name)
        {
            return node.get();
        }
    }

    if (method == find_method::recursive)
    {
        // This loop should be seperate since we want to search in order of depth.
        for (auto &node : children_)
        {
            auto result = node->find_child_by_name(name, method);

            if (result != nullptr)
                return result;
        }
    }

    return nullptr;
}

auto scene_node::__find_scene_object_by_name(const std::string &name, const find_method method) const
    -> std::shared_ptr<scene_object>
{
    for (auto &object : scene_objects_)
    {
        if (object->get_name() == name)
        {
            return object;
        }
    }

    if (method == find_method::recursive)
    {
        // This loop should be seperate since we want to search in order of depth.
        for (auto &node : children_)
        {
            auto result = node->__find_scene_object_by_name(name, method);

            if (result != nullptr)
                return result;
        }
    }

    return nullptr;
}

} // namespace scene
} // namespace aeon
