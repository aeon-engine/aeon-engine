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

#include <platform/null/platform_null_window.h>
#include <platform/null/platform_null_interface.h>

namespace aeon
{
namespace platform
{
namespace null
{

platform_window::platform_window(platform_interface *interface, int width, int height, const std::string &title)
    : platform::platform_window(width, height, title)
    , logger_(common::logger::get_singleton(), "Platform::Null")
    , interface_(interface)
{
    AEON_LOG_DEBUG(logger_) << "Creating null platform window." << std::endl;
}

platform_window::~platform_window()
{
    AEON_LOG_DEBUG(logger_) << "Window destructor called." << std::endl;
}

void platform_window::make_current()
{
}

glm::vec2 platform_window::get_framebuffer_size()
{
    return get_size();
}

bool platform_window::__on_frame_start(float)
{
    make_current();
    return true;
}

bool platform_window::__on_frame_end(float)
{
    return true;
}

} // namespace null
} // namespace platform
} // namespace aeon
