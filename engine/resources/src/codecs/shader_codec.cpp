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

#include <aeon/resources/resource_manager.h>
#include <aeon/resources/codecs/shader_codec.h>
#include <aeon/resources/wrappers/shader_resource_wrapper.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/streams/stream_reader.h>

namespace aeon
{
namespace resources
{

shader_codec::shader_codec()
    : logger_(common::logger::get_singleton(), "Resources::ShaderCodec")
{
}

auto shader_codec::get_codec_type() const -> resource_encoding
{
    return resource_encoding::material;
}

auto shader_codec::decode(resource_manager & /*parent*/, const std::shared_ptr<shader_resource_wrapper> &wrapper) const
    -> std::shared_ptr<shader>
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
    return std::make_shared<shader>(std::move(shader_data));
}

} // namespace resources
} // namespace aeon
