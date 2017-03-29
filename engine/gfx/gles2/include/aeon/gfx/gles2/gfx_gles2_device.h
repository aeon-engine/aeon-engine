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
namespace gles2
{

DEFINE_EXCEPTION_OBJECT(gles2_initialized_exception, aeon::common::exception,
                        "OpenGL ES 2.0 Device already initialized.");
DEFINE_EXCEPTION_OBJECT(gles2_device_exception, aeon::common::exception, "OpenGL ES 2.0 Device Exception");

class gfx_gles2_device : public gfx::device
{
public:
    using render_targets = std::vector<std::shared_ptr<render_target>>;

    explicit gfx_gles2_device(io::io_interface &io);
    virtual ~gfx_gles2_device();

    void __initialize_impl() override;

    void set_clear_color(const common::types::color &c) override;
    void set_viewport(render_target &rt, viewport &vp) override;

    void clear_buffer(int buffer_flag) override;

    auto create_mesh(std::shared_ptr<material> material) -> std::unique_ptr<mesh> override;

    void add_render_target(std::shared_ptr<render_target> target) override;

    auto render(float dt) -> bool override;

    void set_scissor(const common::types::rectangle<float> &scissor) const;

private:
    void __create_managers();
    void __setup_opengl() const;

    aeon::logger::logger logger_;
    render_targets render_targets_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
