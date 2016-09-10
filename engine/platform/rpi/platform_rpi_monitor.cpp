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

#include <platform/rpi/platform_rpi_monitor.h>

namespace aeon
{
namespace platform
{
namespace rpi
{

platform_monitor::platform_monitor(int width, int height, int x, int y, bool primary,
                                   const std::string &name)
    : platform::platform_monitor(width, height, x, y, primary, name)
{
}

void platform_monitor::set_gramma(float)
{
    throw std::runtime_error("Not yet implemented.");
}

gamma_ramp platform_monitor::get_gamma_ramp()
{
    throw std::runtime_error("Not yet implemented.");
}

void platform_monitor::set_gamma_ramp(gamma_ramp)
{
    throw std::runtime_error("Not yet implemented.");
}

video_mode platform_monitor::get_video_mode()
{
    throw std::runtime_error("Not yet implemented.");
}

video_modes platform_monitor::get_video_modes()
{
    throw std::runtime_error("Not yet implemented.");
}

} // namespace rpi
} // namespace platform
} // namespace aeon
