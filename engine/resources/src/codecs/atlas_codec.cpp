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
#include <aeon/resources/codecs/atlas_codec.h>
#include <aeon/resources/wrappers/atlas_resource_wrapper.h>
#include <aeon/common/buffer.h>

namespace aeon
{
namespace resources
{

atlas_codec::atlas_codec()
    : logger_(common::logger::get_singleton(), "Resources::AtlasCodec")
{
}

resource_encoding atlas_codec::get_codec_type() const
{
    return resource_encoding::atlas;
}

atlas_ptr atlas_codec::decode(resource_manager &parent, atlas_resource_wrapper_ptr wrapper)
{
    AEON_LOG_DEBUG(logger_) << "Decoding atlas resource." << std::endl;

    common::buffer_u8 input;
    wrapper->read_raw(input);

    streams::memory_stream stream(std::move(input));
    utility::configfile atlas_file;
    atlas_file.load(stream);

    if (!atlas_file.has_entry("material"))
    {
        AEON_LOG_ERROR(logger_) << "Could not decode atlas resource. Could not find material entry." << std::endl;
        throw atlas_codec_decode_exception();
    }

    material_resource_wrapper_ptr material_res_wrapper =
        parent.load_material_wrapper(atlas_file.get<std::string>("material", ""));
    material_ptr material_res = material_res_wrapper->open();

    data::atlas atlas_data;

    for (auto region_entry : atlas_file)
    {
        if (region_entry.first == "material")
            continue;

        common::types::rectangle<float> region_rect = __atlas_string_to_data(region_entry.second);

        atlas_data.push_back({region_entry.first, region_rect.x, region_rect.y, region_rect.width, region_rect.height});
    }

    AEON_LOG_DEBUG(logger_) << "Found " << atlas_data.size() << " regions in atlas resource." << std::endl;

    return std::make_shared<resources::atlas>(wrapper, material_res_wrapper->get_path(), atlas_data);
}

common::types::rectangle<float> atlas_codec::__atlas_string_to_data(const std::string &str) const
{
    std::vector<std::string> items = utility::string::split(str, ',');

    if (items.size() != 4)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode atlas resource. Expected 4 tokens, got " << items.size() << "."
                                << std::endl;
        throw atlas_codec_decode_exception();
    }

    float left = 0;
    float right = 0;
    float top = 0;
    float bottom = 0;

    try
    {
        left = std::stof(items[0]);
        right = std::stof(items[1]);
        top = std::stof(items[2]);
        bottom = std::stof(items[3]);
    }
    catch (const std::invalid_argument &)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode atlas resource. Not a number." << std::endl;
        throw atlas_codec_decode_exception();
    }
    catch (const std::out_of_range &)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode atlas resource. Number out of range." << std::endl;
        throw atlas_codec_decode_exception();
    }

    return {left, right, top, bottom};
}

} // namespace resources
} // namespace aeon
