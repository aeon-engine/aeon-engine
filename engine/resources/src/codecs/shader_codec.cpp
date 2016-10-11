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
#include <aeon/common/buffer.h>

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

shader_ptr shader_codec::decode(resource_manager & /*parent*/, shader_resource_wrapper_ptr wrapper)
{
    // TODO: Add error handling for missing segments in the resource file

    AEON_LOG_DEBUG(logger_) << "Decoding shader resource." << std::endl;

    common::buffer_u8 input;
    wrapper->read_raw(input);

    streams::memory_stream stream(std::move(input));
    streams::stream_reader<streams::stream> reader(stream);

    shader_decode_state state = shader_decode_state::initial;

    std::string vertex_source;
    std::string fragment_source;

    while (!stream.eof())
    {
        std::string line = reader.read_line();

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

    data::shader shader_data(vertex_source, fragment_source);
    return std::make_shared<shader>(wrapper, shader_data);
}

} // namespace resources
} // namespace aeon
