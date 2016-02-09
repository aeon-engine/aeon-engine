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

#include <GL/glew.h>
#include <gfx/gfx_shader.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gl
{

class shader : public gfx::shader
{
    friend class shader_manager;

public:
    shader();
    ~shader() override;

private:
    GLuint handle_;
};

using shader_gl_ptr = std::shared_ptr<shader>;

} // namespace gl
} // namespace gfx
} // namespace aeon
