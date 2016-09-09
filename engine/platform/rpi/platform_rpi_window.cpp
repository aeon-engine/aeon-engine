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

#include <platform/rpi/platform_rpi_window.h>
#include <platform/rpi/platform_rpi_interface.h>
#include <bcm_host.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <gfx/gl_common/check_gl_error.h>

// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1
// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2
// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8

namespace aeon
{
namespace platform
{
namespace rpi
{

platform_window::platform_window(platform_interface *interface, int width, int height, const std::string &title)
    : platform::platform_window(width, height, title)
    , logger_(common::logger::get_singleton(), "Platform::Raspberry")
    , interface_(interface)
{
    AEON_LOG_DEBUG(logger_) << "Creating OpenGL ES 2.0 context." << std::endl;
    __create_window();
}

platform_window::~platform_window()
{
}

void platform_window::make_current()
{
    if (!eglMakeCurrent(display_, surface_, surface_, context_))
        throw std::runtime_error("Failed to make current.");
}

glm::vec2 platform_window::get_framebuffer_size()
{
    std::uint32_t display_width;
    std::uint32_t display_height;

    if (graphics_get_display_size(0, &display_width, &display_height) < 0)
        throw std::runtime_error("Could not get display size");

    // TODO
    return glm::vec2(display_width, display_height);
}

bool platform_window::__on_frame_start(float /*dt*/)
{
    make_current();

    return true;
}

bool platform_window::__on_frame_end(float /*dt*/)
{
    glFinish();
    AEON_CHECK_GL_ERROR();

    eglSwapBuffers(display_, surface_);
    return true;
}

void platform_window::__create_window()
{
    GLuint flags = 0;

    EGLint attrib_list[] =
    {
        EGL_RED_SIZE, 5,
        EGL_GREEN_SIZE, 6,
        EGL_BLUE_SIZE, 5,
        EGL_ALPHA_SIZE, 8, //(flags & ES_WINDOW_ALPHA) ? 8 : EGL_DONT_CARE,
        EGL_DEPTH_SIZE, (flags & ES_WINDOW_DEPTH) ? 8 : EGL_DONT_CARE,
        EGL_STENCIL_SIZE, (flags & ES_WINDOW_STENCIL) ? 8 : EGL_DONT_CARE,
        EGL_SAMPLE_BUFFERS, (flags & ES_WINDOW_MULTISAMPLE) ? 1 : 0,
        EGL_NONE
    };

    __create_native_window();
    __create_egl_context(attrib_list);
}

void platform_window::__create_native_window()
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

    DISPMANX_ELEMENT_HANDLE_T dispman_element = vc_dispmanx_element_add
    (
        dispman_update,
        dispman_display,
        0,                            /* layer */
        &dst_rect,
        0,                            /* src */
        &src_rect,
        DISPMANX_PROTECTION_NONE,
        0,                            /* alpha */
        0,                            /* clamp */
        (DISPMANX_TRANSFORM_T) 0    /* transform */
    );

    window_.element = dispman_element;
    window_.width = display_width;
    window_.height = display_height;
    vc_dispmanx_update_submit_sync(dispman_update);
}

void platform_window::__create_egl_context(EGLint attrib_list[])
{
    EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

    // Get Display
    display_ = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display_ == EGL_NO_DISPLAY )
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
    surface_ = eglCreateWindowSurface(display_, config, (EGLNativeWindowType) &window_, nullptr);
    if (surface_ == EGL_NO_SURFACE )
        throw std::runtime_error("Failed to create surface.");

    // Create a GL context
    context_ = eglCreateContext(display_, config, EGL_NO_CONTEXT, context_attribs);
    if (context_ == EGL_NO_CONTEXT )
        throw std::runtime_error("Failed to create context.");

    // Make the context current
    if (!eglMakeCurrent(display_, surface_, surface_, context_))
        throw std::runtime_error("Failed to make current.");
}

} // namespace rpi
} // namespace platform
} // namespace aeon
