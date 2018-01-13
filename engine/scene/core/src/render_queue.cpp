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

#include <aeon/scene/render_queue.h>
#include <algorithm>
#include <cassert>

namespace aeon
{
namespace scene
{

void render_queue::add_render_object(const glm::mat4 &matrix, const std::shared_ptr<component> &object, const int group)
{
    assert(group < render_layer::max);

    objects_.push_back(render_queue_object{matrix, object, group});
}

void render_queue::clear_render_objects()
{
    objects_.clear();
}

void render_queue::sort()
{
    std::sort(objects_.begin(), objects_.end(),
              [](const render_queue_object &a, const render_queue_object &b) { return a.group < b.group; });
}

} // namespace scene
} // namespace aeon
