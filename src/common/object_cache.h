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

#include <common/cached_object.h>
#include <aeon/utility.h>
#include <vector>
#include <queue>

namespace aeon
{
namespace common
{

template <typename T>
class object_cache
{
public:
    using cached_object = std::weak_ptr<T>;
    using cached_objects = aeon::utility::linear_map<std::string, cached_object>;

    object_cache()
    {
    }
    
    virtual ~object_cache()
    {
    }

private:
    cached_objects objects_;
};

} // namespace common
} // namespace aeon
