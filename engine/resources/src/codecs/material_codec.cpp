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
#include <aeon/serialization/serialization.h>
#include <build_config.h>
#include <json11.hpp>

namespace aeon
{
namespace resources
{

static auto convert_material_file_data(const serialization::material &material_file_data) -> data::material
{
    data::material material;

#ifdef AEON_GFX_GL
    auto shader_path = material_file_data.shaders.at("gl3");
#else // AEON_GFX_GL
#ifdef AEON_GFX_GLES2
    shader_path_ = material_file_data.shaders.at("gles2");
#else
    static_assert(false, "Invalid or unsupported gfx subsystem selected.");
#endif // AEON_GFX_GLES2
#endif // AEON_GFX_GL

    material.set_shader_path(shader_path);

    for (auto &sampler : material_file_data.samplers)
    {
        material.add_sampler(data::sampler(sampler->name, sampler->path));
    }

    return material;
}

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

    auto input = std::string();
    wrapper->read_raw(input);

    auto error_string = std::string();
    auto json = json11::Json::parse(input, error_string, json11::JsonParse::STANDARD);

    if (!error_string.empty())
    {
        AEON_LOG_ERROR(logger_) << "Parse error while decoding material. Message was: " << error_string << std::endl;
        throw material_codec_decode_exception();
    }

    serialization::material material_file_data(json);
    auto material_data = convert_material_file_data(material_file_data);

    return std::make_shared<resources::material>(wrapper, std::move(material_data));
}

} // namespace resources
} // namespace aeon
