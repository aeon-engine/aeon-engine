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
                                                                  "Example 5 - Multiple Viewports")
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Set up the scene. Because we are splitting the scene vertically, the camera only has half the window to
    // render to. This is why we divide the width by 2. If this is not done, the aspect ratio will look really strange.
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT, 0);

    // Create the left viewport
    aeon::common::types::rectangle<float> viewport_rect_left(0.0f, 0.0f, 0.5f, 1.0f);
    window_->create_viewport(camera_, viewport_rect_left, 0);

    // Create the right viewport
    aeon::common::types::rectangle<float> viewport_rect_right(0.5f, 0.0f, 0.5f, 1.0f);
    window_->create_viewport(camera_, viewport_rect_right, 0);
}

void application::main()
{
    // Load resources
    std::shared_ptr<aeon::gfx::material> ships_material = get_asset_manager().load_material("/resources/materials/ships.amf");

    // A sprite batch requires an atlas, we can either load one from an atlas file, or just generate one if
    // all the sprites have the same size and are properly aligned within the file.
    std::shared_ptr<aeon::gfx::atlas> atlas = get_asset_manager().create_atlas(ships_material, glm::vec2(64, 64));

    // Set up scene
    auto &root_node = scene_manager_.get_root_scene_node();

    // Put the ship in the center of the screen by translating the root node
    root_node.translate(200, 300);

    // Get a region from the atlas for the sprite to render. Here we grab the 10th sprite in the texture,
    // which is counted left to right, top to bottom.
    aeon::data::atlas::region region = atlas->get_region_by_index(10);

    // Create a sprite. The second parameter is the z-order; used to determine which sprite should be rendered on top
    auto ship_sprite = scene_manager_.create_scene_object<aeon::scene::sprite>(atlas, region, glm::vec2(64, 64), 0);

    // Attach the sprite to the scene
    root_node.attach_scene_object(ship_sprite);

    // Start the render loop
    device_.run();
}
