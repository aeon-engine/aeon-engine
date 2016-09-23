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

#include <gfx/null/gfx_null_texture_manager.h>
#include <gfx/null/gfx_null_texture.h>
#include <resources/image.h>

namespace aeon
{
namespace gfx
{
namespace null
{

gfx_null_texture_manager::gfx_null_texture_manager()
    : logger_(common::logger::get_singleton(), "Gfx::Null::TextureManager")
{
}

texture_ptr gfx_null_texture_manager::create(const resources::image &image)
{
    AEON_LOG_TRACE(logger_) << "Created Texture." << std::endl;
    gfx_null_texture_ptr t = std::make_shared<gfx_null_texture>(image);
    t->size_ = image.get_data().get_size();
    return t;
}

} // namespace null
} // namespace gfx
} // namespace aeon
