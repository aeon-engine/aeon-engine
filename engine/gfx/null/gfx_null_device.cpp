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

#include <gfx/null/gfx_null_texture_manager.h>
#include <gfx/null/gfx_null_shader_manager.h>
#include <gfx/null/gfx_null_material_manager.h>
#include <gfx/null/gfx_null_buffer_manager.h>
#include <gfx/null/gfx_null_device.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace null
{

gfx_null_device::gfx_null_device()
    : logger_(common::logger::get_singleton(), "Gfx::Null::Device")
{
}

void gfx_null_device::__initialize_impl()
{
    AEON_LOG_MESSAGE(logger_) << "Initializing device." << std::endl;

    if (initialized_)
    {
        AEON_LOG_FATAL(logger_) << "Initialize called while already initialized." << std::endl;
        throw null_initialized_exception();
    }

    __create_managers();

    initialized_ = true;
}

void gfx_null_device::set_clear_color(const common::types::color &)
{
}

void gfx_null_device::set_viewport(scene::viewport *)
{
}

void gfx_null_device::clear_buffer(int)
{
}

mesh_ptr gfx_null_device::create_mesh(material_ptr material)
{
    // TODO: Implement
    return nullptr;
}

void gfx_null_device::__create_managers()
{
    texture_manager_ = std::make_unique<null::gfx_null_texture_manager>();
    shader_manager_ = std::make_unique<null::gfx_null_shader_manager>();
    material_manager_ = std::make_unique<null::gfx_null_material_manager>(*this);
    buffer_manager_ = std::make_unique<null::gfx_null_buffer_manager>();
    atlas_manager_ = std::make_unique<gfx_atlas_manager>();
}

} // namespace null
} // namespace gfx
} // namespace aeon
