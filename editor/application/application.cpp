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
#include <QFile>

namespace aeon
{
namespace editor
{

application::application(int argc, char *argv[])
    : qt_application_(argc, argv)
    , logger_backend_()
    , logger_(common::logger::get_singleton(), "AeonEditor")
    , platform_(argc, argv)
    , resource_manager_(platform_)
    , scene_manager_(device_)
    , asset_manager_(resource_manager_, scene_manager_)
    , mainwindow_(*this)
{
    apply_stylesheet();
}

int application::exec()
{
    mainwindow_.show();

    return qt_application_.exec();
}

void application::apply_stylesheet()
{
    QFile sheet(":/style/stylesheet");
    sheet.open(QFile::ReadOnly);
    QString styleSheet = sheet.readAll();
    qt_application_.setStyleSheet(styleSheet);
}

gfx::gl::gfx_gl_device &application::get_device()
{
    return device_;
}

resources::resource_manager &application::get_resource_manager()
{
    return resource_manager_;
}

scene::scene_manager &application::get_scene_manager()
{
    return scene_manager_;
}

assets::asset_manager & application::get_asset_manager()
{
    return asset_manager_;
}

} // namespace editor
} // namespace aeon
