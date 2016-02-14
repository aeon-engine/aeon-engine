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

#include <resources/wrappers/atlas_resource_wrapper.h>
#include <resources/resource_manager.h>
#include <resources/codecs/atlas_codec.h>

namespace aeon
{
namespace resources
{

atlas_resource_wrapper::atlas_resource_wrapper(resource_manager &parent, const std::string &path,
                                               resource_provider_weak_ptr provider)
    : resource_wrapper(parent, path, provider)
{
    if (get_type() != resource_type::atlas)
        throw resource_type_exception();
}

atlas_ptr atlas_resource_wrapper::open(gfx::device &device)
{
    atlas_codec_ptr codec = __get_parent().get_codec_manager().get_atlas_codec();
    return codec->decode(__get_parent(), device, std::dynamic_pointer_cast<atlas_resource_wrapper>(shared_from_this()));
}

} // namespace resources
} // namespace aeon
