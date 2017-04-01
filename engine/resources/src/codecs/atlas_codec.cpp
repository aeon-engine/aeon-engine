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
#include <aeon/resources/codecs/atlas_codec.h>
#include <aeon/resources/wrappers/atlas_resource_wrapper.h>

namespace aeon
{
namespace resources
{

atlas_codec::atlas_codec()
    : logger_(common::logger::get_singleton(), "Resources::AtlasCodec")
{
}

auto atlas_codec::get_codec_type() const -> resource_encoding
{
    return resource_encoding::atlas;
}

auto atlas_codec::decode(resource_manager &parent, const std::shared_ptr<atlas_resource_wrapper> &wrapper) const
    -> std::shared_ptr<atlas>
{
    AEON_LOG_DEBUG(logger_) << "Decoding atlas resource." << std::endl;

    auto input = std::vector<std::uint8_t>();
    wrapper->read_raw(input);

    auto stream = streams::memory_stream(std::move(input));
    auto atlas_file = utility::configfile();
    atlas_file.load(stream);

    if (!atlas_file.has_entry("material"))
    {
        AEON_LOG_ERROR(logger_) << "Could not decode atlas resource. Could not find material entry." << std::endl;
        throw atlas_codec_decode_exception();
    }

    auto material_res_wrapper =
        parent.load_resource_wrapper<material_resource_wrapper>(atlas_file.get<std::string>("material", ""));
    auto material_res = material_res_wrapper->open();

    data::atlas atlas_data;

    for (auto region_entry : atlas_file)
    {
        if (region_entry.first == "material")
            continue;

        auto region_rect = __atlas_string_to_data(region_entry.second);

        // TODO: work out the region sizes in pixels
        atlas_data.push_back(data::atlas::region{region_entry.first, region_rect.left(), region_rect.top(),
                                                 region_rect.right(), region_rect.bottom(), 0, 0});
    }

    AEON_LOG_DEBUG(logger_) << "Found " << atlas_data.size() << " regions in atlas resource." << std::endl;

    return std::make_shared<resources::atlas>(material_res_wrapper->get_path(), atlas_data);
}

auto atlas_codec::__atlas_string_to_data(const std::string &str) const -> common::types::rectangle<float>
{
    auto items = utility::string::split(str, ',');

    if (items.size() != 4)
    {
        AEON_LOG_ERROR(logger_) << "Could not decode atlas resource. Expected 4 tokens, got " << items.size() << "."
                                << std::endl;
        throw atlas_codec_decode_exception();
    }

    auto left = 0.0f;
    auto right = 0.0f;
    auto top = 0.0f;
    auto bottom = 0.0f;

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

    return {left, top, right, bottom};
}

} // namespace resources
} // namespace aeon
