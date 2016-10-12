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
#include <aeon/scene/sprite.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 2 - Scene Manager")
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    get_main_window()->attach_listener(this);

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    window_->create_viewport(camera_, 0);
}

void application::main()
{
    // Load resources
    aeon::gfx::material_ptr ships_material = get_asset_manager().load_material("/resources/materials/ships.amf");

    // A sprite batch requires an atlas, we can either load one from an atlas file, or just generate one if
    // all the sprites have the same size and are properly aligned within the file.
    aeon::gfx::atlas_ptr atlas = get_asset_manager().create_atlas(ships_material, glm::vec2(64, 64));

    // Set up scene
    aeon::scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();
    root_node->translate(400, 300);

    aeon::data::atlas::region ship1 = atlas->get_region_by_index(0);
    aeon::data::atlas::region ship2 = atlas->get_region_by_index(4);
    aeon::data::atlas::region ship3 = atlas->get_region_by_index(10);

    aeon::scene::sprite_ptr ship1_sprite =
        scene_manager_.create_scene_object<aeon::scene::sprite>(atlas, ship1, glm::vec2(64, 64), 0);
    root_node->attach_scene_object(ship1_sprite);

    ship2_pivot_node_ = root_node->create_child_scene_node();
    aeon::scene::scene_node_ptr ship2_node = ship2_pivot_node_->create_child_scene_node();
    ship2_node->translate(200.0f, 0.0f);

    aeon::scene::sprite_ptr ship2_sprite =
        scene_manager_.create_scene_object<aeon::scene::sprite>(atlas, ship2, glm::vec2(64, 64), 1);
    ship2_node->attach_scene_object(ship2_sprite);

    ship3_pivot_node_ = ship2_node->create_child_scene_node();
    aeon::scene::scene_node_ptr ship3_node = ship3_pivot_node_->create_child_scene_node();
    ship3_node->translate(100.0f, 0.0f);

    aeon::scene::sprite_ptr ship3_sprite =
        scene_manager_.create_scene_object<aeon::scene::sprite>(atlas, ship3, glm::vec2(64, 64), 2);
    ship3_node->attach_scene_object(ship3_sprite);

    device_.run();
}

bool application::on_frame_begin(const float dt)
{
    // Scene nodes can be moved every frame to move objects on the screen.
    ship2_pivot_node_->rotate(dt);
    ship3_pivot_node_->rotate(dt * -2.0f);

    return true;
}
