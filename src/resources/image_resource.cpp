/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <resources/image_resource.h>
#include <resources/resource_manager.h>

namespace aeon
{
namespace resources
{

image_resource::image_resource(resource_manager &parent, const std::string &path,
                               resource_provider_weak_ptr provider) :
    resource(parent, path, provider)
{
    if (get_type() != resource_type::image)
        throw resource_type_exception();
}

image_resource::~image_resource()
{
}

image_ptr image_resource::open()
{
    image_codec_ptr codec = __get_parent().get_codec_manager().get_image_codec(get_encoding());

    common::buffer_u8 buffer;
    __read_raw(buffer);

    return codec->decode(buffer);
}

} // namespace resources
} // namespace aeon
