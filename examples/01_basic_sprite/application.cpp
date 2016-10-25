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
                                                                  "Example 1 - Basic Sprite")
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    window_->create_viewport(camera_, 0);

    aeon::gfx::gfx_window_settings settings(800, 600, "Test window 2");
    aeon::gfx::gfx_window_ptr window2 = device_.create_window(settings);

    aeon::scene::orthographic_camera_ptr camera2 =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    window2->create_viewport(camera2, 0);
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

    // Put the ship in the center of the screen by translating the root node
    root_node->translate(400, 300);

    // Get a region from the atlas for the sprite to render. Here we grab the 10th sprite in the texture,
    // which is counted left to right, top to bottom.
    aeon::data::atlas::region region = atlas->get_region_by_index(10);

    // Create a sprite. The second parameter is the z-order; used to determine which sprite should be rendered on top
    aeon::scene::sprite_ptr ship_sprite =
        scene_manager_.create_scene_object<aeon::scene::sprite>(atlas, region, glm::vec2(64, 64), 0);

    // Attach the sprite to the scene
    root_node->attach_scene_object(ship_sprite);

    // Start the render loop
    device_.run();
}
