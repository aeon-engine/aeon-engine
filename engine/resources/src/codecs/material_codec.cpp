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
#include <json11.hpp>

namespace aeon
{
namespace resources
{

class material_file_deserializer
{
public:
    explicit material_file_deserializer(const logger::logger &logger, json11::Json &json, data::material &material_data)
        : logger_(logger)
        , json_(json)
        , material_data_(material_data)
    {
        __parse_shaders();
        __parse_samplers();
    }

    ~material_file_deserializer() = default;

private:
    void __parse_shaders() const
    {
        auto &shaders = json_["shaders"];

        if (!shaders.is_object())
        {
            AEON_LOG_ERROR(logger_) << "'Shaders' entry missing from material file." << std::endl;
            throw material_codec_decode_exception();
        }

#ifdef AEON_GFX_GL
        auto shader_path = shaders["gl3"].string_value();
#else // AEON_GFX_GL
#ifdef AEON_GFX_GLES2
        shader_path_ = shaders["gles2"].string_value();
#else
        static_assert(false, "Invalid or unsupported gfx subsystem selected.");
#endif // AEON_GFX_GLES2
#endif // AEON_GFX_GL

        if (shader_path.empty())
        {
            AEON_LOG_ERROR(logger_) << "Shader path was empty." << std::endl;
            throw material_codec_decode_exception();
        }

        material_data_.set_shader_path(shader_path);
    }

    void __parse_samplers() const
    {
        auto &samplers = json_["samplers"];

        if (!samplers.is_array())
        {
            AEON_LOG_ERROR(logger_) << "'Samplers' entry missing or incorrect in material file." << std::endl;
            throw material_codec_decode_exception();
        }

        auto &sampler_array = samplers.array_items();

        for (auto &sampler : sampler_array)
        {
            auto &name_object = sampler["name"];

            if (!name_object.is_string())
            {
                AEON_LOG_ERROR(logger_) << "Sampler name entry missing or incorrect in material file." << std::endl;
                throw material_codec_decode_exception();
            }

            auto &path_object = sampler["path"];

            if (!path_object.is_string())
            {
                AEON_LOG_ERROR(logger_) << "Sampler path entry missing or incorrect in material file." << std::endl;
                throw material_codec_decode_exception();
            }

            material_data_.add_sampler(data::sampler(name_object.string_value(), path_object.string_value()));
        }
    }

    const logger::logger &logger_;
    json11::Json &json_;
    data::material &material_data_;
};

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

    auto material_data = data::material();
    auto material_file_data = material_file_deserializer(logger_, json, material_data);

    return std::make_shared<resources::material>(wrapper, std::move(material_data));
}

} // namespace resources
} // namespace aeon
