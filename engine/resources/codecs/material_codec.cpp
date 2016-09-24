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

#include <aeon/platform.h>
#include <aeon/streams.h>
#include <aeon/utility.h>
#include <resources/resource_manager.h>
#include <resources/codecs/material_codec.h>
#include <resources/wrappers/material_resource_wrapper.h>
#include <common/buffer.h>
#include <build_config.h>

namespace aeon
{
namespace resources
{

material_codec::material_codec()
    : logger_(common::logger::get_singleton(), "Resources::MaterialCodec")
{
}

resource_encoding material_codec::get_codec_type() const
{
    return resource_encoding::material;
}

material_ptr material_codec::decode(material_resource_wrapper_ptr wrapper) const
{
    AEON_LOG_DEBUG(logger_) << "Decoding material resource." << std::endl;

    common::buffer_u8 input;
    wrapper->read_raw(input);

    streams::memory_stream stream(std::move(input));
    utility::configfile material_file;
    material_file.load(stream);

    if (!material_file.has_entry("texture"))
    {
        AEON_LOG_ERROR(logger_) << "Could not decode material. Could not find texture entry." << std::endl;
        throw material_codec_decode_exception();
    }

#ifdef AEON_GFX_GL
    std::string shader_path = material_file.get<std::string>("shader_gl3", "");
#else // AEON_GFX_GL
#ifdef AEON_GFX_GLES2
    std::string shader_path = material_file.get<std::string>("shader_gles2", "");
#else // AEON_GFX_GLES2
#ifdef AEON_GFX_NULL
    // TODO: Handle this better.
    std::string shader_path = material_file.get<std::string>("shader_gl3", "");
#else  // AEON_GFX_NULL
    std::string shader_path = material_file.get<std::string>("shader", "");
#endif // AEON_GFX_NULL
#endif // AEON_GFX_GLES2
#endif // AEON_GFX_GL

    data::material::texture_paths textures;
    textures["texture"] = material_file.get<std::string>("texture", "");
    data::material material_data(shader_path, textures);

    return std::make_shared<resources::material>(wrapper, material_data);
}

} // namespace resources
} // namespace aeon
