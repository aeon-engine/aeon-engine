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

#pragma once

#include <string>
#include <memory>

namespace aeon
{
namespace gfx
{

class resource
{
public:
    resource();
    virtual ~resource();

    virtual const std::string to_string() const = 0;
};

using resource_ptr = std::shared_ptr<resource>;

} // namespace gfx
} // namespace aeon
