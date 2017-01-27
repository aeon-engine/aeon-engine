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

#include <GL/glew.h>
#include <frm_mainwindow_view.h>
#include <ui_frm_mainwindow.h>
#include <widgets/editor_view.h>
#include <resource_browser/resource_browser_view.h>
#include <application.h>
#include <QSplitter>

namespace aeon
{
namespace editor
{

frm_mainwindow_view::frm_mainwindow_view(application &app)
    : QMainWindow(nullptr)
    , ui_(std::make_unique<Ui::MainWindow>())
    , application_(app)
    , count(0)
{
    ui_->setupUi(this);
    editor_view_ = new editor_view(this);
    setCentralWidget(editor_view_);
    editor_view_->makeCurrent();

    connect(ui_->actionAsset_Browser, &QAction::triggered, this, &frm_mainwindow_view::on_asset_browser_clicked);
}

void frm_mainwindow_view::on_asset_browser_clicked(bool checked)
{
    resource_browser_view rb_view(this);
    rb_view.exec();
}

frm_mainwindow_view::~frm_mainwindow_view() = default;

} // namespace editor
} // namespace aeon