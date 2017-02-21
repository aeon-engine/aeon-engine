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

#include <aeon/platform.h>
#include <aeon/streams.h>
#include <aeon/utility.h>
#include <aeon/resources/resource_manager.h>
#include <aeon/resources/codecs/scene_codec.h>
#include <aeon/resources/wrappers/scene_resource_wrapper.h>
#include <aeon/serialization/serialization.h>
#include <json11.hpp>

namespace aeon
{
namespace resources
{

scene_codec::scene_codec()
    : logger_(common::logger::get_singleton(), "Resources::SceneCodec")
{
}

auto scene_codec::get_codec_type() const -> resource_encoding
{
    return resource_encoding::scene;
}

auto scene_codec::decode(const std::shared_ptr<scene_resource_wrapper> &wrapper) const -> std::shared_ptr<scene>
{
    AEON_LOG_DEBUG(logger_) << "Decoding scene resource." << std::endl;

    auto input = std::string();
    wrapper->read_raw(input);

    auto error_string = std::string();
    auto json = json11::Json::parse(input, error_string, json11::JsonParse::STANDARD);

    if (!error_string.empty())
    {
        AEON_LOG_ERROR(logger_) << "Parse error while decoding scene. Message was: " << error_string << std::endl;
        throw material_codec_decode_exception();
    }

    serialization::scene scene_file_data(json);

    return std::make_shared<resources::scene>(wrapper, std::move(scene_file_data));
}

} // namespace resources
} // namespace aeon
