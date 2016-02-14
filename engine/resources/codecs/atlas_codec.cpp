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
#include <resources/codecs/atlas_codec.h>
#include <resources/wrappers/atlas_resource_wrapper.h>
#include <common/buffer.h>

namespace aeon
{
namespace resources
{

resource_encoding atlas_codec::get_codec_type() const
{
    return resource_encoding::atlas;
}

atlas_ptr atlas_codec::decode(resource_manager &parent, atlas_resource_wrapper_ptr wrapper)
{
    common::buffer_u8 input;
    wrapper->read_raw(input);

    streams::memory_stream stream(std::move(input));
    utility::configfile atlas_file;
    atlas_file.load(stream);

    if (!atlas_file.has_entry("material"))
        throw atlas_codec_decode_exception();

    material_resource_wrapper_ptr material_res_wrapper =
        parent.load_material_wrapper(atlas_file.get<std::string>("material", ""));
    material_ptr material_res = material_res_wrapper->open();

    unsigned int texture_width = material_res->get_texture()->get_width();
    unsigned int texture_height = material_res->get_texture()->get_height();

    atlas_regions regions;
    atlas_region_names names;

    for (auto region_entry : atlas_file)
    {
        if (region_entry.first == "material")
            continue;

        common::types::rectangle<float> region_rect =
            __atlas_string_to_rectangle(region_entry.second, texture_width, texture_height);

        atlas_region region(region_rect.left, region_rect.top, region_rect.right, region_rect.bottom);

        names.insert({region_entry.first, regions.size()});
        regions.push_back(region);
    }

    return std::make_shared<resources::atlas>(wrapper, material_res, regions, names);
}

common::types::rectangle<float> atlas_codec::__atlas_string_to_rectangle(const std::string &str,
    unsigned int texture_width, unsigned int texture_height) const
{
    std::vector<std::string> items = utility::string::split(str, ',');

    if (items.size() != 4)
        throw atlas_codec_decode_exception();

    int x = 0;
    int y = 0;
    int width = 0;
    int height = 0;

    try
    {
        x = std::stoi(items[0]);
        y = std::stoi(items[1]);
        width = std::stoi(items[2]);
        height = std::stoi(items[3]);
    }
    catch (const std::invalid_argument &)
    {
        throw atlas_codec_decode_exception();
    }
    catch (const std::out_of_range &)
    {
        throw atlas_codec_decode_exception();
    }

    float left = static_cast<float>(x) / static_cast<float>(texture_width);
    float right = static_cast<float>(x + width) / static_cast<float>(texture_width);
    float top = static_cast<float>(y) / static_cast<float>(texture_height);
    float bottom = static_cast<float>(y + height) / static_cast<float>(texture_height);

    return { left, top, right, bottom };
}

} // namespace resources
} // namespace aeon
