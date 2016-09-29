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

#include <editor_view.h>

namespace aeon
{
namespace editor
{

editor_view::editor_view(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QSurfaceFormat fmt;
    fmt.setVersion(3, 3);
    fmt.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(fmt);
    QSurfaceFormat::setDefaultFormat(fmt);
}

editor_view::~editor_view()
{
}

void editor_view::initializeGL()
{
}

void editor_view::resizeGL(int width, int height)
{
    //context_size_ = glm::vec2(width * devicePixelRatioF(), height * devicePixelRatioF());
}

void editor_view::paintGL()
{
    // Redraw...
    update();
}

} // namespace editor
} // namespace aeon
