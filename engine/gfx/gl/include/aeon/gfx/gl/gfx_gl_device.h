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

#pragma once

#include <aeon/gfx/gfx_device.h>
#include <aeon/gfx/gfx_render_target.h>
#include <aeon/input/input_handler.h>
#include <aeon/common/exception.h>
#include <aeon/common/logger.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

DEFINE_EXCEPTION_OBJECT(gl_initialized_exception, aeon::common::exception, "OpenGL Device already initialized.");
DEFINE_EXCEPTION_OBJECT(gl_device_exception, aeon::common::exception, "OpenGL Device Exception");

class gfx_gl_device : public gfx::device
{
public:
    using render_targets = std::vector<render_target_ptr>;

    explicit gfx_gl_device(platform::platform_interface &platform, input::input_handler &input_handler);
    virtual ~gfx_gl_device();

    void __initialize_impl() override;

    void set_clear_color(const common::types::color &c) override;
    void set_viewport(render_target &rt, viewport &vp) override;

    void clear_buffer(int buffer_flag) override;

    mesh_ptr create_mesh(material_ptr material) override;

    gfx_monitors get_monitors() override;

    gfx_window_ptr create_window(const gfx_window_settings &settings, gfx_monitor_ptr monitor = nullptr) override;

    void run() override;
    void stop() override;

    input::input_handler &get_input_handler();

    void set_scissor(const common::types::rectangle<float> &scissor) const;

private:
    void __initialize_glfw() const;
    void __create_managers();
    void __setup_opengl() const;
    void __initialize_glew() const;
    void __report_and_squash_glew_errors() const;

    aeon::logger::logger logger_;
    input::input_handler &input_handler_;
    render_targets render_targets_;
    bool running_;
    double previous_time_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
