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

#include <core/editor_gl_device.h>

#include <aeon/gfx/gfx_render_target.h>
#include <aeon/resources/resource_manager.h>
#include <aeon/scene/basic_scene_manager/basic_scene_manager.h>
#include <aeon/assets/asset_manager.h>
#include <aeon/input/input_handler.h>

#include <QtWidgets/QOpenGLWidget>
#include <QElapsedTimer>

namespace aeon
{
namespace editor
{

class frm_mainwindow_view;
class editor_view : public QOpenGLWidget, public gfx::render_target
{
Q_OBJECT

public:
    editor_view(frm_mainwindow_view *main_window, QWidget *parent = nullptr);
    ~editor_view() override;

    void make_current() override;
    glm::vec2 get_framebuffer_size() const override;

private:
    void __initialize_engine();

    bool __on_frame_start(float dt) override;
    bool __on_frame_end(float dt) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void closeEvent(QCloseEvent *event) override;

    QElapsedTimer timer_;
    glm::vec2 context_size_;
    frm_mainwindow_view *main_window_;

    platform::platform_interface platform_;
    input::input_handler input_handler_;
    editor_gl_device device_;

    resources::resource_manager resource_manager_;
    scene::basic_scene_manager scene_manager_;
    assets::asset_manager asset_manager_;

    bool gl_initialized_;
};

} // namespace editor
} // namespace aeon
