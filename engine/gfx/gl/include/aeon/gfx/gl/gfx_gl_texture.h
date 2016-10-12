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

#include <aeon/gfx/gfx_texture.h>
#include <aeon/common/logger.h>
#include <GL/glew.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class gfx_gl_texture : public gfx::texture
{
    friend class gfx_gl_texture_manager;

public:
    explicit gfx_gl_texture();
    ~gfx_gl_texture() override;

    void bind() const;
    glm::vec2 get_size() const override;

private:
    aeon::logger::logger logger_;
    GLuint handle_;
    glm::vec2 size_;
};

using gfx_gl_texture_ptr = std::shared_ptr<gl::gfx_gl_texture>;

} // namespace gl
} // namespace gfx
} // namespace aeon
