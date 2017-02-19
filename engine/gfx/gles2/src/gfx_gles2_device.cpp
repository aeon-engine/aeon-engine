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

#include <aeon/gfx/gles2/gfx_gles2_texture_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_shader_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_material_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_buffer_manager.h>
#include <aeon/gfx/gles2/gfx_gles2_device.h>
#include <aeon/gfx/gles2/gfx_gles2_mesh.h>
#include <aeon/gfx/gles2/gfx_gles2_monitor.h>
#include <aeon/gfx/gles2/gfx_gles2_rpi_window.h>
#include <memory>
#include <aeon/gfx/gl_common/check_gl_error.h>

#include <bcm_host.h>
#include <GLES2/gl2.h>
#include <sys/time.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_device::gfx_gles2_device(platform::platform_interface &platform, input::input_handler &input_handler)
    : gfx::device(platform)
    , logger_(common::logger::get_singleton(), "Gfx::Gles2::Device")
    , input_handler_(input_handler)
    , render_targets_()
    , running_(false)
    , previous_time_(0.0)
{
}

gfx_gles2_device::~gfx_gles2_device()
{
}

void gfx_gles2_device::__initialize_impl()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing device." << std::endl;

    if (initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Initialize called while already initialized." << std::endl;
        throw gles2_initialized_exception();
    }

    initialized_ = true;
}

void gfx_gles2_device::set_clear_color(const common::types::color &c)
{
    glClearColor(c.r, c.g, c.b, c.a);
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_device::set_viewport(render_target &rt, viewport &vp)
{
    common::types::rectangle<float> vp_rel_rect = vp.get_rectangle();
    glm::vec2 framebuffer_size = rt.get_framebuffer_size();
    common::types::rectangle<int> vp_abs_rect = {static_cast<int>(vp_rel_rect.left() * framebuffer_size.x),
                                                 static_cast<int>(vp_rel_rect.top() * framebuffer_size.y),
                                                 static_cast<int>(vp_rel_rect.right() * framebuffer_size.x),
                                                 static_cast<int>(vp_rel_rect.bottom() * framebuffer_size.y)};

    glViewport(vp_abs_rect.left(), vp_abs_rect.top(), vp_abs_rect.right(), vp_abs_rect.bottom());
    AEON_CHECK_GL_ERROR();

    glScissor(vp_abs_rect.left(), vp_abs_rect.top(), vp_abs_rect.right(), vp_abs_rect.bottom());
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_device::clear_buffer(int buffer_flag)
{
    GLenum buffers = 0;

    if ((buffer_flag & gfx::buffer_clear_flag::color_buffer) != 0)
        buffers |= GL_COLOR_BUFFER_BIT;

    if ((buffer_flag & gfx::buffer_clear_flag::depth_buffer) != 0)
        buffers |= GL_DEPTH_BUFFER_BIT;

    glClear(buffers);
    AEON_CHECK_GL_ERROR();
}

std::unique_ptr<mesh> gfx_gles2_device::create_mesh(std::shared_ptr<material> material)
{
    return std::make_unique<gfx_gles2_mesh>(this, material);
}

std::vector<std::shared_ptr<gfx_monitor>> gfx_gles2_device::get_monitors()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error getting monitors. Gfx device not initialized." << std::endl;
        throw gles2_device_exception();
    }

    // Not implemented yet for GLES2.
    return {};
}

std::shared_ptr<gfx_window> gfx_gles2_device::create_window(const gfx_window_settings &settings,
                                                            std::shared_ptr<gfx_monitor> monitor)
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error creating window. Gfx device not initialized." << std::endl;
        throw gles2_device_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Creating window: " << settings.get_width() << "x" << settings.get_height() << " '"
                            << settings.get_title() << "'." << std::endl;

    // TODO: Create the right window for the right platform.
    std::shared_ptr<gfx_window> window = std::make_shared<gfx_gles2_rpi_window>(*this, platform_interface_, settings);

    // HACK: If there are no render targets yet, this is the first window that is being opened.
    // This means we can initialize opengl here.
    if (render_targets_.empty())
    {
        __create_managers();
        __setup_opengl();
    }

    render_targets_.push_back(window);

    return window;
}

void gfx_gles2_device::run()
{
    if (!initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Error starting message loop. Gfx device not initialized." << std::endl;
        throw gles2_device_exception();
    }

    AEON_LOG_DEBUG(logger_) << "Starting message loop." << std::endl;

    struct timeval t1, t2;
    struct timezone tz;

    gettimeofday(&t1, &tz);

    running_ = true;

    while (running_)
    {
        gettimeofday(&t2, &tz);
        float delta_time = static_cast<float>(t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) * 1e-6);
        t1 = t2;

         // TODO: handle input

        clear_buffer(gfx::buffer_clear_flag::color_buffer | gfx::buffer_clear_flag::depth_buffer);

        for (std::shared_ptr<render_target> &render_target : render_targets_)
        {
            if (!render_target->handle_frame(delta_time))
            {
                running_ = false;
                break;
            }
        }
    }

    AEON_LOG_DEBUG(logger_) << "Message loop stopped." << std::endl;
}

void gfx_gles2_device::stop()
{
    AEON_LOG_DEBUG(logger_) << "Stopping GLFW message loop." << std::endl;
    running_ = false;
}

input::input_handler &gfx_gles2_device::get_input_handler()
{
    return input_handler_;
}

void gfx_gles2_device::set_scissor(const common::types::rectangle<float> &scissor) const
{
    glScissor(static_cast<GLsizei>(scissor.left()), static_cast<GLsizei>(scissor.top()),
              static_cast<GLsizei>(scissor.width()), static_cast<GLsizei>(scissor.height()));
    AEON_CHECK_GL_ERROR();
}

void gfx_gles2_device::__create_managers()
{
    texture_manager_ = std::make_unique<gfx_gles2_texture_manager>();
    shader_manager_ = std::make_unique<gfx_gles2_shader_manager>();
    material_manager_ = std::make_unique<gfx_gles2_material_manager>();
    buffer_manager_ = std::make_unique<gfx_gles2_buffer_manager>();
    atlas_manager_ = std::make_unique<gfx_atlas_manager>();
}

void gfx_gles2_device::__setup_opengl() const
{
    glEnable(GL_DEPTH_TEST);
    AEON_CHECK_GL_ERROR();

    glDepthFunc(GL_LESS);
    AEON_CHECK_GL_ERROR();

    glEnable(GL_BLEND);
    AEON_CHECK_GL_ERROR();

    glEnable(GL_SCISSOR_TEST);
    AEON_CHECK_GL_ERROR();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    AEON_CHECK_GL_ERROR();

    glEnable(GL_CULL_FACE);
    AEON_CHECK_GL_ERROR();

    glCullFace(GL_BACK);
    AEON_CHECK_GL_ERROR();

    glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
    AEON_CHECK_GL_ERROR();
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
