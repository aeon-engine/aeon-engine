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

#pragma once

#include <aeon/resources/resource.h>
#include <aeon/resources/wrappers/world_resource_wrapper.h>
#include <aeon/serialization/serialization.h>
#include <aeon/common/logger.h>
#include <memory>

namespace aeon
{
namespace resources
{

class world : public resource
{
public:
    explicit world(const std::shared_ptr<resource_wrapper> &wrapper, serialization::world &&world_data);
    virtual ~world();

    const auto &get_material_data() const
    {
        return world_data_;
    }

    auto get_material_resource_wrapper() const
    {
        return std::dynamic_pointer_cast<world_resource_wrapper>(get_resource_wrapper());
    }

private:
    logger::logger logger_;
    serialization::world world_data_;
};

} // namespace resources
} // namespace aeon
