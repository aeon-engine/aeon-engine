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

namespace aeon
{
namespace editor
{

class editor_view : public QOpenGLWidget
{
    Q_OBJECT

public:
    editor_view(QWidget *parent = nullptr);
    ~editor_view() override;

private:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

} // namespace editor
} // namespace aeon
