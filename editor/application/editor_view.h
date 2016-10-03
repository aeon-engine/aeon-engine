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

#include <QtWidgets/QOpenGLWidget>
#include <gfx/gfx_render_target.h>
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

private:
    void make_current() override;
    glm::vec2 get_framebuffer_size() override;

    bool __on_frame_start(float dt) override;
    bool __on_frame_end(float dt) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    QElapsedTimer timer_;
    glm::vec2 context_size_;
    frm_mainwindow_view *main_window_;
};

} // namespace editor
} // namespace aeon
