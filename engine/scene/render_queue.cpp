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

render_queue::render_queue()
{
}

render_queue::~render_queue()
{
}

void render_queue::add_render_object(render_object_ptr object, int group)
{
    assert(group < render_layer::max);

    objects_.push_back({group, object});
}

void render_queue::clear_render_objects()
{
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
    std::sort(objects_.begin(), objects_.end(), [](const render_object_group_pair &a, const render_object_group_pair &b)
        {
            int real_a_prio = (a.first << 24) + a.second->get_priority();
            int real_b_prio = (b.first << 24) + b.second->get_priority();
            return real_a_prio < real_b_prio;
        }
    );
}

} // namespace scene
} // namespace aeon
