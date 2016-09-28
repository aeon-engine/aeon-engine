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

#include <application.h>
#include <frm_mainwindow_view.h>
#include <QFile>

namespace aeon
{
namespace editor
{

application::application(int argc, char *argv[])
    : qt_application_(argc, argv)
{
    apply_stylesheet();
}

int application::exec() const
{
    frm_mainwindow_view mainwindow;
    mainwindow.show();

    return qt_application_.exec();
}

void application::apply_stylesheet()
{
    QFile sheet(":/style/stylesheet");
    sheet.open(QFile::ReadOnly);
    QString styleSheet = sheet.readAll();
    qt_application_.setStyleSheet(styleSheet);
}

} // namespace editor
} // namespace aeon