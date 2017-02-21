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
#include <aeon/gfx/gfx_monitor.h>
#include <GLFW/glfw3.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class gfx_gl_monitor : public gfx_monitor
{
public:
    gfx_gl_monitor(GLFWmonitor *monitor, int width, int height, int x, int y, bool primary, const std::string &name);
    virtual ~gfx_gl_monitor() = default;

    void set_gramma(float gamma) override;

    gamma_ramp get_gamma_ramp() override;
    void set_gamma_ramp(gamma_ramp ramp) override;

    video_mode get_video_mode() override;
    video_modes get_video_modes() override;

    GLFWmonitor *get_internal_handle() const
    {
        return monitor_;
    }

private:
    GLFWmonitor *monitor_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
