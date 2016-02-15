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

#pragma once

#include <resources/exceptions.h>
#include <resources/resource_encoding.h>
#include <resources/codecs/codec.h>
#include <resources/atlas.h>
#include <common/types/rectangle.h>
#include <string>

namespace aeon
{
namespace resources
{

class atlas_resource_wrapper;
class resource_manager;

class atlas_codec : public codec
{
public:
    atlas_codec() = default;
    virtual ~atlas_codec() = default;

    resource_encoding get_codec_type() const override;

    atlas_ptr decode(resource_manager &parent, gfx::device &device, atlas_resource_wrapper_ptr wrapper);

private:
    struct atlas_data
    {
        int x, y, width, height;
    };

    atlas_data __atlas_string_to_data(const std::string &str) const;

    common::types::rectangle<float> __atlas_data_to_uv(const atlas_data &data, unsigned int texture_width,
                                                       unsigned int texture_height) const;
};

using atlas_codec_ptr = std::shared_ptr<atlas_codec>;

} // namespace resources
} // namespace aeon
