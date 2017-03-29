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

#include <aeon/platform/rpi/rpi_platform_monitor.h>
#include <aeon/platform/platform_manager.h>

namespace aeon
{
namespace platform
{
namespace rpi
{

void rpi_monitor::set_gramma(float /*gamma*/)
{
    // TODO: Implement for SDL.
    throw platform_exception();
}

auto rpi_monitor::get_gamma_ramp() -> gamma_ramp
{
    // TODO: Implement for SDL.
    throw platform_exception();
}

void rpi_monitor::set_gamma_ramp(gamma_ramp /*ramp*/)
{
    // TODO: Implement for SDL.
    throw platform_exception();
}

auto rpi_monitor::get_video_mode() -> video_mode
{
    // TODO: Implement for SDL.
    throw platform_exception();
}

auto rpi_monitor::get_video_modes() -> video_modes
{
    // TODO: Implement for SDL.
    throw platform_exception();
}

} // namespace rpi
} // namespace platform
} // namespace aeon
