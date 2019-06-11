/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/codecs/amf_codec.h>
#include <aeon/serialization/serialization.h>
#include <aeon/common/logger.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <json11.hpp>

namespace aeon::codecs
{

material_codec_amf::material_codec_amf()
    : logger_(common::logger::get_singleton(), "Codecs::Amf")
{
}

material_codec_amf::~material_codec_amf() = default;

auto material_codec_amf::decode(const std::unique_ptr<resources::resource_provider> &provider) const
    -> std::unique_ptr<resources::material>
{
    AEON_LOG_DEBUG(logger_) << "Decoding material resource." << std::endl;

    streams::stream_reader reader(provider->get_stream());
    auto input = reader.read_to_string();

    auto error_string = std::string();
    auto json = json11::Json::parse(input, error_string, json11::JsonParse::STANDARD);

    if (!error_string.empty())
    {
        AEON_LOG_ERROR(logger_) << "Parse error while decoding material. Message was: " << error_string << std::endl;
        throw material_codec_decode_exception();
    }

    serialization::material material_file_data(json);
    return std::make_unique<resources::material>(std::move(material_file_data));
}

void material_codec_amf::encode(std::shared_ptr<resources::material> source,
                                const std::unique_ptr<resources::resource_provider> &destination) const
{
    streams::stream_writer writer(destination->get_stream());
    writer << source->get_material_data().to_json().dump();
}

} // namespace aeon::codecs
