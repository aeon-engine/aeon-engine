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

#include <scene/render_object.h>
#include <vector>
#include <utility>
#include <glm/mat4x4.hpp>

namespace aeon
{
namespace scene
{

struct render_queue_object
{
    glm::mat4 matrix;
    render_object_ptr object;
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
    void add_render_object(const glm::mat4 &matrix, render_object_ptr object, int group);
    void clear_render_objects();

    void sort();

    render_queue_vector::const_iterator begin() const;
    render_queue_vector::const_iterator end() const;

private:
    render_queue_vector objects_;
};

} // namespace scene
} // namespace aeon
