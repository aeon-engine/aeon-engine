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
#include <editor_view.h>
#include <application.h>
#include <QSplitter>
#include <QCloseEvent>
#include <aeon/resources/providers/filesystem_provider.h>
#include <editor_gl_device.h>

namespace aeon
{
namespace editor
{

frm_mainwindow_view::frm_mainwindow_view(application &app)
    : QMainWindow(nullptr)
    , ui_(std::make_unique<Ui::MainWindow>())
    , application_(app)
    , gl_initialized_(false)
    , count(0)
{
    ui_->setupUi(this);
    editor_view_ = new editor_view(this);
    setCentralWidget(editor_view_);
    editor_view_->makeCurrent();
}

frm_mainwindow_view::~frm_mainwindow_view() = default;

void frm_mainwindow_view::handle_gl_init()
{
    if (gl_initialized_)
        return;

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Glew init fail.");
    }

    application_.get_device().initialize_editor();

    application_.get_resource_manager().mount(std::make_shared<resources::filesystem_provider>("."), "/");

    camera_ =
        std::make_shared<scene::perspective_camera>(&application_.get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

    editor_view_->create_viewport(camera_, "view1", 0);

    auto &root_scene_node = application_.get_scene_manager().get_root_scene_node();
    auto mesh_node = application_.get_asset_manager().load_mesh("/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae");
    mesh_node->translate(0.0f, -1.5f, -10.0f);
    root_scene_node.attach_child(mesh_node);

    gl_initialized_ = true;
}

void frm_mainwindow_view::closeEvent(QCloseEvent *event)
{
    application_.get_scene_manager().cleanup_scene();
    application_.get_device().stop();
    event->accept();
}

} // namespace editor
} // namespace aeon
