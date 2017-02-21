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

#include <aeon/resources/codecs/codec_manager.h>
#include <aeon/resources/codecs/image_png_codec.h>
#include <aeon/resources/codecs/image_dds_codec.h>
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

auto codec_manager::get_codec(const resource_encoding encoding) const -> codec &
{
    auto result = codecs_.find(encoding);

    if (result == codecs_.end())
        throw codec_manager_unknown_codec_exception();

    return *(result->second);
}

auto codec_manager::get_image_codec(const resource_encoding encoding) const -> image_codec &
{
    if (get_resource_type_by_encoding(encoding) != resource_type::image)
    {
        AEON_LOG_ERROR(logger_) << "Can not decode resource as image." << std::endl;
        throw codec_manager_codec_mismatch_exception();
    }

    return dynamic_cast<image_codec &>(get_codec(encoding));
}

auto codec_manager::get_material_codec() const -> material_codec &
{
    return dynamic_cast<material_codec &>(get_codec(resource_encoding::material));
}

auto codec_manager::get_shader_codec() const -> shader_codec &
{
    return dynamic_cast<shader_codec &>(get_codec(resource_encoding::shader));
}

auto codec_manager::get_atlas_codec() const -> atlas_codec &
{
    return dynamic_cast<atlas_codec &>(get_codec(resource_encoding::atlas));
}

auto codec_manager::get_mesh_codec(const resource_encoding encoding) const -> mesh_codec &
{
    if (get_resource_type_by_encoding(encoding) != resource_type::mesh)
    {
        AEON_LOG_ERROR(logger_) << "Can not decode resource as mesh." << std::endl;
        throw codec_manager_codec_mismatch_exception();
    }

    return dynamic_cast<mesh_codec &>(get_codec(encoding));
}

auto codec_manager::get_scene_codec() const -> scene_codec &
{
    return dynamic_cast<scene_codec &>(get_codec(resource_encoding::scene));
}

auto codec_manager::get_resource_type_by_encoding(const resource_encoding encoding) const -> resource_type
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
        case resource_encoding::image_dds:
            return resource_type::image;
        case resource_encoding::mesh_assimp:
            return resource_type::mesh;
        case resource_encoding::scene:
            return resource_type::scene;
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
    codecs_[resource_encoding::image_dds] = std::make_unique<image_codec_dds>();
    codecs_[resource_encoding::atlas] = std::make_unique<atlas_codec>();
    codecs_[resource_encoding::mesh_assimp] = std::make_unique<mesh_codec_assimp>();
    codecs_[resource_encoding::scene] = std::make_unique<scene_codec>();

    AEON_LOG_DEBUG(logger_) << "Registered " << codecs_.size() << " codecs." << std::endl;
}

} // namespace resources
} // namespace aeon
