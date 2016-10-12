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
    
class renter_target;

class device
{
public:
    explicit device(platform::platform_interface &platform);
    virtual ~device() = default;

    void initialize();

    virtual void set_clear_color(const common::types::color &c) = 0;
    virtual void set_viewport(render_target &rt, viewport &vp) = 0;
    virtual void clear_buffer(int buffer_flag) = 0;

    virtual mesh_ptr create_mesh(material_ptr material) = 0;

    /*!
     * Get a list of all monitors connected to this system.
     */
    virtual gfx_monitors get_monitors() = 0;

    /*!
     * Create a window. A window can be created on a specific monitor. When no monitor is
     * given, the window appears on the main monitor.
     */
    virtual gfx_window_ptr create_window(const gfx_window_settings &settings, gfx_monitor_ptr monitor = nullptr) = 0;

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
