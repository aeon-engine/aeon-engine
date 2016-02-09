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

#include <gfx/gfx_texture_manager.h>
#include <resources/wrappers/image_resource_wrapper.h>

namespace aeon
{
namespace gfx
{

texture_ptr texture_manager::load_texture(resources::image_ptr image)
{
    const std::string &path = image->get_resource_wrapper()->get_path();
    texture_ptr tex = cache_.get_cached_object(path);

    if (tex)
        return tex;

    tex = __load_texture(image);

    if (tex)
        cache_.add_cached_object(path, tex);

    return tex;
}

} // namespace gfx
} // namespace aeon
