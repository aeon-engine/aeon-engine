/*
 * Copyright (c) 2012-2018 Robin Degen
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
#include <aeon/scene/components/sprite.h>
#include <aeon/resources/providers/filesystem_collection_provider.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application()
    : aeon::application::desktop_application(aeon::application::default_context::create())
{
    // Init resources
    get_resource_manager().mount(
        std::make_unique<aeon::resources::filesystem_collection_provider>(get_io_interface(), "."), "/");

    get_main_window().attach_listener(this);

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
    auto atlas = get_asset_manager().create_atlas(ships_material, aeon::math::vector2<float>(64, 64));

    // Set up scene
    auto root_node = get_scene_manager().get_root_scene_node();
    root_node->translate(400, 300);

    auto ship1 = atlas->get_region_by_index(0);
    auto ship2 = atlas->get_region_by_index(4);
    auto ship3 = atlas->get_region_by_index(10);

    auto ship1_sprite = get_scene_manager().create_component<aeon::scene::sprite>(atlas, ship1, 0);
    root_node->attach_component(ship1_sprite);

    ship2_pivot_node_ = root_node->create_child_scene_node();
    auto ship2_node = ship2_pivot_node_->create_child_scene_node();
    ship2_node->translate(200.0f, 0.0f);

    auto ship2_sprite = get_scene_manager().create_component<aeon::scene::sprite>(atlas, ship2, 1);
    ship2_node->attach_component(ship2_sprite);

    ship3_pivot_node_ = ship2_node->create_child_scene_node();
    auto ship3_node = ship3_pivot_node_->create_child_scene_node();
    ship3_node->translate(100.0f, 0.0f);

    // Instead of just passing the atlas region, you can also manually pass a size to the sprite.
    // This will scale the sprite.
    auto ship3_sprite =
        get_scene_manager().create_component<aeon::scene::sprite>(atlas, ship3, aeon::math::vector2<float>(32, 32), 2);
    ship3_node->attach_component(ship3_sprite);

    get_platform().run();
}

auto application::on_frame_begin(const float dt) -> bool
{
    // Scene nodes can be moved every frame to move objects on the screen.
    ship2_pivot_node_->rotate(dt);
    ship3_pivot_node_->rotate(dt * -2.0f);

    return true;
}
