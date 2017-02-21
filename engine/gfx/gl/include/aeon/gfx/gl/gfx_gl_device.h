/*
 * Copyright (c) 2012-2017 Robin Degen
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
    using render_targets = std::vector<std::shared_ptr<render_target>>;

    explicit gfx_gl_device(platform::platform_interface &platform, input::input_handler &input_handler);
    virtual ~gfx_gl_device();

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
