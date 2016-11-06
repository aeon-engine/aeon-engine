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

#include <aeon/resources/wrappers/resource_wrapper.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

class material;
class material_resource_wrapper : public resource_wrapper
{
public:
    explicit material_resource_wrapper(resource_manager &parent, const std::string &path,
                                       const std::weak_ptr<resource_provider> &provider);
    virtual ~material_resource_wrapper() = default;

    auto open() -> std::shared_ptr<material>;
};

} // namespace resources
} // namespace aeon
