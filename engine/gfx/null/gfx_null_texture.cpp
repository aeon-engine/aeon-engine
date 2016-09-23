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

#include <gfx/null/gfx_null_texture.h>

namespace aeon
{
namespace gfx
{
namespace null
{

gfx_null_texture::gfx_null_texture(const resources::image &image)
    : gfx::texture(image)
    , logger_(common::logger::get_singleton(), "Gfx::Null::Texture")
{
}

gfx_null_texture::~gfx_null_texture()
{
    AEON_LOG_TRACE(logger_) << "Deleting Texture." << std::endl;
}

void gfx_null_texture::bind() const
{
}

} // namespace null
} // namespace gfx
} // namespace aeon
