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

#include <aeon/resources/codecs/codec_manager.h>
#include <aeon/resources/codecs/image_png_codec.h>
#include <aeon/resources/codecs/mesh_assimp_codec.h>

namespace aeon
{
namespace resources
{

codec_manager::codec_manager()
    : logger_(common::logger::get_singleton(), "Resources::CodecManager")
{
    __register_codecs();
}

codec &codec_manager::get_codec(resource_encoding encoding)
{
    auto result = codecs_.find(encoding);

    if (result == codecs_.end())
        throw codec_manager_unknown_codec_exception();

    return *(result->second);
}

image_codec &codec_manager::get_image_codec(resource_encoding encoding)
{
    if (get_resource_type_by_encoding(encoding) != resource_type::image)
    {
        AEON_LOG_ERROR(logger_) << "Can not decode resource as image." << std::endl;
        throw codec_manager_codec_mismatch_exception();
    }

    return dynamic_cast<image_codec &>(get_codec(encoding));
}

material_codec &codec_manager::get_material_codec()
{
    return dynamic_cast<material_codec &>(get_codec(resource_encoding::material));
}

shader_codec &codec_manager::get_shader_codec()
{
    return dynamic_cast<shader_codec &>(get_codec(resource_encoding::shader));
}

atlas_codec &codec_manager::get_atlas_codec()
{
    return dynamic_cast<atlas_codec &>(get_codec(resource_encoding::atlas));
}

mesh_codec &codec_manager::get_mesh_codec(resource_encoding encoding)
{
    if (get_resource_type_by_encoding(encoding) != resource_type::mesh)
    {
        AEON_LOG_ERROR(logger_) << "Can not decode resource as mesh." << std::endl;
        throw codec_manager_codec_mismatch_exception();
    }

    return dynamic_cast<mesh_codec &>(get_codec(encoding));
}

resource_type codec_manager::get_resource_type_by_encoding(resource_encoding encoding) const
{
    switch (encoding)
    {
        case resource_encoding::material:
            return resource_type::material;
        case resource_encoding::shader:
            return resource_type::shader;
        case resource_encoding::atlas:
            return resource_type::atlas;
        case resource_encoding::image_png:
            return resource_type::image;
        case resource_encoding::mesh_assimp:
            return resource_type::mesh;
        case resource_encoding::unknown:
        default:
        {
            AEON_LOG_ERROR(logger_) << "Unknown encoding." << std::endl;
            throw codec_manager_unknown_codec_exception();
        }
    }
}

void codec_manager::__register_codecs()
{
    codecs_[resource_encoding::material] = std::make_unique<material_codec>();
    codecs_[resource_encoding::shader] = std::make_unique<shader_codec>();
    codecs_[resource_encoding::image_png] = std::make_unique<image_codec_png>();
    codecs_[resource_encoding::atlas] = std::make_unique<atlas_codec>();
    codecs_[resource_encoding::mesh_assimp] = std::make_unique<mesh_codec_assimp>();

    AEON_LOG_DEBUG(logger_) << "Registered " << codecs_.size() << " codecs." << std::endl;
}

} // namespace resources
} // namespace aeon
