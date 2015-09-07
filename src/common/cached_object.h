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
#include <cstdint>

namespace aeon
{
namespace common
{

using cached_handle = std::uint64_t;

class cached_object
{
public:
    cached_object(cached_handle handle, const std::string &name) :
        handle_(handle),
        name_(name)
    {
    }
    
    virtual ~cached_object()
    {
    }
    
    const cached_handle get_cached_handle() const
    {
        return handle_;
    }
    
    const std::string &get_cached_name() const
    {
        return name_;
    }
    
private:
    cached_handle handle_;
    std::string name_;
};

} // namespace common
} // namespace aeon
