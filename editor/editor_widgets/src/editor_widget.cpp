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

#include <aeon/editor_widgets/editor_widget.h>
#include <QFile>

namespace aeon
{
namespace editor
{
namespace widgets
{

editor_widget::editor_widget(QWidget *parent)
    : QFrame(parent)
{
    __apply_custom_stylesheet();
}

editor_widget::~editor_widget() = default;

void editor_widget::__apply_custom_stylesheet()
{
    QFile sheet(":/aeon_editor_widgets/style/stylesheet");
    sheet.open(QFile::ReadOnly);
    QString styleSheet = sheet.readAll();
    setStyleSheet(styleSheet);
}

} // namespace widgets
} // namespace editor
} // namespace aeon
