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

#pragma once

#include <QtWidgets/QOpenGLWidget>

namespace aeon
{
namespace platform
{
namespace qt
{

class platform_qt_window;
class platform_qt_opengl_widget : public QOpenGLWidget
{
Q_OBJECT

public:
    platform_qt_opengl_widget(QWidget *parent = nullptr);
    ~platform_qt_opengl_widget() override;

    void set_window(platform_qt_window *window)
    {
        window_ = window;
    }

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    platform_qt_window *window_;
};

} // namespace qt
} // namespace platform
} // namespace aeon
