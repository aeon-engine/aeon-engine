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

namespace aeon
{

application::application()
    : resource_manager_(platform_)
    , scene_manager_(device_)
{
    __setup_console();

    platform_.initialize();
    window_ = platform_.create_window(800, 600, "Test");
    window_->attach_frame_listener(this);

    device_.initialize();

    resource_manager_.mount(std::make_shared<resources::filesystem_provider>("."), "/");
}

application::~application()
{
}

void application::main(int, char *[])
{
    resources::material_resource_wrapper_ptr mat_res =
        resource_manager_.load_material("/resources/materials/testmaterial.mat");
    resources::material_ptr mat = mat_res->open();
    resources::image_resource_wrapper_ptr img_res = mat->get_texture_resource();
    resources::image_ptr img = img_res->open();

    texture_ = device_.get_texture_manager().load_texture(img);

    img->clear_data();

    platform_.run();

    // aeon::utility::configfile config_file;
    // std::string config_file_path = "config.ini";
    // config_file.load(std::make_shared<aeon::streams::file_stream>(config_file_path));
}

bool application::on_frame(double dt)
{
    static float time = 0;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D);

    texture_->bind();

    float ratio = 800.0f / 600.0f;
    //glViewport(0, 0, 800, 600);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float)time * 50.0f, 0.f, 0.f, 1.f);

    glBegin(GL_TRIANGLES);
    //glColor3f(1.f, 0.f, 0.f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    //glColor3f(0.f, 1.f, 0.f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(0.6f, -0.4f, 0.f);
    //glColor3f(0.f, 0.f, 1.f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();

    glFlush();

    time += (float)dt;

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
