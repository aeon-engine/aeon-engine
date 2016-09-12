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

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

application::application(int argc, char *argv[])
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(argc, argv, WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 6 - Mesh Loading")
{
    // Init resources
    get_resource_manager()->mount(std::make_shared<aeon::resources::filesystem_provider>("."), "/");

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::orthographic_camera>(get_scene_manager(), 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    window_->create_viewport(camera_, 0);
}

void application::main()
{
    // Load resources
    aeon::scene::scene_node_ptr node = get_asset_manager().load_mesh("/resources/meshes/teapot.dae");
    get_scene_manager()->get_root_scene_node()->attach_child(node);

    // Start the render loop
    platform_.run();
}
