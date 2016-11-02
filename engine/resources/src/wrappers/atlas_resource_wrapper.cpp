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

#include <aeon/resources/wrappers/atlas_resource_wrapper.h>
#include <aeon/resources/resource_manager.h>
#include <aeon/resources/codecs/atlas_codec.h>

namespace aeon
{
namespace resources
{

atlas_resource_wrapper::atlas_resource_wrapper(resource_manager &parent, const std::string &path,
                                               const std::weak_ptr<resource_provider> &provider)
    : resource_wrapper(parent, path, provider)
{
    if (get_type() != resource_type::atlas)
        throw resource_type_exception();
}

std::shared_ptr<atlas> atlas_resource_wrapper::open()
{
    atlas_codec &codec = __get_parent().get_codec_manager().get_atlas_codec();
    return codec.decode(__get_parent(), std::dynamic_pointer_cast<atlas_resource_wrapper>(shared_from_this()));
}

} // namespace resources
} // namespace aeon
