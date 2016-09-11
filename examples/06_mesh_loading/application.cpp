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

        // Attach this class as a frame listener
    get_main_window()->attach_listener(this);

    // Set up the scene
    camera_ =
        std::make_shared<aeon::scene::perspective_camera>(get_scene_manager(), 45.0f, 800.0f / 600.0f, 0.1f, 1000.0f);

    window_->create_viewport(camera_, 0);
}

void application::main()
{
    // Load resources
    node_ = get_asset_manager().load_mesh("/resources/meshes/teapot.dae");
    get_scene_manager()->get_root_scene_node()->attach_child(node_);

    node_->translate(0.0f, -1.2f, -5.0f);
    node_->rotate(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    node2_ = get_asset_manager().load_mesh("/resources/meshes/cube.dae");
    node_->attach_child(node2_);

    node2_->translate(0.0f, 0.0f, -10.0f);

    // Start the render loop
    platform_.run();
}

bool application::on_frame(float dt)
{
    (void) dt;
    node_->rotate(0.01f * dt, glm::vec3(0.0f, 0.0f, 1.0f));
    return true;
}
