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

#include <aeon/resources/wrappers/image_resource_wrapper.h>
#include <aeon/resources/resource_manager.h>

namespace aeon
{
namespace resources
{

image_resource_wrapper::image_resource_wrapper(resource_manager &parent, const std::string &path,
                                               resource_provider_weak_ptr provider)
    : resource_wrapper(parent, path, provider)
{
    if (get_type() != resource_type::image)
        throw resource_type_exception();
}

image_ptr image_resource_wrapper::open()
{
    image_codec &codec = __get_parent().get_codec_manager().get_image_codec(get_encoding());
    return codec.decode(__get_parent(), std::dynamic_pointer_cast<image_resource_wrapper>(shared_from_this()));
}

} // namespace resources
} // namespace aeon