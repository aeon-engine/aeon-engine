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

application::application()
    : aeon::desktop_application<aeon::scene::basic_scene_manager>(WINDOW_WIDTH, WINDOW_HEIGHT,
                                                                  "Example 6 - Mesh Loading")
    , timer_(0.0f)
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
    rotation_node_ = get_scene_manager()->create_child_scene_node();
    get_scene_manager()->get_root_scene_node()->attach_child(rotation_node_);

    rotation_node_->translate(0.0f, -1.5f, -10.0f);

    // Load resources
    wave_node_ =
        get_asset_manager().load_mesh("/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae");
    rotation_node_->attach_child(wave_node_);

    aeon::scene::scene_node_ptr skydome = get_asset_manager().load_mesh("resources/meshes/skysphere/skydome.dae");
    wave_node_->attach_child(skydome);
    skydome->scale(10.0f);
    skydome->translate(0.0f, -30.0f, 0.0f);

    // Start the render loop
    device_.run();
}

bool application::on_frame(float dt)
{
    rotation_node_->rotate(0.0f, -0.005f * dt, 0.0f);

    timer_ += dt;
    wave_node_->set_identity();
    wave_node_->translate(0.0f, 0.0f, sin(timer_ * 0.1f) * 4.0f);
    wave_node_->rotate(sin(timer_ * 0.1f) * 0.001f, 0.0f, 0.0f);
    return true;
}
