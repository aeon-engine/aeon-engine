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
#include <scene/sprite.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 4 - Input Handler (Use the arrow keys)")
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Attach this class as a frame listener
    get_main_window()->attach_listener(this);

    // Set up the scene
    camera_ = std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    window_->create_viewport(camera_, aeon::common::types::rectangle<int>(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0), 0);

    get_platform_interface()->get_input_handler()->attach_listener(this);
}

void application::main(int, char *[])
{
    // Load resources
    aeon::gfx::material_ptr ship_material = resource_manager_.load_material("/resources/materials/ship1.mat");

    // Set up scene
    aeon::scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();

    // Put the ship in the center of the screen by translating the root node
    root_node->translate(400, 300);

    // Create a sprite. The second parameter is the z-order; used to determine which sprite should be rendered on top
    aeon::scene::sprite_ptr ship_sprite = scene_manager_.create_render_object<aeon::scene::sprite>(ship_material, 0);

    // Attach the sprite to the scene
    root_node->attach_render_object(ship_sprite);

    // Start the render loop
    platform_.run();
}

bool application::on_frame(float dt)
{
    aeon::scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();
    root_node->rotate(movement_vector_.x * dt * 3.0f);
    root_node->translate(0, movement_vector_.y * dt * 200.0f);

    return true;
}


void application::on_keyboard_event(aeon::platform::platform_window * /*window*/, aeon::platform::keyboard_key key,
    aeon::platform::keyboard_key_state key_state, int /*modifier*/)
{
    std::cout << "Key: " << static_cast<int>(key) << " " << static_cast<int>(key_state) << std::endl;

    if (key == aeon::platform::keyboard_key::key_escape &&
        key_state == aeon::platform::keyboard_key_state::pressed)
    {
        platform_.stop();
    }

    if (key == aeon::platform::keyboard_key::key_up)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            movement_vector_.y = -1.0f;
        else
            movement_vector_.y = 0.0f;
    }
    else if (key == aeon::platform::keyboard_key::key_down)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            movement_vector_.y = 1.0f;
        else
            movement_vector_.y = 0.0f;
    }

    if (key == aeon::platform::keyboard_key::key_left)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            movement_vector_.x = -1.0f;
        else
            movement_vector_.x = 0.0f;
    }
    else if (key == aeon::platform::keyboard_key::key_right)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            movement_vector_.x = 1.0f;
        else
            movement_vector_.x = 0.0f;
    }
}

void application::on_mouse_button_event(aeon::platform::platform_window * /*window*/, aeon::platform::mouse_button button,
    aeon::platform::mouse_button_state button_state)
{
    std::cout << "Button: " << static_cast<int>(button) << " " << static_cast<int>(button_state) << std::endl;
}
