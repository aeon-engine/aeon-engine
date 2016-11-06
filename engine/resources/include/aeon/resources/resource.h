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

namespace aeon
{
namespace resources
{

class resource
{
public:
    resource(const std::shared_ptr<resource_wrapper> &wrapper)
        : wrapper_(wrapper)
    {
    }

    virtual ~resource() = default;

    const auto &get_resource_wrapper() const
    {
        return wrapper_;
    }

private:
    std::shared_ptr<resource_wrapper> wrapper_;
};

} // namespace resources
} // namespace aeon
