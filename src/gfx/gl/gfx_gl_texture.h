/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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
#include <gfx/gfx_texture.h>

namespace aeon
{
namespace gfx
{
namespace gl
{

class texture : public gfx::texture
{
friend class texture_manager;
public:
    explicit texture(resources::image_resource_wrapper_ptr image);
    ~texture() override;

private:
    GLuint handle_;
};

using texture_gl_ptr = std::shared_ptr<texture>;

} // namespace gl
} // namespace gfx
} // namespace aeon
