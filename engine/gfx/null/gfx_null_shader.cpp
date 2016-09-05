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

#include <gfx/null/gfx_null_shader.h>
#include <glm/gtc/type_ptr.hpp>

namespace aeon
{
namespace gfx
{
namespace null
{

gfx_null_shader::gfx_null_shader()
    : logger_(common::logger::get_singleton(), "Gfx::Null::Shader")
{
}

gfx_null_shader::~gfx_null_shader()
{
    AEON_LOG_TRACE(logger_) << "Deleting Program." << std::endl;
}

void gfx_null_shader::bind() const
{
}

void gfx_null_shader::set_projection_matrix(const glm::mat4 &)
{
}

void gfx_null_shader::set_model_matrix(const glm::mat4 &)
{
}

void gfx_null_shader::set_view_matrix(const glm::mat4 &)
{
}

} // namespace null
} // namespace gfx
} // namespace aeon
