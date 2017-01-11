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
#include <aeon/resources/codecs/world_codec.h>
#include <aeon/resources/wrappers/world_resource_wrapper.h>
#include <aeon/serialization/serialization.h>
#include <json11.hpp>

namespace aeon
{
namespace resources
{

world_codec::world_codec()
    : logger_(common::logger::get_singleton(), "Resources::WorldCodec")
{
}

auto world_codec::get_codec_type() const -> resource_encoding
{
    return resource_encoding::world;
}

auto world_codec::decode(const std::shared_ptr<world_resource_wrapper> &wrapper) const -> std::shared_ptr<world>
{
    AEON_LOG_DEBUG(logger_) << "Decoding world resource." << std::endl;

    auto input = std::string();
    wrapper->read_raw(input);

    auto error_string = std::string();
    auto json = json11::Json::parse(input, error_string, json11::JsonParse::STANDARD);

    if (!error_string.empty())
    {
        AEON_LOG_ERROR(logger_) << "Parse error while decoding world. Message was: " << error_string << std::endl;
        throw material_codec_decode_exception();
    }

    serialization::world world_file_data(json);

    return std::make_shared<resources::world>(wrapper, std::move(world_file_data));
}

} // namespace resources
} // namespace aeon
