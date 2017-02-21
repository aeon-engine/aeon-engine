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

#include <GLES2/gl2.h>
#include <gfx/gfx_material.h>
#include <gfx/gles2/gfx_gles2_shader.h>
#include <gfx/gles2/gfx_gles2_texture.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_material : public gfx::material
{
    friend class gfx_gles2_material_manager;

    void bind() override;

public:
    gfx_gles2_material() = default;
    ~gfx_gles2_material() = default;

    gfx::shader *get_shader() const override;
    gfx::texture *get_texture() const override;

protected:
    gfx_gles2_shader_ptr shader_;
    gfx_gles2_texture_ptr texture_;
};

using gfx_gles2_material_ptr = std::shared_ptr<gfx_gles2_material>;

} // namespace gles2
} // namespace gfx
} // namespace aeon
