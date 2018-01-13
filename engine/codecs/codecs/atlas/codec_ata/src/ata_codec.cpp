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

#include <aeon/codecs/ata_codec.h>
#include <aeon/utility/configfile.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/common/logger.h>
#include <aeon/common/string.h>

namespace aeon
{
namespace codecs
{

atlas_codec_ata::atlas_codec_ata()
    : logger_(common::logger::get_singleton(), "Codecs::AtlasCodec")
{
}

atlas_codec_ata::~atlas_codec_ata() = default;

auto atlas_codec_ata::decode(const std::unique_ptr<resources::resource_provider> &provider) const
    -> std::unique_ptr<resources::atlas>
{
    AEON_LOG_DEBUG(logger_) << "Decoding atlas resource." << std::endl;

    auto atlas_file = utility::configfile();
    atlas_file.load(*provider);

    if (!atlas_file.has_entry("material"))
    {
        AEON_LOG_ERROR(logger_) << "Could not decode atlas resource. Could not find material entry." << std::endl;
        throw atlas_codec_decode_exception();
    }

    auto material_path = atlas_file.get<std::string>("material", "");

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

    return std::make_unique<resources::atlas>(material_path, atlas_data);
}

void atlas_codec_ata::encode(std::shared_ptr<resources::atlas> /*source*/,
                             const std::unique_ptr<resources::resource_provider> & /*destination*/) const
{
    AEON_LOG_ERROR(logger_) << "Atlas encoding is not implemented." << std::endl;
    throw atlas_codec_encode_exception();
}

auto atlas_codec_ata::__atlas_string_to_data(const std::string &str) const -> common::types::rectangle<float>
{
    auto items = common::string::split(str, ',');

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

} // namespace codecs
} // namespace aeon
