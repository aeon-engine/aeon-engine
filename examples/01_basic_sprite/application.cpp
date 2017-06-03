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
#include <aeon/scene/components/sprite.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : aeon::application::desktop_application(aeon::application::default_context::create())
{
    // Set the log level to show only warnings and higher importance messages.
    // During initialization the engine may still print out debug or trace messages
    // depending on build settings.
    get_logger_backend().set_log_level(aeon::logger::log_level::warning);

    // Init resources
    get_resource_manager().mount(
        std::make_unique<aeon::resources::filesystem_collection_provider>(get_io_interface(), "."), "/");

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    get_main_window().create_viewport(camera_, "viewport1", 0);
}

void application::main()
{
    // Load resources
    auto ships_material = get_asset_manager().load_material("/resources/materials/ships.amf");

    // A sprite batch requires an atlas, we can either load one from an atlas file, or just generate one if
    // all the sprites have the same size and are properly aligned within the file.
    auto atlas = get_asset_manager().create_atlas(ships_material, glm::vec2(64, 64));

    // Set up scene
    auto &root_node = get_scene_manager().get_root_scene_node();

    // Put the ship in the center of the screen by translating the root node
    root_node.translate(400, 300);

    // Get a region from the atlas for the sprite to render. Here we grab the 10th sprite in the texture,
    // which is counted left to right, top to bottom.
    auto region = atlas->get_region_by_index(10);

    // Create a sprite. The last parameter is the z-order; used to determine which sprite should be rendered on top
    auto ship_sprite = get_scene_manager().create_component<aeon::scene::sprite>(atlas, region, 0);

    // Attach the sprite to the scene
    root_node.attach_component(ship_sprite);

    // Start the render loop
    get_platform().run();
}
