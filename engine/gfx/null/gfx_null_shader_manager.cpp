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

#include <gfx/null/gfx_null_shader_manager.h>
#include <gfx/null/gfx_null_shader.h>

namespace aeon
{
namespace gfx
{
namespace null
{

gfx_null_shader_manager::gfx_null_shader_manager()
    : logger_(common::logger::get_singleton(), "Gfx::Null::ShaderManager")
{
}

shader_ptr gfx_null_shader_manager::__load(resources::shader_ptr shader)
{
    AEON_LOG_TRACE(logger_) << "Loading Program." << std::endl;
    gfx_null_shader_ptr s = std::make_shared<gfx_null_shader>();
    return s;
}

} // namespace null
} // namespace gfx
} // namespace aeon
