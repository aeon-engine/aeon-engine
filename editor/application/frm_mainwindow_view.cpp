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
    , gl_initialized_(false)
    , count(0)
{
    ui_->setupUi(this);

    QSplitter *vsplitter = new QSplitter(Qt::Vertical, this);
    QSplitter *hsplitter1 = new QSplitter(Qt::Horizontal, vsplitter);
    vsplitter->addWidget(hsplitter1);
    QSplitter *hsplitter2 = new QSplitter(Qt::Horizontal, vsplitter);
    vsplitter->addWidget(hsplitter2);

    editor_views[0] = new editor_view(this, hsplitter1);
    hsplitter1->addWidget(editor_views[0]);

    editor_views[1] = new editor_view(this, hsplitter1);
    hsplitter1->addWidget(editor_views[1]);

    editor_views[2] = new editor_view(this, hsplitter2);
    hsplitter2->addWidget(editor_views[2]);

    editor_views[3] = new editor_view(this, hsplitter2);
    hsplitter2->addWidget(editor_views[3]);
    
    setCentralWidget(vsplitter);

    /*editor_view *editor_view1 = new editor_view(this);
    setCentralWidget(editor_view1);*/

    editor_views[0]->makeCurrent();
}

frm_mainwindow_view::~frm_mainwindow_view()
{
    delete ui_;
}

void frm_mainwindow_view::handle_gl_init()
{
    // hack to make sure all the contexts are there before trying to load anything
    if (++count < 4)
        return;

    // hack hack
    if (gl_initialized_)
        return;

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Glew init fail.");
    }

    application_.get_device().initialize();
    //application_.get_device().set_clear_color(common::types::color(1, 0, 0, 1));

    application_.get_resource_manager().mount(std::make_shared<resources::filesystem_provider>("."), "/");

    cameras_[0] =
        std::make_shared<scene::perspective_camera>(&application_.get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    cameras_[1] =
        std::make_shared<scene::perspective_camera>(&application_.get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    cameras_[2] =
        std::make_shared<scene::perspective_camera>(&application_.get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    cameras_[3] =
        std::make_shared<scene::perspective_camera>(&application_.get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

    editor_views[0]->create_viewport(cameras_[0], 0);
    editor_views[1]->create_viewport(cameras_[1], 0);
    editor_views[2]->create_viewport(cameras_[2], 0);
    editor_views[3]->create_viewport(cameras_[3], 0);

    auto root_scene_node = application_.get_scene_manager().get_root_scene_node();
    auto mesh_node = application_.get_asset_manager().load_mesh("/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae");
    mesh_node->translate(0.0f, -1.5f, -10.0f);
    root_scene_node->attach_child(mesh_node);

    gl_initialized_ = true;
}

} // namespace editor
} // namespace aeon
