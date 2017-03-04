/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <QFile>
#include <aeon_editor_widgets_export.h>

namespace Ui
{
    class resource_manager_toolbar;
}

namespace aeon
{
namespace editor
{
namespace widgets
{

template <typename T>
class editor_widget : public T
{
public:
    explicit editor_widget(QWidget *parent = nullptr)
        : T(parent)
    {
        __apply_custom_stylesheet();
    }

    virtual ~editor_widget() = default;

private:
    void __apply_custom_stylesheet()
    {
        QFile sheet(":/aeon_editor_widgets/stylesheet");
        sheet.open(QFile::ReadOnly);
        auto styleSheet = sheet.readAll();
        this->setStyleSheet(styleSheet);
    }
};

} // namespace widgets
} // namespace editor
} // namespace aeon
