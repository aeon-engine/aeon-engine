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
}

void application::main()
{
    auto &root_node = get_scene_manager()->get_root_scene_node();

    auto world = get_asset_manager().load_scene("/resources/scenes/testworld.asc");
    root_node.attach_child(world);

    camera_ = world->find_scene_object_by_name<aeon::scene::perspective_camera>("camera1");
    window_->create_viewport(camera_, "viewport1", 0);

    camera2_ = world->find_scene_object_by_name<aeon::scene::perspective_camera>("camera2");
    aeon::common::types::rectangle<float> smaller_viewport_rect(0.1f, 0.1f, 0.3f, 0.3f);
    window_->create_viewport(camera2_, smaller_viewport_rect, "viewport2", 1);

    rotation_node_ = root_node.find_child_by_name("rotation_node");

    staff_node_ = root_node.find_child_by_name("SUN Onlin7");
    staff_node_->set_position(0.5f, 0.0f, 0.0f);

    // Start the render loop
    device_.run();
}

bool application::on_frame_begin(const float dt)
{
    rotation_node_->rotate(0.0f, -0.1f * dt, 0.0f);
    staff_node_->rotate(-0.3f * dt, 0.0f, 0.0f);
    return true;
}
