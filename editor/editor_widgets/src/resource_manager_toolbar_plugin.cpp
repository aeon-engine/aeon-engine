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

#include <resource_manager_toolbar_plugin.h>
#include <aeon/editor_widgets/resource_manager_toolbar.h>

namespace aeon
{
namespace editor
{
namespace widgets
{

resource_manager_toolbar_plugin::resource_manager_toolbar_plugin()
    : resource_manager_toolbar_plugin(nullptr)
{
}

resource_manager_toolbar_plugin::resource_manager_toolbar_plugin(QObject *parent)
    : QObject(parent)
    , initialized_(false)
{
}

resource_manager_toolbar_plugin::~resource_manager_toolbar_plugin() = default;

bool resource_manager_toolbar_plugin::isContainer() const
{
    return false;
}

bool resource_manager_toolbar_plugin::isInitialized() const
{
    return initialized_;
}

QIcon resource_manager_toolbar_plugin::icon() const
{
    return QIcon(":/aeon_editor_widgets/creator_icons/toolbar_icon");
}

QString resource_manager_toolbar_plugin::domXml() const
{
    return R"(
    <ui language="c++" displayname="Resource Manager Toolbar">
        <widget class="aeon::editor::widgets::resource_manager_toolbar" name="resource_manager_toolbar">
            <property name="geometry">
                <rect>
                    <x>0</x>
                    <y>0</y>
                    <width>282</width>
                    <height>23</height>
                </rect>
            </property>
            <property name="text">
                <string>ResourceManagerToolbar</string>
            </property>
        </widget>
    </ui>
    )";
}

QString resource_manager_toolbar_plugin::group() const
{
    return "Aeon Engine";
}

QString resource_manager_toolbar_plugin::includeFile() const
{
    return "aeon/editor_widgets/resource_manager_toolbar.h";
}

QString resource_manager_toolbar_plugin::name() const
{
    return "aeon::editor::widgets::resource_manager_toolbar";
}

QString resource_manager_toolbar_plugin::toolTip() const
{
    return "";
}

QString resource_manager_toolbar_plugin::whatsThis() const
{
    return "";
}

QWidget * resource_manager_toolbar_plugin::createWidget(QWidget *parent)
{
    return new resource_manager_toolbar(parent);
}

void resource_manager_toolbar_plugin::initialize(QDesignerFormEditorInterface *core)
{
    if (initialized_)
        return;

    initialized_ = true;
}

} // namespace widgets
} // namespace editor
} // namespace aeon
