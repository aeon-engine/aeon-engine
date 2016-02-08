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

#include <aeon/utility.h>
#include <common/application.h>
#include <scene/sprite.h>

namespace aeon
{

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : desktop_application(WINDOW_WIDTH, WINDOW_HEIGHT, "Test")
    , turn_timer_(0.0f)
    , direction_(move_south)
{
    get_main_window()->attach_frame_listener(this);

    // Set up the scene
    camera_ = std::make_shared<scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    window_->create_viewport(camera_, common::types::rectangle<int>(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0), 0);
}

void application::main(int, char *[])
{
    // Load resources
    gfx::material_ptr ship1_material = resource_manager_.load_material("/resources/materials/ship1.mat");
    gfx::material_ptr ship2_material = resource_manager_.load_material("/resources/materials/ship2.mat");
    gfx::material_ptr ship3_material = resource_manager_.load_material("/resources/materials/ship3.mat");
    gfx::material_ptr animation_material = resource_manager_.load_material("/resources/materials/2d_character.mat");

    // Set up scene
    scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();
    root_node->translate(400, 300);

    scene::sprite_ptr ship1_sprite = scene_manager_.create_render_object<scene::sprite>(ship1_material, 0);
    root_node->attach_render_object(ship1_sprite);

    ship2_pivot_node_ = root_node->create_child_scene_node();
    scene::scene_node_ptr ship2_node = ship2_pivot_node_->create_child_scene_node();
    ship2_node->translate(200.0f, 0.0f);

    scene::sprite_ptr ship2_sprite = scene_manager_.create_render_object<scene::sprite>(ship2_material, 1);
    ship2_node->attach_render_object(ship2_sprite);

    ship3_pivot_node_ = ship2_node->create_child_scene_node();
    scene::scene_node_ptr ship3_node = ship3_pivot_node_->create_child_scene_node();
    ship3_node->translate(100.0f, 0.0f);

    scene::sprite_ptr ship3_sprite = scene_manager_.create_render_object<scene::sprite>(ship3_material, 1);
    ship3_node->attach_render_object(ship3_sprite);

    scene::scene_node_ptr animated_node = root_node->create_child_scene_node();
    animated_node->translate(-300, -200);

    scene::sprite_animation_settings animation_settings(glm::vec2(32, 32));
    animation_settings.generate_sequence(move_south, 0, 3, scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_west, 12, 3, scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_east, 24, 3, scene::animation_sequence_type::up_down);
    animation_settings.generate_sequence(move_north, 36, 3, scene::animation_sequence_type::up_down);

    animation_settings.set_start_condition(scene::animation_start_condition::auto_start);
    animation_settings.set_speed(0.3f);
    animation_settings.set_repeat(scene::animation_repeat::continuous);

    animated_sprite_ = scene_manager_.create_render_object<scene::animated_sprite>(
        animation_material, 10, animation_settings);
    animated_node->attach_render_object(animated_sprite_);

    platform_.run();
}

bool application::on_frame(float dt)
{
    ship2_pivot_node_->rotate(dt);
    ship3_pivot_node_->rotate(dt * -2.0f);

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


} // namespace aeon
