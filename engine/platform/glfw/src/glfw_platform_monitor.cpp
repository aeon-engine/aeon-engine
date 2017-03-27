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

#include <aeon/platform/glfw/glfw_platform_monitor.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

glfw_monitor::glfw_monitor(GLFWmonitor *monitor, int width, int height, int x, int y, bool primary,
                           const std::string &name)
    : monitor(width, height, x, y, primary, name)
    , monitor_(monitor)
{
}

void glfw_monitor::set_gramma(float gamma)
{
    glfwSetGamma(monitor_, gamma);
}

auto glfw_monitor::get_gamma_ramp() -> gamma_ramp
{
    const auto *ramp = glfwGetGammaRamp(monitor_);
    auto r = gamma_ramp();

    for (unsigned int i = 0; i < ramp->size; ++i)
    {
        r.push_back({ramp->red[i], ramp->green[i], ramp->blue[i]});
    }

    return r;
}

void glfw_monitor::set_gamma_ramp(gamma_ramp ramp)
{
    auto r = GLFWgammaramp{};
    r.red = new unsigned short[r.size];
    r.green = new unsigned short[r.size];
    r.blue = new unsigned short[r.size];
    r.size = static_cast<unsigned int>(ramp.size());

    for (unsigned int i = 0; i < r.size; ++i)
    {
        r.red[i] = static_cast<unsigned short>(ramp[i].red);
        r.green[i] = static_cast<unsigned short>(ramp[i].green);
        r.blue[i] = static_cast<unsigned short>(ramp[i].blue);
    }

    glfwSetGammaRamp(monitor_, &r);

    delete[] r.red;
    delete[] r.green;
    delete[] r.blue;
}

auto glfw_monitor::get_video_mode() -> video_mode
{
    const auto *vidmode = glfwGetVideoMode(monitor_);

    return {vidmode->width,     vidmode->height,   vidmode->redBits,
            vidmode->greenBits, vidmode->blueBits, vidmode->refreshRate};
}

auto glfw_monitor::get_video_modes() -> video_modes
{
    int count;
    const auto *vidmodes = glfwGetVideoModes(monitor_, &count);

    auto modes = video_modes{};
    for (int i = 0; i < count; ++i)
    {
        modes.push_back({vidmodes[i].width, vidmodes[i].height, vidmodes[i].redBits, vidmodes[i].greenBits,
                         vidmodes[i].blueBits, vidmodes[i].refreshRate});
    }

    return modes;
}

} // namespace glfw
} // namespace platform
} // namespace aeon
