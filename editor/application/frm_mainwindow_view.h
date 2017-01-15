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

#include <QtWidgets/QMainWindow>
#include <aeon/scene/perspective_camera.h>
#include <array>

namespace Ui
{
    class MainWindow;
}

namespace aeon
{
namespace editor
{

class editor_view;
class application;
class frm_mainwindow_view : public QMainWindow
{
    Q_OBJECT

public:
    frm_mainwindow_view(application &app);
    virtual ~frm_mainwindow_view();

private Q_SLOTS:
    void on_asset_browser_clicked(bool checked);

private:
    std::unique_ptr<Ui::MainWindow> ui_;
    application &application_;

    std::shared_ptr<scene::camera> camera_;
    int count;

    editor_view *editor_view_;
};

} // namespace editor
} // namespace aeon
