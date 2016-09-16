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

#include <platform/ios_qt/platform_ios_qt_interface.h>
#include <platform/ios_qt/platform_ios_qt_window.h>
#include <platform/generic/platform_generic_filesystem_interface.h>

namespace aeon
{
namespace platform
{
namespace qt
{

platform_interface::platform_interface(int argc, char *argv[])
    : platform::platform_interface(argc, argv, std::make_unique<generic::platform_filesystem_interface>())
    , logger_(common::logger::get_singleton(), "Platform::Qt")
    , application_(argc, argv)
    , initialized_(false)
{
}

platform_interface::~platform_interface()
{
}

void platform_interface::initialize()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing Qt." << std::endl;
    initialized_ = true;

    AEON_LOG_DEBUG(logger_) << "Successfully initialized Qt." << std::endl;
}

void platform_interface::run()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error starting message loop. Platform not initialized." << std::endl;
        throw platform_interface_initialize_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Starting message loop." << std::endl;

    application_.exec();

    AEON_LOG_DEBUG(logger_) << "Stopped message loop." << std::endl;
}

void platform_interface::stop()
{
    AEON_LOG_DEBUG(logger_) << "Stopping Qt message loop." << std::endl;
    application_.quit();
}

platform_monitors platform_interface::get_monitors()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error getting monitors. Platform not initialized." << std::endl;
        throw platform_interface_initialize_exception();
    }

    if (!initialized_)
        throw platform_interface_initialize_exception();

    platform_monitors monitors;
    return monitors;
}

platform::platform_window_ptr platform_interface::create_window(int /*width*/, int /*height*/,
                                                                const std::string & /*name*/,
                                                                platform_monitor_ptr monitor)
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error creating window. Platform not initialized." << std::endl;
        throw platform_interface_initialize_exception();
    }

    qt::platform_window_ptr window = std::make_shared<qt::platform_qt_window>(this);

    // HACK: If there are no render targets yet, this is the first window that is being opened.
    // This means we can initialize glew here.
    if (render_targets_.empty())
    {
        __initialize_glew();
    }

    render_targets_.push_back(window);

    return window;
}

void platform_interface::__initialize_glew() const
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        AEON_LOG_FATAL(logger_) << "GLEW initialization failed." << std::endl;
        throw platform_interface_initialize_exception();
    }

    // Squash all OpenGL errors from glewInit before continuing.
    __report_and_squash_glew_errors();
}

void platform_interface::__report_and_squash_glew_errors() const
{
    int count = 0;
    while (glGetError() != GL_NO_ERROR)
    {
        if (count++ > 100)
        {
            AEON_LOG_FATAL(logger_) << "GLEW initialization reported too many OpenGL errors (> 100)." << std::endl;
            break;
        }
    }

    if (count > 0)
        AEON_LOG_WARNING(logger_) << "glewInit reported " << count << " OpenGL error(s)." << std::endl;
}

} // namespace qt
} // namespace platform
} // namespace aeon
