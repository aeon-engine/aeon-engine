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

#include <aeon/gfx/gfx_texture.h>
#include <aeon/common/logger.h>
#include <GLES2/gl2.h>

namespace aeon
{
namespace gfx
{
namespace gles2
{

class gfx_gles2_texture : public gfx::texture
{
    friend class gfx_gles2_texture_manager;

public:
    explicit gfx_gles2_texture();
    ~gfx_gles2_texture() override;

    void bind() const;
    auto get_size() const -> glm::vec2 override;
    auto get_pixel_format() const -> data::image::pixel_format override;

    void set_texture_bind_point(const int bind_point) const;

private:
    aeon::logger::logger logger_;
    GLuint handle_;
    glm::vec2 size_;
    data::image::pixel_format pixel_format_;
};

} // namespace gles2
} // namespace gfx
} // namespace aeon
