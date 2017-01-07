/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
        std::make_shared<aeon::scene::perspective_camera>(get_scene_manager(), 70.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
    window_->create_viewport(camera_, 0);

    camera2_ =
        std::make_shared<aeon::scene::perspective_camera>(get_scene_manager(), 70.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
    aeon::common::types::rectangle<float> smaller_viewport_rect(0.1f, 0.1f, 0.3f, 0.3f);
    window_->create_viewport(camera2_, smaller_viewport_rect, 1);
}

void application::main()
{
    auto camera1_node = get_scene_manager()->create_child_scene_node();
    camera1_node->attach_scene_object(camera_);
    camera1_node->set_position(0.0f, 0.0f, 10.0f);

    auto camera2_node = get_scene_manager()->create_child_scene_node();
    camera2_node->attach_scene_object(camera2_);
    camera2_node->set_position(0.0f, 0.0f, -10.0f);
    camera2_node->rotate(glm::vec3(0.0f, glm::pi<float>(), 0.0f));

    rotation_node_ = get_scene_manager()->create_child_scene_node();
    get_scene_manager()->get_root_scene_node().attach_child(rotation_node_);

    // Load resources
    auto female_warrior =
        get_asset_manager().load_mesh("/resources/meshes/elementalist-warrior-female-character-f/x-elemetal.dae");
    rotation_node_->attach_child(female_warrior);
    rotation_node_->set_position(2.0f, 0.0f, 0.0f);

    auto skydome = get_asset_manager().load_mesh("resources/meshes/skysphere/skydome.dae");
    skydome->set_position(0.0f, -30.0f, 0.0f);
    skydome->scale(10.0f);
    get_scene_manager()->get_root_scene_node().attach_child(skydome);

    // Start the render loop
    device_.run();
}

bool application::on_frame_begin(const float dt)
{
    rotation_node_->rotate(0.0f, -0.5f * dt, 0.0f);
    return true;
}
