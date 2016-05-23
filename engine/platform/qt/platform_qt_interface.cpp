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

#include <platform/qt/platform_qt_interface.h>
#include <platform/qt/platform_qt_window.h>
#include <platform/generic/platform_generic_filesystem_interface.h>
#include <gl/glew.h>

namespace aeon
{
namespace platform
{
namespace qt
{

platform_interface::platform_interface(int argc, char *argv[])
    : platform::platform_interface(argc, argv, std::make_unique<generic::platform_filesystem_interface>())
    , application_(argc, argv)
    , initialized_(false)
{
}

platform_interface::~platform_interface()
{
}

void platform_interface::initialize()
{
    initialized_ = true;
}

void platform_interface::run()
{
    if (!initialized_)
        throw platform_interface_initialize_exception();

    application_.exec();
}

void platform_interface::stop()
{
    application_.quit();
}

platform_monitors platform_interface::get_monitors()
{
    if (!initialized_)
        throw platform_interface_initialize_exception();

    platform_monitors monitors;
    return monitors;
}

platform::platform_window_ptr platform_interface::create_window(int /*width*/, int /*height*/,
                                                                const std::string & /*name*/,
                                                                platform_monitor_ptr monitor)
{
    qt::platform_window_ptr window = std::make_shared<qt::platform_qt_window>(this);
    render_targets_.push_back(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw platform_interface_initialize_exception();
    }

    return window;
}

} // namespace qt
} // namespace platform
} // namespace aeon
