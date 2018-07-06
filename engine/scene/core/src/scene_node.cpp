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

#include <aeon/scene/scene_node.h>
#include <algorithm>

namespace aeon
{
namespace scene
{

scene_node::scene_node(const std::string &name)
    : movable_object()
    , parent_matrix_(math::mat4::indentity())
    , total_matrix_(math::mat4::indentity())
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

void scene_node::attach_component(const std::shared_ptr<component> &object)
{
    object->__set_scene_node(this);
    components_.push_back(object);
}

void scene_node::detach_component(const std::shared_ptr<component> &object)
{
    object->__set_scene_node(nullptr);
    components_.erase(std::remove(components_.begin(), components_.end(), object), components_.end());
}

void scene_node::detach_all_components()
{
    for (auto &obj : components_)
        obj->__set_scene_node(nullptr);

    components_.clear();
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

    detach_all_components();
    detach_all_children();
}

auto scene_node::clone() -> std::shared_ptr<scene_node>
{
    auto node_copy = std::shared_ptr<scene_node>(new scene_node());
    node_copy->components_ = components_;
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

auto scene_node::__find_component_by_name(const std::string &name, const find_method method) const
    -> std::shared_ptr<component>
{
    for (auto &object : components_)
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
            auto result = node->__find_component_by_name(name, method);

            if (result != nullptr)
                return result;
        }
    }

    return nullptr;
}

} // namespace scene
} // namespace aeon
