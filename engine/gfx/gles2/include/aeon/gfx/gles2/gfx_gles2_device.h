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
namespace gles2
{

DEFINE_EXCEPTION_OBJECT(gles2_initialized_exception, aeon::common::exception,
                        "OpenGL ES 2.0 Device already initialized.");
DEFINE_EXCEPTION_OBJECT(gles2_device_exception, aeon::common::exception, "OpenGL ES 2.0 Device Exception");

class gfx_gles2_device : public gfx::device
{
public:
    using render_targets = std::vector<std::shared_ptr<render_target>>;

    explicit gfx_gles2_device(platform::platform_interface &platform, input::input_handler &input_handler);
    virtual ~gfx_gles2_device();

    void __initialize_impl() override;

    void set_clear_color(const common::types::color &c) override;
    void set_viewport(render_target &rt, viewport &vp) override;

    void clear_buffer(int buffer_flag) override;

    std::unique_ptr<mesh> create_mesh(std::shared_ptr<material> material) override;

    std::vector<std::shared_ptr<gfx_monitor>> get_monitors() override;

    std::shared_ptr<gfx_window> create_window(const gfx_window_settings &settings,
                                              std::shared_ptr<gfx_monitor> monitor = nullptr) override;

    void run() override;
    void stop() override;

    input::input_handler &get_input_handler();

    void set_scissor(const common::types::rectangle<float> &scissor) const;

private:
    void __create_managers();
    void __setup_opengl() const;

    aeon::logger::logger logger_;
    input::input_handler &input_handler_;
    render_targets render_targets_;
    bool running_;
    double previous_time_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
