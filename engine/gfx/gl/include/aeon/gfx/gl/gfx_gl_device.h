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

#pragma once

#include <aeon/gfx/gfx_device.h>
#include <aeon/gfx/gfx_render_target.h>
#include <aeon/common/exception.h>
#include <aeon/common/logger.h>

namespace aeon::gfx::gl
{

DEFINE_EXCEPTION_OBJECT(gl_initialized_exception, aeon::common::exception, "OpenGL Device already initialized.");
DEFINE_EXCEPTION_OBJECT(gl_device_exception, aeon::common::exception, "OpenGL Device Exception");

class gfx_gl_device : public gfx::device
{
public:
    explicit gfx_gl_device(io::io_interface &io);
    virtual ~gfx_gl_device();

    void __initialize_impl() override;

    void set_clear_color(const common::types::color &c) override;
    void set_viewport(render_target &rt, viewport &vp) override;

    void clear_buffer(int buffer_flag) override;

    auto create_mesh(std::shared_ptr<material> material) -> std::unique_ptr<mesh> override;

    void add_render_target(render_target *target) override;
    void remove_render_target(render_target *target) override;

    auto render(float dt) -> bool override;

    void set_scissor(const common::types::rectangle<float> &scissor) const override;

private:
    void __create_managers();
    void __setup_opengl() const;
    void __initialize_glad() const;
    void __report_and_squash_glad_errors() const;

    logger::logger logger_;
    std::vector<render_target *> render_targets_;
};

} // namespace aeon::gfx::gl
