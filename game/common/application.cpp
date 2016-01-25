/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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
#include <common/application.h>
#include <console/console.h>

#include <platform/glfw/platform_glfw_interface.h>
#include <resources/resource_manager.h>
#include <resources/providers/filesystem_provider.h>
#include <resources/wrappers/image_resource_wrapper.h>
#include <resources/image.h>
#include <gfx/gl/gfx_gl_device.h>
#include <scene/scene_managers/basic/basic_scene_manager.h>

namespace aeon
{

application::application()
{
}

application::~application()
{
}

gfx::texture_ptr t;

void application::main(int, char *[])
{
    __setup_console();

    platform::glfw::platform_interface i;
    i.initialize();
    platform::platform_monitors m = i.get_monitors();
    platform::video_modes vms = m[0]->get_video_modes();

    platform::platform_window_ptr window = i.create_window(800, 600, "Test");

    window->attach_frame_listener(this);

    resources::resource_manager mgr(i);
    resources::resource_provider_ptr provider = std::make_shared<resources::filesystem_provider>(".");
    mgr.mount(provider, "/");

    resources::image_resource_wrapper_ptr img_res = mgr.load_image("/resources/textures/test.png");
    resources::image_ptr img = img_res->open();

    scene::basic_scene_manager sm;

    gfx::gl::device d;
    t = d.get_texture_manager().load_texture(img);

    std::cout << img->get_width();

    i.run();

    // aeon::utility::configfile config_file;
    // std::string config_file_path = "config.ini";
    // config_file.load(std::make_shared<aeon::streams::file_stream>(config_file_path));
}

bool application::on_frame(double dt)
{
    static float time = 0;

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_TEXTURE_2D);

    t->bind();

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
