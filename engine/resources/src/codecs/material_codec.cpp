/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/platform.h>
#include <aeon/streams.h>
#include <aeon/utility.h>
#include <aeon/resources/resource_manager.h>
#include <aeon/resources/codecs/material_codec.h>
#include <aeon/resources/wrappers/material_resource_wrapper.h>
#include <build_config.h>

namespace aeon
{
namespace resources
{

material_codec::material_codec()
    : logger_(common::logger::get_singleton(), "Resources::MaterialCodec")
{
}

auto material_codec::get_codec_type() const -> resource_encoding
{
    return resource_encoding::material;
}

auto material_codec::decode(const std::shared_ptr<material_resource_wrapper> &wrapper) const
    -> std::shared_ptr<material>
{
    AEON_LOG_DEBUG(logger_) << "Decoding material resource." << std::endl;

    auto input = std::vector<std::uint8_t>();
    wrapper->read_raw(input);

    auto stream = streams::memory_stream(std::move(input));
    auto material_file = utility::configfile();
    material_file.load(stream);

    if (!material_file.has_entry("texture"))
    {
        AEON_LOG_ERROR(logger_) << "Could not decode material. Could not find texture entry." << std::endl;
        throw material_codec_decode_exception();
    }

#ifdef AEON_GFX_GL
    auto shader_path = material_file.get<std::string>("shader_gl3", "");
#else // AEON_GFX_GL
#ifdef AEON_GFX_GLES2
    auto shader_path = material_file.get<std::string>("shader_gles2", "");
#else // AEON_GFX_GLES2
#ifdef AEON_GFX_NULL
    // TODO: Handle this better.
    auto shader_path = material_file.get<std::string>("shader_gl3", "");
#else  // AEON_GFX_NULL
    auto shader_path = material_file.get<std::string>("shader", "");
#endif // AEON_GFX_NULL
#endif // AEON_GFX_GLES2
#endif // AEON_GFX_GL

    auto textures = data::material::texture_paths();
    textures["texture"] = material_file.get<std::string>("texture", "");
    auto material_data = data::material(shader_path, textures);

    return std::make_shared<resources::material>(wrapper, std::move(material_data));
}

} // namespace resources
} // namespace aeon
