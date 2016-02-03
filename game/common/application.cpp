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

#include <aeon/utility.h>
#include <aeon/streams.h>
#include <common/application.h>
#include <console/console.h>
#include <scene/sprite.h>

namespace aeon
{

application::application()
    : resource_manager_(platform_)
    , scene_manager_(device_)
{
    __setup_console();

    // Init the platform and window
    platform_.initialize();
    window_ = platform_.create_window(800, 600, "Test");
    window_->attach_frame_listener(this);

    // Init opengl
    device_.initialize();

    // Init resources
    resource_manager_.mount(std::make_shared<resources::filesystem_provider>("."), "/");

    // Set up the scene
    camera_ = std::make_shared<scene::orthographic_camera>(&scene_manager_, 0.0f, 800.0f, 600.0f, 0.0f);

    window_->create_viewport(camera_, common::types::rectangle<float>(0.0f, 800.0f, 600.0f, 0.0f), 0);
}

application::~application()
{
}

void application::main(int, char *[])
{
    // Load resources
    resources::material_resource_wrapper_ptr ship1_res =
        resource_manager_.load_material("/resources/materials/ship1.mat");
    resources::material_ptr ship1_material_data = ship1_res->open();
    gfx::material_ptr ship1_material = device_.get_material_manager().load_material(ship1_material_data);

    resources::material_resource_wrapper_ptr ship2_res =
        resource_manager_.load_material("/resources/materials/ship2.mat");
    resources::material_ptr ship2_material_data = ship2_res->open();
    gfx::material_ptr ship2_material = device_.get_material_manager().load_material(ship2_material_data);

    resources::material_resource_wrapper_ptr ship3_res =
        resource_manager_.load_material("/resources/materials/ship3.mat");
    resources::material_ptr ship3_material_data = ship3_res->open();
    gfx::material_ptr ship3_material = device_.get_material_manager().load_material(ship3_material_data);

    // Set up scene
    scene::scene_node_ptr root_node = scene_manager_.get_root_scene_node();
    root_node->translate(400, 300);

    scene::sprite_ptr ship1_sprite = scene_manager_.create_render_object<scene::sprite>(ship1_material, 0);
    root_node->attach_render_object(ship1_sprite);

    ship2_pivot_node_ = root_node->create_child_scene_node();
    scene::scene_node_ptr ship2_node = ship2_pivot_node_->create_child_scene_node();
    ship2_node->translate(200.0f, 0.0f);

    scene::sprite_ptr ship2_sprite = scene_manager_.create_render_object<scene::sprite>(ship2_material, 1);
    ship2_node->attach_render_object(ship2_sprite);

    ship3_pivot_node_ = ship2_node->create_child_scene_node();
    scene::scene_node_ptr ship3_node = ship3_pivot_node_->create_child_scene_node();
    ship3_node->translate(100.0f, 0.0f);

    scene::sprite_ptr ship3_sprite = scene_manager_.create_render_object<scene::sprite>(ship3_material, 1);
    ship3_node->attach_render_object(ship3_sprite);

    platform_.run();

    // aeon::utility::configfile config_file;
    // std::string config_file_path = "config.ini";
    // config_file.load(std::make_shared<aeon::streams::file_stream>(config_file_path));
}

bool application::on_frame(double dt)
{
    static float time = 0;

    time += (float)dt;

    ship2_pivot_node_->rotate(static_cast<float>(dt));
    ship3_pivot_node_->rotate(static_cast<float>(dt) * -2.0f);

    return true;
}

void application::__setup_console()
{
    // Set up debug logging
    aeon::console::set_loglevel(aeon::console::log_level::debug);

    // Create console streams
    auto console_stdoutput = std::make_shared<aeon::streams::io_stream>(aeon::streams::access_mode::write);

    // console_stdoutput->set_color(aeon::streams::color::blue, aeon::streams::weight::bold);

    std::string console_log_file = "console.log";
    auto console_fileoutput =
        std::make_shared<aeon::streams::file_stream>(console_log_file, aeon::streams::access_mode::write);

    // Create listeners with these streams
    // auto console_std_listener =
    //    std::make_shared<aeon::console_stream_listener>(console_stdoutput);
    // auto console_file_listener =
    //    std::make_shared<aeon::console_stream_listener>(console_fileoutput);

    // Bind a default console
    // aeon::console::add_console_listener(console_std_listener);
    // aeon::console::add_console_listener(console_file_listener);
}

} // namespace aeon
