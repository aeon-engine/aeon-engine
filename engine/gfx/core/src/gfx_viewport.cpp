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

#include <aeon/gfx/gfx_viewport.h>

namespace aeon
{
namespace gfx
{

viewport::viewport(std::shared_ptr<gfx_camera> camera, const std::string &name, int zorder)
    : viewport(camera, common::types::rectangle<float>(0.0f, 0.0f, 1.0f, 1.0f), name, zorder)
{
}

viewport::viewport(std::shared_ptr<gfx_camera> camera, const common::types::rectangle<float> &rect,
                   const std::string &name, int zorder)
    : has_z_order(zorder)
    , camera_(camera)
    , rectangle_(rect)
    , name_(name)
{
}

void viewport::set_rectangle(const common::types::rectangle<float> &rect)
{
    rectangle_ = rect;
}

void viewport::set_camera(std::shared_ptr<gfx_camera> camera)
{
    camera_ = camera;
}

void viewport::update(render_target &rt, float dt)
{
    camera_->render_scene(rt, *this, dt);
}

} // namespace gfx
} // namespace aeon
