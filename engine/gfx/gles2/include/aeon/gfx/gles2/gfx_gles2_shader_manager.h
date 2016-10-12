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

#include <gfx/gfx_resource_manager.h>
#include <GLES2/gl2.h>
#include <common/logger.h>
#include <common/exception.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

DEFINE_EXCEPTION_OBJECT(gfx_gles2_shader_exception, aeon::common::exception, "GLES2 shader exception.");
DEFINE_EXCEPTION_OBJECT(gfx_gles2_shader_compile_exception, gfx_gles2_shader_exception,
                        "GLES2 shader compilation exception.");

class gfx_gles2_shader_manager : public gfx::shader_manager
{
public:
    gfx_gles2_shader_manager();
    virtual ~gfx_gles2_shader_manager() = default;

private:
    shader_ptr __load(resources::shader_ptr shader) override;

    GLuint __load_gl_shader(const std::string &source, GLenum type);
    GLuint __link_gl_program(GLuint vertexshader, GLuint fragmentshader);

    aeon::logger::logger logger_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
