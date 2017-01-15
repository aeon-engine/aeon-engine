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
#include <aeon/platform/generic/platform_generic_filesystem_interface.h>
#include <aeon/resources/providers/filesystem_provider.h>
#include <widgets/editor_view.h>
#include <frm_mainwindow_view.h>
#include <QCloseEvent>
#include <memory>

namespace aeon
{
namespace editor
{

editor_view::editor_view(frm_mainwindow_view *main_window, QWidget *parent)
    : QOpenGLWidget(parent)
    , timer_()
    , context_size_(0, 0)
    , main_window_(main_window)
    , platform_(std::make_unique<platform::generic::platform_filesystem_interface>())
    , input_handler_()
    , device_(platform_, input_handler_)
    , resource_manager_(platform_)
    , scene_manager_(device_)
    , asset_manager_(resource_manager_, scene_manager_)
    , gl_initialized_(false)
{
    timer_.start();
}

editor_view::~editor_view() = default;

void editor_view::make_current()
{
    makeCurrent();
}

glm::vec2 editor_view::get_framebuffer_size() const
{
    return context_size_;
}

void editor_view::__initialize_engine()
{
    if (gl_initialized_)
        return;

    make_current();

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Glew init fail.");
    }

    device_.initialize_editor();

    resource_manager_.mount(std::make_shared<resources::filesystem_provider>("."), "/");

    auto camera =
        std::make_shared<scene::perspective_camera>(&scene_manager_, 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

    create_viewport(camera, "view1", 0);

#if 0
    auto &root_scene_node = scene_manager_.get_root_scene_node();
    auto mesh_node = asset_manager_.load_mesh("/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae");
    mesh_node->translate(0.0f, -1.5f, -10.0f);
    root_scene_node.attach_child(mesh_node);
#endif

    gl_initialized_ = true;
}

bool editor_view::__on_frame_start(float)
{
    make_current();
    return true;
}

bool editor_view::__on_frame_end(float)
{
    return true;
}

void editor_view::initializeGL()
{
}

void editor_view::resizeGL(int width, int height)
{
    context_size_ = glm::vec2(width * devicePixelRatioF(), height * devicePixelRatioF());
    __initialize_engine();
}

void editor_view::paintGL()
{
    make_current();
    double time_diff_nsecs = static_cast<double>(timer_.nsecsElapsed());
    double time_diff_secs = time_diff_nsecs / 1000000000;
    handle_frame(time_diff_secs);
    timer_.restart();

    update();
}

void editor_view::closeEvent(QCloseEvent *event)
{
    scene_manager_.cleanup_scene();
    device_.stop();
    event->accept();
}

} // namespace editor
} // namespace aeon
