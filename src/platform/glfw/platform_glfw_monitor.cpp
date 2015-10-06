/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <platform/glfw/platform_glfw_monitor.h>

namespace aeon
{
namespace platform
{
namespace glfw
{

platform_monitor::platform_monitor(GLFWmonitor *monitor, int width, int height,
                                   int x, int y, bool primary, const std::string &name) :
    platform::platform_monitor(width, height, x, y, primary, name),
    monitor_(monitor)
{
}

platform_monitor::~platform_monitor()
{
    monitor_ = nullptr;
}

void platform_monitor::set_gramma(float gamma)
{
    glfwSetGamma(monitor_, gamma);
}

gamma_ramp platform_monitor::get_gamma_ramp()
{
    const GLFWgammaramp *ramp = glfwGetGammaRamp(monitor_);
    gamma_ramp r;
    
    for (unsigned int i = 0; i < ramp->size; ++i)
    {
        r.push_back(gamma_ramp_data(ramp->red[i], ramp->green[i], ramp->blue[i]));
    }

    return r;
}

void platform_monitor::set_gamma_ramp(gamma_ramp ramp)
{
    GLFWgammaramp r;
    r.size = static_cast<unsigned int>(ramp.size());
    r.red = new unsigned short[r.size];
    r.green = new unsigned short[r.size];
    r.blue = new unsigned short[r.size];

    for (unsigned int i = 0; i < r.size; ++i)
    {
        r.red[i] = static_cast<unsigned short>(ramp[i].red);
        r.green[i] = static_cast<unsigned short>(ramp[i].green);
        r.blue[i] = static_cast<unsigned short>(ramp[i].blue);
    }

    glfwSetGammaRamp(monitor_, &r);

    delete [] r.red;
    delete [] r.green;
    delete [] r.blue;
}

video_mode platform_monitor::get_video_mode()
{
    const GLFWvidmode *vidmode = glfwGetVideoMode(monitor_);

    return video_mode(
        vidmode->width,
        vidmode->height,
        vidmode->redBits,
        vidmode->greenBits,
        vidmode->blueBits,
        vidmode->refreshRate
    );
}

video_modes platform_monitor::get_video_modes()
{
    int count;
    const GLFWvidmode *vidmodes = glfwGetVideoModes(monitor_, &count);

    video_modes modes;
    for (int i = 0; i < count; ++i)
    {
        modes.push_back(
            video_mode(
                vidmodes[i].width,
                vidmodes[i].height,
                vidmodes[i].redBits,
                vidmodes[i].greenBits,
                vidmodes[i].blueBits,
                vidmodes[i].refreshRate
            )
        );
    }

    return modes;
}

} // namespace glfw
} // namespace platform
} // namespace aeon
