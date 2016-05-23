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

#include <platform/qt/platform_qt_opengl_widget.h>
#include <platform/qt/platform_qt_window.h>

namespace aeon
{
namespace platform
{
namespace qt
{

platform_qt_opengl_widget::platform_qt_opengl_widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , window_(nullptr)
{
    QSurfaceFormat fmt;
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(fmt);
    QSurfaceFormat::setDefaultFormat(fmt);
}

platform_qt_opengl_widget::~platform_qt_opengl_widget()
{
}

void platform_qt_opengl_widget::initializeGL()
{
}

void platform_qt_opengl_widget::resizeGL(int /*w*/, int /*h*/)
{
}

void platform_qt_opengl_widget::paintGL()
{
    window_->__handle_paint();
}

} // namespace qt
} // namespace platform
} // namespace aeon
