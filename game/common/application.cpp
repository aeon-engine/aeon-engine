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

    resources::material_resource_wrapper_ptr mat_res =
        resource_manager_.load_material("/resources/materials/testmaterial.mat");
    resources::material_ptr mat = mat_res->open();
    material_ = device_.get_material_manager().load_material(mat);

    node_ = scene_manager_.get_root_scene_node();
    scene::sprite_ptr sprite1 = scene_manager_.create_render_object<scene::sprite>(material_, 10);

    sprite1->set_size(128, 128);

    node_->attach_render_object(sprite1);

    node_->translate(200, 200);

    scene::scene_node_ptr node2 = node_->create_child_scene_node();
    scene::sprite_ptr sprite2 = scene_manager_.create_render_object<scene::sprite>(material_, 5);

    node2->attach_render_object(sprite2);
    node2->translate(200, 0);

    platform_.run();

    // aeon::utility::configfile config_file;
    // std::string config_file_path = "config.ini";
    // config_file.load(std::make_shared<aeon::streams::file_stream>(config_file_path));
}

bool application::on_frame(double dt)
{
    static float time = 0;

    time += (float)dt;

    node_->rotate(static_cast<float>(dt));

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
