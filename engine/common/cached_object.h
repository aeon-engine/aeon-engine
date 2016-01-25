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

#include <string>

namespace aeon
{
namespace common
{

class cached_object
{
    template <typename T>
    friend class object_cache;

public:
    cached_object()
        : name_("Unnamed")
    {
    }

    virtual ~cached_object()
    {
    }

    const std::string &get_cached_name() const
    {
        return name_;
    }

private:
    std::string name_;
};

} // namespace common
} // namespace aeon
