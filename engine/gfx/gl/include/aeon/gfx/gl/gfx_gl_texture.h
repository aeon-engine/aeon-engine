/*
 * Copyright (c) 2012-2018 Robin Degen
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
#include <glad/glad.h>

namespace aeon::gfx::gl
{

class gfx_gl_texture : public gfx::texture
{
    friend class gfx_gl_texture_manager;

public:
    explicit gfx_gl_texture();
    ~gfx_gl_texture() override;

    void bind() const;
    auto get_size() const -> math::vector2<float> override;
    auto get_pixel_format() const -> imaging::pixel_encoding override;

    void set_texture_bind_point(const int bind_point) const;

private:
    aeon::logger::logger logger_;
    GLuint handle_;
    math::vector2<float> size_;
    imaging::pixel_encoding pixel_format_;
};

} // namespace aeon::gfx::gl
