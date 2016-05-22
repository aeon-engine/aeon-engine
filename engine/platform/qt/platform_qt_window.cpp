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

#include <platform/qt/platform_qt_window.h>
#include <platform/qt/platform_qt_interface.h>
#include <ui_mainwindow.h>

namespace aeon
{
namespace platform
{
namespace qt
{

platform_qt_window::platform_qt_window(platform_interface *i)
    : QMainWindow(nullptr)
    , platform::platform_window(800, 600, "Aeon Engine")
    , interface_(i)
    , ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    ui->openGLWidget->set_window(this);

    show();

    ui->openGLWidget->makeCurrent();
}

platform_qt_window::~platform_qt_window()
{
}

void platform_qt_window::__handle_paint()
{
    handle_frame(0.1f);
}

void platform_qt_window::make_current()
{
    ui->openGLWidget->makeCurrent();
}

bool platform_qt_window::__on_frame_start(float /*dt*/)
{
    make_current();
    return true;
}

bool platform_qt_window::__on_frame_end(float /*dt*/)
{
    return true;
}

glm::vec2 platform_qt_window::get_framebuffer_size()
{
    // TODO:
    return glm::vec2(800, 600);
}

} // namespace qt
} // namespace platform
} // namespace aeon
