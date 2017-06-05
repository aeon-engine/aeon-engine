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

#include "application.h"
#include <aeon/scene/components/sprite.h>
#include <aeon/application/default_context.h>
#include <aeon/resources/providers/filesystem_collection_provider.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const float SHIP_ROTATION_SPEED = 3.0f;
const float SHIP_ACCELERATION = 3.0f;
const float SHIP_MAX_SPEED = 2.0f;
const float SHIP_FRICTION = 2.0f;

application::application()
    : aeon::application::desktop_application(aeon::application::default_context::create())
    , move_direction_(ship_move_direction::none)
    , rotate_direction_(ship_rotate_direction::none)
    , forward_speed_(0.0f)
{
    // Init resources
    get_resource_manager().mount(
        std::make_unique<aeon::resources::filesystem_collection_provider>(get_io_interface(), "."), "/");

    // Attach this class as a frame listener
    get_main_window().attach_listener(this);

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    get_main_window().create_viewport(camera_, "viewport1", 0);

    get_input_handler().attach_listener(this);
}

void application::main()
{
    // Load resources
    auto ships_material = get_asset_manager().load_material("/resources/materials/ships.amf");

    // A sprite batch requires an atlas, we can either load one from an atlas file, or just generate one if
    // all the sprites have the same size and are properly aligned within the file.
    auto atlas = get_asset_manager().create_atlas(ships_material, glm::vec2(64, 64));

    // Get a region from the atlas for the sprite to render. Here we grab the 10th sprite in the texture,
    // which is counted left to right, top to bottom.
    auto region = atlas->get_region_by_index(10);

    ship_node_ = get_scene_manager().get_root_scene_node()->create_child_scene_node();

    // Put the ship in the center of the screen
    ship_node_->translate(400, 300);

    // Create a sprite. The last parameter is the z-order; used to determine which sprite should be rendered on top
    auto ship_sprite = get_scene_manager().create_component<aeon::scene::sprite>(atlas, region, 0);

    // Attach the sprite to the scene
    ship_node_->attach_component(ship_sprite);

    // Start the render loop
    get_platform().run();
}

auto application::on_frame_begin(const float dt) -> bool
{
    if (rotate_direction_ == ship_rotate_direction::left)
    {
        ship_node_->rotate(-SHIP_ROTATION_SPEED * dt);
    }
    else if (rotate_direction_ == ship_rotate_direction::right)
    {
        ship_node_->rotate(SHIP_ROTATION_SPEED * dt);
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

    ship_node_->translate(0, forward_speed_);

    return true;
}

void application::on_keyboard_key_state_changed_event(const aeon::input::keyboard_key key,
                                                      const aeon::input::keyboard_key_state key_state,
                                                      const int /*modifier*/)
{
    AEON_LOG_MESSAGE(get_logger()) << "Key: " << static_cast<int>(key) << " " << static_cast<int>(key_state)
                                   << std::endl;

    if (key == aeon::input::keyboard_key::key_escape && key_state == aeon::input::keyboard_key_state::pressed)
    {
        get_platform().stop();
    }

    if (key == aeon::input::keyboard_key::key_up)
    {
        if (key_state == aeon::input::keyboard_key_state::pressed)
            move_direction_ = ship_move_direction::forward;
        else
            move_direction_ = ship_move_direction::none;
    }

    if (key == aeon::input::keyboard_key::key_down)
    {
        if (key_state == aeon::input::keyboard_key_state::pressed)
            move_direction_ = ship_move_direction::reverse;
        else
            move_direction_ = ship_move_direction::none;
    }

    if (key == aeon::input::keyboard_key::key_left)
    {
        if (key_state == aeon::input::keyboard_key_state::pressed)
            rotate_direction_ = ship_rotate_direction::left;
        else
            rotate_direction_ = ship_rotate_direction::none;
    }

    if (key == aeon::input::keyboard_key::key_right)
    {
        if (key_state == aeon::input::keyboard_key_state::pressed)
            rotate_direction_ = ship_rotate_direction::right;
        else
            rotate_direction_ = ship_rotate_direction::none;
    }
}

void application::on_mouse_button_event(aeon::input::mouse_button button, aeon::input::mouse_button_state button_state)
{
    std::cout << "Button: " << static_cast<int>(button) << " " << static_cast<int>(button_state) << std::endl;
}
