/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/gfx/gles2/gfx_gles2_monitor.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_monitor::gfx_gles2_monitor(int width, int height, int x, int y, bool primary, const std::string &name)
    : gfx_monitor(width, height, x, y, primary, name)
{
}

void gfx_gles2_monitor::set_gramma(float)
{
}

gamma_ramp gfx_gles2_monitor::get_gamma_ramp()
{
    return gamma_ramp();
}

void gfx_gles2_monitor::set_gamma_ramp(gamma_ramp)
{
}

video_mode gfx_gles2_monitor::get_video_mode()
{
    throw std::runtime_error("not implemented.");
}

video_modes gfx_gles2_monitor::get_video_modes()
{
    throw std::runtime_error("not implemented.");
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
