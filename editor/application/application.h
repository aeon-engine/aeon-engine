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

#include <aeon/utility.h>
#include <platform_interface.h>
#include <gfx/gl/gfx_gl_device.h>
#include <resources/resource_manager.h>
#include <scene/scene_managers/basic/basic_scene_manager.h>
#include <assets/asset_manager.h>
#include <QtWidgets/QApplication>
#include <frm_mainwindow_view.h>

namespace aeon
{
namespace editor
{

class application : utility::noncopyable
{
public:
    application(int argc, char *argv[]);
    ~application() = default;

    int exec();

    gfx::gl::gfx_gl_device &get_device();
    resources::resource_manager &get_resource_manager();
    scene::scene_manager &get_scene_manager();
    assets::asset_manager &get_asset_manager();

private:
    void apply_stylesheet();

    QApplication qt_application_;

    common::logger logger_backend_;
    aeon::logger::logger logger_;

    platform_interface platform_;
    gfx::gl::gfx_gl_device device_;

    resources::resource_manager resource_manager_;
    scene::basic_scene_manager scene_manager_;
    assets::asset_manager asset_manager_;
    frm_mainwindow_view mainwindow_;
};

} // namespace editor
} // namespace aeon
