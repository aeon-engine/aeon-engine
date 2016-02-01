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
#include <resources/codecs/material_codec.h>
#include <resources/wrappers/material_resource_wrapper.h>
#include <common/buffer.h>

namespace aeon
{
namespace resources
{

resource_encoding material_codec::get_codec_type() const
{
    return resource_encoding::material;
}

material_ptr material_codec::decode(resource_manager &parent, material_resource_wrapper_ptr wrapper)
{
    common::buffer_u8 input;
    wrapper->read_raw(input);

    streams::memory_stream stream(std::move(input));
    utility::configfile material_file;
    material_file.load(stream);

    if (!material_file.has_entry("texture"))
        throw material_codec_decode_exception();

    // For some reason I need to put class in front... I have no idea -Robin.
    material_ptr material = std::make_shared<class material>(wrapper);
    image_resource_wrapper_ptr texture_res = parent.load_image(material_file.get<std::string>("texture", ""));

    material->set_texture_data(texture_res->open());

    return material;
}

} // namespace resources
} // namespace aeon