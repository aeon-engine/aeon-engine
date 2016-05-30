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
    , context_size_(0, 0)
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

glm::vec2 platform_qt_opengl_widget::get_context_size() const
{
    return context_size_;
}

void platform_qt_opengl_widget::initializeGL()
{
}

void platform_qt_opengl_widget::resizeGL(int width, int height)
{
    context_size_ = glm::vec2(width, height);
}

void platform_qt_opengl_widget::paintGL()
{
    window_->__handle_paint();
    update();
}

} // namespace qt
} // namespace platform
} // namespace aeon
