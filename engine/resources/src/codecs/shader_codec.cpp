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
#include <aeon/resources/resource_manager.h>
#include <aeon/resources/codecs/shader_codec.h>
#include <aeon/resources/wrappers/shader_resource_wrapper.h>

namespace aeon
{
namespace resources
{

shader_codec::shader_codec()
    : logger_(common::logger::get_singleton(), "Resources::ShaderCodec")
{
}

resource_encoding shader_codec::get_codec_type() const
{
    return resource_encoding::material;
}

std::shared_ptr<shader> shader_codec::decode(resource_manager & /*parent*/,
                                             const std::shared_ptr<shader_resource_wrapper> &wrapper)
{
    // TODO: Add error handling for missing segments in the resource file

    AEON_LOG_DEBUG(logger_) << "Decoding shader resource." << std::endl;

    auto input = std::vector<std::uint8_t>();
    wrapper->read_raw(input);

    auto stream = streams::memory_stream(std::move(input));
    auto reader = streams::stream_reader<streams::stream>(stream);

    auto state = shader_decode_state::initial;

    auto vertex_source = std::string();
    auto fragment_source = std::string();

    while (!stream.eof())
    {
        auto line = reader.read_line();

        if (line.empty())
            continue;

        if (line[0] == '[')
        {
            if (line.compare(0, 8, "[vertex]") == 0)
            {
                state = shader_decode_state::parsing_vertex;
                continue;
            }

            if (line.compare(0, 10, "[fragment]") == 0)
            {
                state = shader_decode_state::parsing_fragment;
                continue;
            }

            AEON_LOG_ERROR(logger_) << "Could not decode shader resource. Unexpected token '['."
                                       "Must be either '[vertex]' or '[fragment]'."
                                    << std::endl;

            throw shader_codec_decode_exception();
        }

        if (state == shader_decode_state::parsing_vertex)
        {
            vertex_source += line + '\n';
        }
        else if (state == shader_decode_state::parsing_fragment)
        {
            fragment_source += line + '\n';
        }
    }

    auto shader_data = data::shader(vertex_source, fragment_source);
    return std::make_shared<shader>(wrapper, std::move(shader_data));
}

} // namespace resources
} // namespace aeon
