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

#include <scene/render_queue.h>
#include <algorithm>
#include <cassert>

namespace aeon
{
namespace scene
{

void render_queue::add_render_object(const glm::mat4 &matrix, scene_object_ptr object, int group)
{
    assert(group < render_layer::max);

    objects_.push_back(render_queue_object{matrix, object, group});
}

void render_queue::clear_render_objects()
{
    objects_.clear();
}

render_queue::render_queue_vector::const_iterator render_queue::begin() const
{
    return objects_.cbegin();
}

render_queue::render_queue_vector::const_iterator render_queue::end() const
{
    return objects_.cend();
}

void render_queue::sort()
{
    std::sort(objects_.begin(), objects_.end(),
              [](const render_queue_object &a, const render_queue_object &b) { return a.group < b.group; });
}

} // namespace scene
} // namespace aeon
