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
#include <aeon/application/default_context.h>
#include <aeon/resources/providers/filesystem_collection_provider.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : aeon::application::desktop_application(aeon::application::default_context::create())
    , turn_timer_(0.0f)
    , direction_(move_south)
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
}

void application::main()
{
    // Load resources
    auto animation_material = get_asset_manager().load_material("/resources/materials/valheim.amf");
    auto atlas = get_asset_manager().create_atlas(animation_material, glm::vec2(32, 32));

    // Set up scene
    auto root_node = get_scene_manager().get_root_scene_node();
    root_node->translate(400, 300);

    // The parameter given to the animation settings constructor is the size of each frame inside of the sprite sheet
    // This frame size does not need to be a power of 2.
    auto animation_settings = aeon::scene::sprite_animation_settings(glm::vec2(128, 128));

    // Sequences can be generated so that different animations can be played easily. The first parameter is a handle
    // that can be any number as long as it's unique to that animation. In this example we used an enum to give each
    // animation a name.
    // The 2nd parameter is the offset of the frame within the sprite sheet. Offsets are counted left to right, top to
    // bottom.
    // The 3rd parameter is how many frames should be animated. Again, these frames are counted left to right, top to
    // bottom.
    // The final parameter determines how the sequence of frames should be played, for example normally (1234),
    // reversed (4321), or back and forth (123432).
    animation_settings.generate_sequence(move_south, 3, 3, aeon::scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_west, 15, 3, aeon::scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_east, 27, 3, aeon::scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_north, 39, 3, aeon::scene::animation_sequence_type::up_down);

    // Set up the animation so that automaticly starts playing right away.
    animation_settings.set_start_condition(aeon::scene::animation_start_condition::auto_start);

    // The time in seconds each frame is visible
    animation_settings.set_speed(0.3f);

    // Set up the animation so that it keeps playing forever.
    animation_settings.set_repeat(aeon::scene::animation_repeat::continuous);

    animated_sprite_ = get_scene_manager().create_component<aeon::scene::animated_sprite>(atlas, 0, animation_settings);
    root_node->attach_component(animated_sprite_);

    get_platform().run();
}

auto application::on_frame_begin(const float dt) -> bool
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
