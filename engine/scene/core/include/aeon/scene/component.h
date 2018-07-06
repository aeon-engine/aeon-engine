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

#include <aeon/scene/render_layer.h>
#include <aeon/common/noncopyable.h>
#include <aeon/math/mat4.h>
#include <string>

namespace aeon
{
namespace scene
{

enum component_render_type
{
    renderable,
    spatial
};

class render_queue;
class scene_node;
class scene_manager;

class component : public common::noncopyable
{
    friend class scene_node;

public:
    explicit component(const std::string &name, const int queue_group, component_render_type render_type,
                       scene_manager &scene_manager)
        : queue_group_(queue_group)
        , render_type_(render_type)
        , scene_manager_(scene_manager)
        , scene_node_(nullptr)
        , name_(name)
    {
    }

    virtual ~component() = default;

    auto get_render_type() const
    {
        return render_type_;
    }

    auto get_queue_group() const
    {
        return queue_group_;
    }

    auto get_name() const
    {
        return name_;
    }

    /*!
     * Called by the render queue when rendering. For some objects rendering
     * doesn't make sense (like camera's). In that case, this function must be
     * used to set up the matrices and/or buffers.
     */
    virtual void render(const math::mat4 & /*projection*/, const math::mat4 & /*view*/, const math::mat4 & /*model*/,
                        const float /*dt*/)
    {
    }

    /*!
     * Get the calculated matrix from the scene node. If this object is not attached
     * to any scene node, an identity matrix will be returned.
     */
    auto get_scene_matrix() const -> math::mat4;

protected:
    void __set_scene_node(scene_node *node)
    {
        scene_node_ = node;
    }

    int queue_group_;
    component_render_type render_type_;
    scene_manager &scene_manager_;
    scene_node *scene_node_;
    std::string name_;
};

} // namespace scene
} // namespace aeon
