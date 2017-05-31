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
#include <glm/mat4x4.hpp>
#include <vector>
#include <utility>
#include <memory>

namespace aeon
{
namespace scene
{

struct render_queue_object
{
    glm::mat4 matrix;
    std::shared_ptr<component> object;
    int group;
};

class render_queue
{
public:
    using render_queue_vector = std::vector<render_queue_object>;

    render_queue() = default;
    ~render_queue() = default;

    /*!
     * Add a renderable object to the queue. The group can be any number.
     * The groups are sorted in descending order, meaning higher numbers will get rendered first,
     * due to front to back rendering. Default groups are defined in render_layer::render_layer_enum.
     */
    void add_render_object(const glm::mat4 &matrix, const std::shared_ptr<component> &object, const int group);
    void clear_render_objects();

    void sort();

    auto begin() const
    {
        return objects_.cbegin();
    }

    auto end() const
    {
        return objects_.cend();
    }

private:
    render_queue_vector objects_;
};

} // namespace scene
} // namespace aeon
