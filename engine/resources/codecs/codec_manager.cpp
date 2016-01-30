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

#include <resources/codecs/codec_manager.h>
#include <resources/codecs/image_png_codec.h>

namespace aeon
{
namespace resources
{

codec_manager::codec_manager()
{
    __register_codecs();
}

codec_ptr codec_manager::get_codec(resource_encoding encoding)
{
    auto result = codecs_.find(encoding);

    if (result == codecs_.end())
        throw codec_manager_unknown_codec_exception();

    return result->second;
}

image_codec_ptr codec_manager::get_image_codec(resource_encoding encoding)
{
    if (get_resource_type_by_encoding(encoding) != resource_type::image)
        throw codec_manager_codec_mismatch_exception();

    return std::dynamic_pointer_cast<image_codec>(get_codec(encoding));
}

material_codec_ptr codec_manager::get_material_codec()
{
    return std::dynamic_pointer_cast<material_codec>(get_codec(resource_encoding::material));
}

resource_type codec_manager::get_resource_type_by_encoding(resource_encoding encoding) const
{
    switch (encoding)
    {
        case resource_encoding::image_png:
            return resource_type::image;
        case resource_encoding::material:
            return resource_type::material;
        case resource_encoding::unknown:
        default:
            throw codec_manager_unknown_codec_exception();
    }
}

void codec_manager::__register_codecs()
{
    codecs_[resource_encoding::image_png] = std::make_shared<image_codec_png>();
    codecs_[resource_encoding::material] = std::make_shared<material_codec>();
}

} // namespace resources
} // namespace aeon
