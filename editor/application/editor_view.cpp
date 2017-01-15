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
#include <editor_view.h>
#include <frm_mainwindow_view.h>

namespace aeon
{
namespace editor
{

editor_view::editor_view(frm_mainwindow_view *main_window, QWidget *parent)
    : QOpenGLWidget(parent)
    , timer_()
    , context_size_(0, 0)
    , main_window_(main_window)
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
    make_current();
    main_window_->handle_gl_init();
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

} // namespace editor
} // namespace aeon
