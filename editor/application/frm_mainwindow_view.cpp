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
#include <resources/providers/filesystem_provider.h>

namespace aeon
{
namespace editor
{

frm_mainwindow_view::frm_mainwindow_view(application &app)
    : QMainWindow(nullptr)
    , ui_(new Ui::MainWindow)
    , application_(app)
{
    ui_->setupUi(this);

    QSplitter *vsplitter = new QSplitter(Qt::Vertical, this);
    QSplitter *hsplitter1 = new QSplitter(Qt::Horizontal, vsplitter);
    vsplitter->addWidget(hsplitter1);
    QSplitter *hsplitter2 = new QSplitter(Qt::Horizontal, vsplitter);
    vsplitter->addWidget(hsplitter2);

    editor_view *editor_view1 = new editor_view(hsplitter1);
    hsplitter1->addWidget(editor_view1);

    editor_view *editor_view2 = new editor_view(hsplitter1);
    hsplitter1->addWidget(editor_view2);

    editor_view *editor_view3 = new editor_view(hsplitter2);
    hsplitter2->addWidget(editor_view3);

    editor_view *editor_view4 = new editor_view(hsplitter2);
    hsplitter2->addWidget(editor_view4);

    setCentralWidget(vsplitter);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Glew init fail.");
    }

    application_.get_device().initialize();

    application_.get_resource_manager().mount(std::make_shared<resources::filesystem_provider>("."), "/");

    camera_ =
        std::make_shared<scene::perspective_camera>(&application_.get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

    editor_view1->create_viewport(camera_, 0);

    auto root_scene_node = application_.get_scene_manager().get_root_scene_node();
    auto mesh_node = application_.get_asset_manager().load_mesh("/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae");
    root_scene_node->attach_child(mesh_node);
}

frm_mainwindow_view::~frm_mainwindow_view()
{
    delete ui_;
}

} // namespace editor
} // namespace aeon
