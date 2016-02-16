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
#include <scene/sprite_batch.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 3 - Sprite Animation")
    , turn_timer_(0.0f)
    , direction_(move_south)
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Attach this class as a frame listener
    get_main_window()->attach_listener(this);

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    window_->create_viewport(camera_, aeon::common::types::rectangle<int>(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT), 0);
}

void application::main(int, char *[])
{
    // Load resources
    aeon::gfx::material_ptr animation_material =
        resource_manager_.load_material("/resources/materials/2d_character.amf");
    aeon::resources::atlas_ptr atlas = std::make_shared<aeon::resources::atlas>(animation_material, glm::vec2(32, 32));

    // Set up scene
    aeon::scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();
    root_node->translate(400, 300);

    // Create a sprite batch. All sprites must be batched in order to be rendered
    aeon::scene::sprite_batch_ptr sprite_batch = scene_manager_.create_scene_object<aeon::scene::sprite_batch>(atlas);

    // The sprite batch must be attached to the scene.
    root_node->attach_scene_object(sprite_batch);

    // The parameter given to the animation settings constructor is the size of each frame inside of the sprite sheet
    // This frame size does not need to be a power of 2.
    aeon::scene::sprite_animation_settings animation_settings(glm::vec2(32, 32));

    // Sequences can be generated so that different animations can be played easily. The first parameter is a handle
    // that can be any number as long as it's unique to that animation. In this example we used an enum to give each
    // animation a name.
    // The 2nd parameter is the offset of the frame within the sprite sheet. Offsets are counted left to right, top to
    // bottom.
    // The 3rd parameter is how many frames should be animated. Again, these frames are counted left to right, top to
    // bottom.
    // The final parameter determines how the sequence of frames should be played, for example normally (1234),
    // reversed (4321), or back and forth (123432).
    animation_settings.generate_sequence(move_south, 0, 3, aeon::scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_west, 12, 3, aeon::scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_east, 24, 3, aeon::scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_north, 36, 3, aeon::scene::animation_sequence_type::up_down);

    // Set up the animation so that automaticly starts playing right away.
    animation_settings.set_start_condition(aeon::scene::animation_start_condition::auto_start);

    // The time in seconds each frame is visible
    animation_settings.set_speed(0.3f);

    // Set up the animation so that it keeps playing forever.
    animation_settings.set_repeat(aeon::scene::animation_repeat::continuous);

    animated_sprite_ =
        scene_manager_.create_scene_object<aeon::scene::animated_sprite>(sprite_batch, atlas, 0, animation_settings);
    root_node->attach_scene_object(animated_sprite_);

    platform_.run();
}

bool application::on_frame(float dt)
{
    turn_timer_ += dt;
    if (turn_timer_ > 5.0f)
    {
        direction_ = direction_ + 1;

        // Hack hack hack...
        if (direction_ > move_north)
            direction_ = move_south;

        animated_sprite_->set_animation_sequence(direction_);

        turn_timer_ = 0.0f;
    }

    return true;
}
