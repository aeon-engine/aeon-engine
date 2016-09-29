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

#include <platform_interface.h>
#include <platform/generic/platform_generic_filesystem_interface.h>
#include <memory>
#include <GL/glew.h>

namespace aeon
{
namespace editor
{

platform_interface::platform_interface(int argc, char *argv[])
    : platform::platform_interface(argc, argv, std::make_unique<platform::generic::platform_filesystem_interface>())
    , logger_(common::logger::get_singleton(), "Platform::Editor")
    , initialized_(false)
{
}

platform_interface::~platform_interface()
{
}

void platform_interface::initialize()
{
    throw platform::platform_exception();
}

void platform_interface::run()
{
    throw platform::platform_exception();
}

void platform_interface::stop()
{
    throw platform::platform_exception();
}

platform::platform_monitors platform_interface::get_monitors()
{
    throw platform::platform_exception();
}

platform::platform_window_ptr platform_interface::create_window(const platform::platform_window_settings &settings,
    platform::platform_monitor_ptr monitor)
{
    throw platform::platform_exception();
}

} // namespace editor
} // namespace aeon
