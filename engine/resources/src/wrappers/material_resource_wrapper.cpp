/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

#include <aeon/resources/wrappers/material_resource_wrapper.h>
#include <aeon/resources/resource_manager.h>

namespace aeon
{
namespace resources
{

material_resource_wrapper::material_resource_wrapper(resource_manager &parent, const std::string &path,
                                                     const std::weak_ptr<resource_provider> &provider)
    : resource_wrapper(parent, path, provider)
{
    if (get_type() != resource_type::material)
        throw resource_type_exception();
}

auto material_resource_wrapper::open() -> std::shared_ptr<material>
{
    auto &codec = __get_parent().get_codec_manager().get_material_codec();
    return codec.decode(std::dynamic_pointer_cast<material_resource_wrapper>(shared_from_this()));
}

} // namespace resources
} // namespace aeon
