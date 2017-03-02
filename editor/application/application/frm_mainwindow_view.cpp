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
#include <application.h>
#include <QSplitter>
#include <QLayout>
#include <QPushButton>

#include <aeon/editor_widgets/resource_manager_toolbar.h>

namespace aeon
{
namespace editor
{

frm_mainwindow_view::frm_mainwindow_view(application &app)
    : QMainWindow(nullptr)
    , ui_(std::make_unique<Ui::MainWindow>())
    , application_(app)
{
    ui_->setupUi(this);

    auto toolbar = ui_->toolBar;
    auto toolbar_2 = ui_->toolBar_2;

    auto widget = new widgets::resource_manager_toolbar();
    //auto widget = new QPushButton();

    //auto action = ui_->toolBar->actions().at(0);
    //widget->setMinimumSize(100, 60);
    auto action2 = toolbar_2->addWidget(widget);
    action2->setVisible(true);
    //widget->setVisible(true);

    //ui_->toolbar_->

    connect(ui_->actionAsset_Browser, &QAction::triggered, this, &frm_mainwindow_view::on_asset_browser_clicked);
}

void frm_mainwindow_view::on_asset_browser_clicked(bool checked)
{
}

frm_mainwindow_view::~frm_mainwindow_view() = default;

} // namespace editor
} // namespace aeon
