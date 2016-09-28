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

#include <frm_mainwindow_view.h>
#include <ui_frm_mainwindow.h>
#include <QSplitter>
#include <QOpenGLWidget>

namespace aeon
{
namespace editor
{

frm_mainwindow_view::frm_mainwindow_view()
    : QMainWindow(nullptr)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    QSplitter *vsplitter = new QSplitter(Qt::Vertical, this);
    QSplitter *hsplitter1 = new QSplitter(Qt::Horizontal, vsplitter);
    vsplitter->addWidget(hsplitter1);
    QSplitter *hsplitter2 = new QSplitter(Qt::Horizontal, vsplitter);
    vsplitter->addWidget(hsplitter2);

    hsplitter1->addWidget(new QOpenGLWidget(hsplitter1));
    hsplitter1->addWidget(new QOpenGLWidget(hsplitter1));

    hsplitter2->addWidget(new QOpenGLWidget(hsplitter2));
    hsplitter2->addWidget(new QOpenGLWidget(hsplitter2));

    setCentralWidget(vsplitter);
}

frm_mainwindow_view::~frm_mainwindow_view()
{
    delete ui_;
}

} // namespace editor
} // namespace aeon
