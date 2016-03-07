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
#include <resources/providers/filesystem_provider.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application(int argc, char *argv[])
    : aeon::aeon_application(argc, argv)
    , scene_manager_(*get_gfx_device())
{
}

aeon::application_settings application::configure_application_settings()
{
    aeon::application_settings settings;
    settings.window_title_hint = "Example 1 - Basic Sprite";
    return settings;
}

void application::setup()
{
    std::string executable_path = get_platform_interface()->get_filesystem_interface()->get_executable_path();

    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>(executable_path), "/");

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(scene_manager_, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    get_platform_interface()->get_default_window()->create_viewport(camera_, 0);

    // Load resources
    aeon::gfx::material_ptr ships_material = resource_manager_.load_material("ships.amf");

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
}
