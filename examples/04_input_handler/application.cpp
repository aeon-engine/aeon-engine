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
#include <scene/sprite_batch.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float SHIP_ROTATION_SPEED = 3.0f;
const float SHIP_ACCELERATION = 3.0f;
const float SHIP_MAX_SPEED = 2.0f;
const float SHIP_FRICTION = 2.0f;

application::application()
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 4 - Input Handler (Use the arrow keys)")
    , move_direction_(ship_move_direction::none)
    , rotate_direction_(ship_rotate_direction::none)
    , forward_speed_(0.0f)
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Attach this class as a frame listener
    get_main_window()->attach_listener(this);

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    window_->create_viewport(camera_, 0);

    get_platform_interface()->get_input_handler()->attach_listener(this);
}

void application::main(int, char *[])
{
    // Load resources
    aeon::gfx::material_ptr ships_material = resource_manager_.load_material("/resources/materials/ships.amf");

    // A sprite batch requires an atlas, we can either load one from an atlas file, or just generate one if
    // all the sprites have the same size and are properly aligned within the file.
    aeon::resources::atlas_ptr atlas = std::make_shared<aeon::resources::atlas>(ships_material, glm::vec2(64, 64));

    // Set up scene
    aeon::scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();

    // Put the ship in the center of the screen by translating the root node
    root_node->translate(400, 300);

    // Create a sprite batch. All sprites must be batched in order to be rendered
    aeon::scene::sprite_batch_ptr sprite_batch = scene_manager_.create_scene_object<aeon::scene::sprite_batch>(atlas);

    // The sprite batch must be attached to the scene.
    root_node->attach_scene_object(sprite_batch);

    // Get a region from the atlas for the sprite to render. Here we grab the 10th sprite in the texture,
    // which is counted left to right, top to bottom.
    aeon::resources::atlas_region region = atlas->get_region_by_index(10);

    // Create a sprite. The second parameter is the z-order; used to determine which sprite should be rendered on top
    aeon::scene::sprite_ptr ship_sprite =
        scene_manager_.create_scene_object<aeon::scene::sprite>(sprite_batch, region, 0);

    // Attach the sprite to the scene
    root_node->attach_scene_object(ship_sprite);

    // Start the render loop
    platform_.run();
}

bool application::on_frame(float dt)
{
    aeon::scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();

    if (rotate_direction_ == ship_rotate_direction::left)
    {
        root_node->rotate(-SHIP_ROTATION_SPEED * dt);
    }
    else if (rotate_direction_ == ship_rotate_direction::right)
    {
        root_node->rotate(SHIP_ROTATION_SPEED * dt);
    }

    if (move_direction_ == ship_move_direction::forward)
    {
        forward_speed_ -= SHIP_ACCELERATION * dt;

        if (forward_speed_ < -SHIP_MAX_SPEED)
            forward_speed_ = -SHIP_MAX_SPEED;
    }
    else if (move_direction_ == ship_move_direction::reverse)
    {
        forward_speed_ += SHIP_ACCELERATION * dt;

        if (forward_speed_ > SHIP_MAX_SPEED)
            forward_speed_ = SHIP_MAX_SPEED;
    }

    // Slow down to 0.
    if (move_direction_ == ship_move_direction::none)
    {
        if (forward_speed_ > 0.0f)
        {
            forward_speed_ -= SHIP_FRICTION * dt;

            if (forward_speed_ <= 0.0f)
                forward_speed_ = 0.0f;
        }
        else if (forward_speed_ < 0.0f)
        {
            forward_speed_ += SHIP_FRICTION * dt;

            if (forward_speed_ >= 0.0f)
                forward_speed_ = 0.0f;
        }
    }

    root_node->translate(0, forward_speed_);

    return true;
}

void application::on_keyboard_event(aeon::platform::platform_window * /*window*/, aeon::platform::keyboard_key key,
                                    aeon::platform::keyboard_key_state key_state, int /*modifier*/)
{
    std::cout << "Key: " << static_cast<int>(key) << " " << static_cast<int>(key_state) << std::endl;

    if (key == aeon::platform::keyboard_key::key_escape && key_state == aeon::platform::keyboard_key_state::pressed)
    {
        platform_.stop();
    }

    if (key == aeon::platform::keyboard_key::key_up)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            move_direction_ = ship_move_direction::forward;
        else
            move_direction_ = ship_move_direction::none;
    }

    if (key == aeon::platform::keyboard_key::key_down)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            move_direction_ = ship_move_direction::reverse;
        else
            move_direction_ = ship_move_direction::none;
    }

    if (key == aeon::platform::keyboard_key::key_left)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            rotate_direction_ = ship_rotate_direction::left;
        else
            rotate_direction_ = ship_rotate_direction::none;
    }

    if (key == aeon::platform::keyboard_key::key_right)
    {
        if (key_state == aeon::platform::keyboard_key_state::pressed)
            rotate_direction_ = ship_rotate_direction::right;
        else
            rotate_direction_ = ship_rotate_direction::none;
    }
}

void application::on_mouse_button_event(aeon::platform::platform_window * /*window*/,
                                        aeon::platform::mouse_button button,
                                        aeon::platform::mouse_button_state button_state)
{
    std::cout << "Button: " << static_cast<int>(button) << " " << static_cast<int>(button_state) << std::endl;
}
