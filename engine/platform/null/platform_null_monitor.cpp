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

#include <platform/null/platform_null_monitor.h>

namespace aeon
{
namespace platform
{
namespace null
{

platform_monitor::platform_monitor(int width, int height, int x, int y, bool primary, const std::string &name)
    : platform::platform_monitor(width, height, x, y, primary, name)
{
}

void platform_monitor::set_gramma(float)
{
}

gamma_ramp platform_monitor::get_gamma_ramp()
{
    return gamma_ramp();
}

void platform_monitor::set_gamma_ramp(gamma_ramp)
{
}

video_mode platform_monitor::get_video_mode()
{
    // TODO: Handle this better.
    return video_mode(1920, 1080, 8, 8, 8, 60);
}

video_modes platform_monitor::get_video_modes()
{
    return video_modes();
}

} // namespace null
} // namespace platform
} // namespace aeon
