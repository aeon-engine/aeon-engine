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

#include <aeon/gfx/gl/gfx_gl_texture_manager.h>
#include <aeon/gfx/gl/gfx_gl_shader_manager.h>
#include <aeon/gfx/gl/gfx_gl_material_manager.h>
#include <aeon/gfx/gl/gfx_gl_buffer_manager.h>
#include <aeon/gfx/gl/gfx_gl_device.h>
#include <aeon/gfx/gl/gfx_gl_mesh.h>
#include <aeon/gfx/gl/gfx_gl_monitor.h>
#include <aeon/gfx/gl/gfx_gl_window.h>
#include <memory>
#include <aeon/gfx/gl_common/check_gl_error.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

gfx_gl_device::gfx_gl_device(platform::platform_interface &platform)
    : gfx::device(platform)
    , logger_(common::logger::get_singleton(), "Gfx::GL::Device")
    , render_targets_()
    , running_(false)
    , previous_time_(0.0)
{
}

gfx_gl_device::~gfx_gl_device()
{
    if (initialized_)
        glfwTerminate();
}

void gfx_gl_device::__initialize_impl()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing device." << std::endl;

    if (initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Initialize called while already initialized." << std::endl;
        throw gl_initialized_exception();
    }

    __initialize_glfw();

    initialized_ = true;
}

void gfx_gl_device::set_clear_color(const common::types::color &c)
{
    glClearColor(c.r, c.g, c.b, c.a);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_device::set_viewport(render_target &rt, viewport &vp)
{
    common::types::rectangle<float> vp_rel_rect = vp.get_rectangle();
    glm::vec2 framebuffer_size = rt.get_framebuffer_size();
    common::types::rectangle<int> vp_abs_rect = {static_cast<int>(vp_rel_rect.x * framebuffer_size.x),
                                                 static_cast<int>(vp_rel_rect.y * framebuffer_size.y),
                                                 static_cast<int>(vp_rel_rect.width * framebuffer_size.x),
                                                 static_cast<int>(vp_rel_rect.height * framebuffer_size.y)};

    glViewport(vp_abs_rect.x, vp_abs_rect.y, vp_abs_rect.width, vp_abs_rect.height);
    AEON_CHECK_GL_ERROR();

    glScissor(vp_abs_rect.x, vp_abs_rect.y, vp_abs_rect.width, vp_abs_rect.height);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_device::clear_buffer(int buffer_flag)
{
    GLenum buffers = 0;

    if ((buffer_flag & gfx::buffer_clear_flag::color_buffer) != 0)
        buffers |= GL_COLOR_BUFFER_BIT;

    if ((buffer_flag & gfx::buffer_clear_flag::depth_buffer) != 0)
        buffers |= GL_DEPTH_BUFFER_BIT;

    glClear(buffers);
    AEON_CHECK_GL_ERROR();
}

mesh_ptr gfx_gl_device::create_mesh(material_ptr material)
{
    return std::make_unique<gfx_gl_mesh>(this, material);
}

gfx_monitors gfx_gl_device::get_monitors()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error getting monitors. Gfx device not initialized." << std::endl;
        throw gl_device_exception();
    }

    int count;
    GLFWmonitor **glfw_monitors = glfwGetMonitors(&count);
    GLFWmonitor *glfw_primary_monitor = glfwGetPrimaryMonitor();

    gfx_monitors monitors;

    for (int i = 0; i < count; ++i)
    {
        GLFWmonitor *m = glfw_monitors[i];

        int physical_width;
        int physical_height;
        glfwGetMonitorPhysicalSize(m, &physical_width, &physical_height);

        int x;
        int y;
        glfwGetMonitorPos(m, &x, &y);

        bool primary = (glfw_primary_monitor == m);

        const char *name = glfwGetMonitorName(m);

        monitors.emplace_back(
            std::make_shared<gfx_gl_monitor>(m, physical_width, physical_height, x, y, primary, name));
    }

    return monitors;
}

gfx_window_ptr gfx_gl_device::create_window(const gfx_window_settings &settings, gfx_monitor_ptr monitor)
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error creating window. Gfx device not initialized." << std::endl;
        throw gl_device_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Creating window: " << settings.get_width() << "x" << settings.get_height() << " '"
                            << settings.get_title() << "'." << std::endl;

    GLFWmonitor *glfw_monitor = nullptr;

    if (monitor)
    {
        std::shared_ptr<gfx_gl_monitor> m = std::dynamic_pointer_cast<gfx_gl_monitor>(monitor);
        glfw_monitor = m->get_internal_handle();
    }

    gfx_window_ptr window = std::make_shared<gfx_gl_window>(platform_interface_, settings, glfw_monitor);
    gfx_gl_window *gl_window = dynamic_cast<gfx_gl_window *>(window.get());

    // HACK: If there are no render targets yet, this is the first window that is being opened.
    // This means we can initialize opengl here.
    if (render_targets_.empty())
    {
        __create_managers();
        __setup_opengl();
        __initialize_glew();

        imgui_render_.initialize(*gl_window);
        window->attach_listener(&imgui_render_);
    }

    render_targets_.push_back(window);

    return window;
}

void gfx_gl_device::run()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error starting message loop. Gfx device not initialized." << std::endl;
        throw gl_device_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Starting message loop." << std::endl;

    previous_time_ = glfwGetTime();

    running_ = true;

    while (running_)
    {
        double current_time = glfwGetTime();
        double delta_time = current_time - previous_time_;
        previous_time_ = current_time;

        glfwPollEvents();

        clear_buffer(gfx::buffer_clear_flag::color_buffer | gfx::buffer_clear_flag::depth_buffer);

        for (gfx::render_target_ptr render_target : render_targets_)
        {
            if (!render_target->handle_frame(static_cast<float>(delta_time)))
            {
                running_ = false;
                break;
            }
        }
    }

    AEON_LOG_DEBUG(logger_) << "Message loop stopped." << std::endl;
}

void gfx_gl_device::stop()
{
    AEON_LOG_DEBUG(logger_) << "Stopping GLFW message loop." << std::endl;
    running_ = false;
}

void gfx_gl_device::__initialize_glfw() const
{
    AEON_LOG_MESSAGE(logger_) << "Initializing GLFW." << std::endl;

    int result = glfwInit();

    if (result == GL_FALSE)
    {
        AEON_LOG_FATAL(logger_) << "Could not initialize GLFW." << std::endl;
        throw gl_device_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Successfully initialized GLFW." << std::endl;
}

void gfx_gl_device::__create_managers()
{
    texture_manager_ = std::make_unique<gfx_gl_texture_manager>();
    shader_manager_ = std::make_unique<gfx_gl_shader_manager>();
    material_manager_ = std::make_unique<gfx_gl_material_manager>();
    buffer_manager_ = std::make_unique<gfx_gl_buffer_manager>();
    atlas_manager_ = std::make_unique<gfx_atlas_manager>();
}

void gfx_gl_device::__setup_opengl() const
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    AEON_CHECK_GL_ERROR();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    AEON_CHECK_GL_ERROR();

    glCullFace(GL_FRONT);
    AEON_CHECK_GL_ERROR();
}

void gfx_gl_device::__initialize_glew() const
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        AEON_LOG_FATAL(logger_) << "GLEW initialization failed." << std::endl;
        throw gl_device_exception();
    }

    // Squash all OpenGL errors from glewInit before continuing.
    __report_and_squash_glew_errors();
}

void gfx_gl_device::__report_and_squash_glew_errors() const
{
    int count = 0;
    while (glGetError() != GL_NO_ERROR)
    {
        if (count++ > 100)
        {
            AEON_LOG_FATAL(logger_) << "GLEW initialization reported too many OpenGL errors (> 100)." << std::endl;
            break;
        }
    }

    if (count > 0)
        AEON_LOG_WARNING(logger_) << "glewInit reported " << count << " OpenGL error(s)." << std::endl;
}

} // namespace gl
} // namespace gfx
} // namespace aeon
