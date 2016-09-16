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
#include <platform/platform_window.h>
#include <QtWidgets/QMainWindow>
#include <QElapsedTimer>
#include <memory>

namespace Ui
{
class mainwindow;
}

namespace aeon
{
namespace platform
{
namespace qt
{

class platform_interface;
class platform_qt_window : public QMainWindow, public platform::platform_window
{
    Q_OBJECT

    friend class platform_qt_opengl_widget;

public:
    platform_qt_window(platform_interface *i);
    ~platform_qt_window() override;

private:
    void __handle_paint();

    void make_current() override;

    bool __on_frame_start(float dt) override;

    bool __on_frame_end(float dt) override;

    glm::vec2 get_framebuffer_size() override;

    QElapsedTimer timer_;
    platform_interface *interface_;
    Ui::mainwindow *ui;
};

using platform_window_ptr = std::shared_ptr<platform_window>;

} // namespace qt
} // namespace platform
} // namespace aeon
