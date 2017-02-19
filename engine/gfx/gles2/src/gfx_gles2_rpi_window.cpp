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

#include <aeon/gfx/gles2/gfx_gles2_rpi_window.h>
#include <aeon/gfx/gles2/gfx_gles2_device.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <bcm_host.h>

// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB 0
// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA 1
// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH 2
// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL 4
// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE 8

namespace aeon
{
namespace gfx
{
namespace gles2
{

gfx_gles2_rpi_window::gfx_gles2_rpi_window(gfx_gles2_device &device, platform::platform_interface &,
                                           const gfx_window_settings &settings)
    : gfx_window(settings)
    , logger_(common::logger::get_singleton(), "Gfx::GLES2::Window")
    , device_(device)
{
    AEON_LOG_DEBUG(logger_) << "Creating GLES 2 context with forward compatibility." << std::endl;

    // TODO: This should be moved elsewhere, since it only needs to happen once.
    bcm_host_init();

    __create_window();
}

gfx_gles2_rpi_window::~gfx_gles2_rpi_window()
{
}

void gfx_gles2_rpi_window::make_current()
{
    if (!eglMakeCurrent(display_, surface_, surface_, context_))
        throw std::runtime_error("Failed to make current.");
}

glm::vec2 gfx_gles2_rpi_window::get_framebuffer_size() const
{
    // TODO: Get the proper framebuffer size.
    return glm::vec2(1920, 1080);
}

void gfx_gles2_rpi_window::set_mouse_cursor_mode(const mouse_cursor_mode)
{
}

mouse_cursor_mode gfx_gles2_rpi_window::get_mouse_cursor_mode() const
{
    return mouse_cursor_mode::normal;
}

void gfx_gles2_rpi_window::__reset_scissor() const
{
    glm::vec2 framebuffer_size = get_framebuffer_size();
    common::types::rectangle<float> rect(0.0f, 0.0f, framebuffer_size.x, framebuffer_size.y);
    device_.set_scissor(rect);
}

bool gfx_gles2_rpi_window::__on_frame_start(float /*dt*/)
{
    make_current();
    return true;
}

bool gfx_gles2_rpi_window::__on_frame_end(float /*dt*/)
{
    __reset_scissor();

    glFinish();

    eglSwapBuffers(display_, surface_);

    return true;
}

void gfx_gles2_rpi_window::__create_window()
{
    GLuint flags = 0;

    EGLint attrib_list[] = {EGL_RED_SIZE,
                            5,
                            EGL_GREEN_SIZE,
                            6,
                            EGL_BLUE_SIZE,
                            5,
                            EGL_ALPHA_SIZE,
                            8, //(flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
                            EGL_DEPTH_SIZE,
                            (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
                            EGL_STENCIL_SIZE,
                            (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
                            EGL_SAMPLE_BUFFERS,
                            (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
                            EGL_NONE};

    __create_native_window();
    __create_egl_context(attrib_list);
}

void gfx_gles2_rpi_window::__create_native_window()
{
    std::uint32_t display_width;
    std::uint32_t display_height;

    // create an EGL window surface, passing context width/height
    if (graphics_get_display_size(0 /* LCD */, &display_width, &display_height) < 0)
        throw std::runtime_error("Could not get display size.");

    VC_RECT_T dst_rect;
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.width = display_width;
    dst_rect.height = display_height;

    VC_RECT_T src_rect;
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.width = display_width << 16;
    src_rect.height = display_height << 16;

    DISPMANX_DISPLAY_HANDLE_T dispman_display = vc_dispmanx_display_open(0); /* LCD */
    DISPMANX_UPDATE_HANDLE_T dispman_update = vc_dispmanx_update_start(0);

    VC_DISPMANX_ALPHA_T alpha = { DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS, 255, 0 };

    DISPMANX_ELEMENT_HANDLE_T dispman_element =
        vc_dispmanx_element_add(dispman_update, dispman_display, 0,     /* layer */
                                &dst_rect, 0,                           /* src */
                                &src_rect, DISPMANX_PROTECTION_NONE, &alpha, /* alpha */
                                0,                                      /* clamp */
                                (DISPMANX_TRANSFORM_T)0                 /* transform */
                                );

    window_.element = dispman_element;
    window_.width = display_width;
    window_.height = display_height;
    vc_dispmanx_update_submit_sync(dispman_update);
}

void gfx_gles2_rpi_window::__create_egl_context(EGLint attrib_list[])
{
    EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

    // Get Display
    display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display_ == EGL_NO_DISPLAY)
        throw std::runtime_error("Failed to create display.");

    // Initialize EGL
    EGLint major_version;
    EGLint minor_version;
    if (!eglInitialize(display_, &major_version, &minor_version))
        throw std::runtime_error("Failed to initialize GLES 2.");

    // Get configs
    EGLint num_configs;
    if (!eglGetConfigs(display_, nullptr, 0, &num_configs))
        throw std::runtime_error("Failed to get configs.");

    // Choose config
    EGLConfig config;
    if (!eglChooseConfig(display_, attrib_list, &config, 1, &num_configs))
        throw std::runtime_error("Failed to choose config.");

    // Create a surface
    surface_ = eglCreateWindowSurface(display_, config, (EGLNativeWindowType)&window_, nullptr);
    if (surface_ == EGL_NO_SURFACE)
        throw std::runtime_error("Failed to create surface.");

    // Create a GL context
    context_ = eglCreateContext(display_, config, EGL_NO_CONTEXT, context_attribs);
    if (context_ == EGL_NO_CONTEXT)
        throw std::runtime_error("Failed to create context.");

    // Make the context current
    if (!eglMakeCurrent(display_, surface_, surface_, context_))
        throw std::runtime_error("Failed to make current.");
}

} // namespace gles2
} // namespace gfx
} // namespace aeon
