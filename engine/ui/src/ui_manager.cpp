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

#include <aeon/ui/ui_manager.h>
#include <imgui.h>

namespace aeon
{
namespace ui
{

ui_manager::ui_manager(gfx::device &device)
    : device_(device)
{
    device_.get_imgui_renderer().attach_listener(this);
}

ui_manager::~ui_manager()
{
    device_.get_imgui_renderer().detach_listener(this);
}

void ui_manager::on_render_ui()
{
    bool show_test_window = true;
    ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
    ImGui::ShowTestWindow(&show_test_window);
}

} // namespace ui
} // namespace aeon
