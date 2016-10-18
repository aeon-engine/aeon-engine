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

#include "application.h"
#include <imgui.h>

const int WINDOW_WIDTH = 3840;
const int WINDOW_HEIGHT = 2160;

//3840x2160

application::application()
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 7 - Editor")
    , timer_(0.0f)
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Attach this class as a frame listener
    get_main_window()->attach_listener(this);
    get_input_handler().attach_listener(this);

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::perspective_camera>(get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    window_->create_viewport(camera_, 0);

    camera2_ =
        std::make_shared<aeon::scene::perspective_camera>(get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);
    aeon::common::types::rectangle<float> smaller_viewport_rect(0.1f, 0.1f, 0.3f, 0.3f);
    window_->create_viewport(camera2_, smaller_viewport_rect, 1);

    map_keys_glfw_to_imgui();
}

void application::main()
{
    rotation_node_ = get_scene_manager()->create_child_scene_node();
    get_scene_manager()->get_root_scene_node()->attach_child(rotation_node_);

    rotation_node_->translate(0.0f, -1.5f, -10.0f);

    // Load resources
    wave_node_ =
        get_asset_manager().load_mesh("/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae");
    rotation_node_->attach_child(wave_node_);

    aeon::scene::scene_node_ptr skydome = get_asset_manager().load_mesh("resources/meshes/skysphere/skydome.dae");
    wave_node_->attach_child(skydome);
    skydome->scale(10.0f);
    skydome->translate(0.0f, -30.0f, 0.0f);

    // Start the render loop
    device_.run();
}

bool application::on_frame_begin(const float dt)
{
    rotation_node_->rotate(0.0f, -0.005f * dt, 0.0f);

    timer_ += dt;
    wave_node_->set_identity();
    wave_node_->translate(0.0f, 0.0f, sin(timer_ * 0.1f) * 4.0f);
    wave_node_->rotate(sin(timer_ * 0.1f) * 0.001f, 0.0f, 0.0f);
    return true;
}

void application::on_keyboard_key_state_changed_event(aeon::input::keyboard_key key, aeon::input::keyboard_key_state key_state,
    int modifier)
{
    ImGuiIO& io = ImGui::GetIO();

    // don't allow unknown keys to fuckup everything
    if (key == aeon::input::keyboard_key::key_unknown)
        return;

    unsigned short temp_key = static_cast<unsigned short>(key);
    // don't allow buffer overrun because of valid keys that do not map to imgui key array
    if (temp_key >= sizeof(io.KeysDown))
        return;

    if (key_state == aeon::input::keyboard_key_state::pressed)
        io.KeysDown[temp_key] = true;
    if (key_state == aeon::input::keyboard_key_state::released)
        io.KeysDown[temp_key] = false;
   
    (void)modifier; // Modifiers are not reliable cross platform
    io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

    // Entering text shizzle
    if (key_state == aeon::input::keyboard_key_state::released)
    {
        if (temp_key > 0 && temp_key < 0x10000)
        {
            io.AddInputCharacter(temp_key);
        }
    }
}

void application::map_keys_glfw_to_imgui()
{
    ImGuiIO &io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    /*io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    */
}
