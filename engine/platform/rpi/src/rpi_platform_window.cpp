/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/platform/rpi/rpi_platform_window.h>
#include <aeon/platform/rpi/rpi_platform_manager.h>

#include <GLES2/gl2.h>
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
namespace platform
{
namespace rpi
{

rpi_window::rpi_window(rpi_platform_manager &platform_manager, const window_settings &settings)
    : window(settings)
    , logger_(common::logger::get_singleton(), "Platform::RPI::Window")
    , platform_manager_(platform_manager)
    , cursor_mode_(mouse_cursor_mode::normal)
{
    AEON_LOG_DEBUG(logger_) << "Creating OpenGL ES 2.0 context." << std::endl;

    __create_window();
}

rpi_window::~rpi_window()
{
}

void rpi_window::make_current()
{
    if (!eglMakeCurrent(display_, surface_, surface_, context_))
        throw std::runtime_error("Failed to make current.");
}

auto rpi_window::get_framebuffer_size() const -> glm::vec2
{
    // TODO: This can be done better.
    if (framebuffer_size_.x == 0.0f && framebuffer_size_.y == 0.0f)
    {
        std::uint32_t display_width;
        std::uint32_t display_height;

        // create an EGL window surface, passing context width/height
        if (graphics_get_display_size(0 /* LCD */, &display_width, &display_height) < 0)
            throw std::runtime_error("Could not get display size.");

        framebuffer_size_.x = static_cast<float>(display_width);
        framebuffer_size_.y = static_cast<float>(display_height);
    }

    return framebuffer_size_;
}

void rpi_window::set_mouse_cursor_mode(const mouse_cursor_mode mode)
{
    cursor_mode_ = mode;
}

auto rpi_window::get_mouse_cursor_mode() const -> mouse_cursor_mode
{
    return cursor_mode_;
}

void rpi_window::__reset_scissor() const
{
    auto framebuffer_size = get_framebuffer_size();
    auto rect = common::types::rectangle<float>(0.0f, 0.0f, framebuffer_size.x, framebuffer_size.y);
    platform_manager_.get_device().set_scissor(rect);
}

auto rpi_window::__on_frame_start(float /*dt*/) -> bool
{
    make_current();
    return true;
}

auto rpi_window::__on_frame_end(float /*dt*/) -> bool
{
    __reset_scissor();

    glFinish();
    eglSwapBuffers(display_, surface_);

    return true;
}

void rpi_window::__create_window()
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

void rpi_window::__create_native_window()
{
    auto framebuffer_size = get_framebuffer_size();
    uint32_t display_width = static_cast<int>(framebuffer_size.x);
    uint32_t display_height = static_cast<int>(framebuffer_size.y);

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

    VC_DISPMANX_ALPHA_T alpha = {DISPMANX_FLAGS_ALPHA_FIXED_ALL_PIXELS, 255, 0};

    DISPMANX_ELEMENT_HANDLE_T dispman_element =
        vc_dispmanx_element_add(dispman_update, dispman_display, 0,          /* layer */
                                &dst_rect, 0,                                /* src */
                                &src_rect, DISPMANX_PROTECTION_NONE, &alpha, /* alpha */
                                0,                                           /* clamp */
                                (DISPMANX_TRANSFORM_T)0                      /* transform */
        );

    window_.element = dispman_element;
    window_.width = display_width;
    window_.height = display_height;
    vc_dispmanx_update_submit_sync(dispman_update);
}

void rpi_window::__create_egl_context(EGLint attrib_list[])
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

} // namespace rpi
} // namespace platform
} // namespace aeon
