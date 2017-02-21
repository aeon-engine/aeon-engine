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

#include <aeon/gfx/gfx_texture_manager.h>
#include <aeon/gfx/gfx_material_manager.h>
#include <aeon/gfx/gfx_shader_manager.h>
#include <aeon/gfx/gfx_atlas_manager.h>
#include <aeon/gfx/gfx_buffer_manager.h>
#include <aeon/gfx/gfx_mesh.h>
#include <aeon/gfx/gfx_window.h>
#include <aeon/gfx/gfx_monitor.h>
#include <aeon/gfx/gfx_viewport.h>
#include <aeon/platform/platform_interface.h>
#include <aeon/common/types/color.h>
#include <memory>

namespace aeon
{
namespace gfx
{

struct buffer_clear_flag
{
    static const int color_buffer = 0x01;
    static const int depth_buffer = 0x02;
};

class render_target;

class device
{
public:
    explicit device(platform::platform_interface &platform);
    virtual ~device() = default;

    void initialize();

    virtual void set_clear_color(const common::types::color &c) = 0;
    virtual void set_viewport(render_target &rt, viewport &vp) = 0;
    virtual void clear_buffer(int buffer_flag) = 0;

    virtual std::unique_ptr<mesh> create_mesh(std::shared_ptr<material> material) = 0;

    /*!
     * Get a list of all monitors connected to this system.
     */
    virtual std::vector<std::shared_ptr<gfx_monitor>> get_monitors() = 0;

    /*!
     * Create a window. A window can be created on a specific monitor. When no monitor is
     * given, the window appears on the main monitor.
     */
    virtual std::shared_ptr<gfx_window> create_window(const gfx_window_settings &settings,
                                                      std::shared_ptr<gfx_monitor> monitor = nullptr) = 0;

    /*!
     * Enter the engine's main loop. You must first call initialize before calling run.
     * This function will not return until stop() is called.
     */
    virtual void run() = 0;

    /*!
     * Stop the mainloop. Has no effect if run hasn't been called.
     */
    virtual void stop() = 0;

    texture_manager &get_texture_manager()
    {
        return *texture_manager_;
    }

    shader_manager &get_shader_manager()
    {
        return *shader_manager_;
    }

    material_manager &get_material_manager()
    {
        return *material_manager_;
    }

    buffer_manager &get_buffer_manager()
    {
        return *buffer_manager_;
    }

    gfx_atlas_manager &get_atlas_manager()
    {
        return *atlas_manager_;
    }

    platform::platform_interface &get_platform_interface()
    {
        return platform_interface_;
    }

protected:
    virtual void __initialize_impl() = 0;

    platform::platform_interface &platform_interface_;
    bool initialized_;
    std::unique_ptr<texture_manager> texture_manager_;
    std::unique_ptr<shader_manager> shader_manager_;
    std::unique_ptr<material_manager> material_manager_;
    std::unique_ptr<buffer_manager> buffer_manager_;
    std::unique_ptr<gfx_atlas_manager> atlas_manager_;
};

} // namespace gfx
} // namespace aeon
