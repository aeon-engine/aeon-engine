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

#include <aeon/common/types/rectangle.h>
#include <aeon/common/has_z_order.h>
#include <aeon/gfx/gfx_camera.h>
#include <memory>
#include <string>

namespace aeon
{
namespace gfx
{

class render_target;

class viewport : public common::has_z_order
{
public:
    explicit viewport(std::shared_ptr<gfx_camera> camera, const std::string &name, int zorder = 0);
    explicit viewport(std::shared_ptr<gfx_camera> camera, const common::types::rectangle<float> &rect,
                      const std::string &name, int zorder = 0);
    virtual ~viewport() = default;

    void set_rectangle(const common::types::rectangle<float> &rect);

    void set_camera(std::shared_ptr<gfx_camera> camera);

    void update(render_target &rt, float dt);

    auto get_camera() const
    {
        return camera_;
    }

    auto get_rectangle() const
    {
        return rectangle_;
    }

    auto get_name() const
    {
        return name_;
    }

private:
    std::shared_ptr<gfx_camera> camera_;
    common::types::rectangle<float> rectangle_;
    std::string name_;
};

} // namespace gfx
} // namespace aeon
