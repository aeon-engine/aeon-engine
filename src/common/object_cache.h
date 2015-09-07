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

#include <type_traits>
#include <common/exception.h>
#include <common/cached_object.h>
#include <aeon/utility.h>

namespace aeon
{
namespace common
{

DEFINE_EXCEPTION_OBJECT(object_cache_exception, exception, "object_cache_exception");
DEFINE_EXCEPTION_OBJECT(object_cache_name_exception, object_cache_exception, "There is already an object cached with the same name.");

template <typename T>
class object_cache
{
public:
    using cached_object_ptr = std::shared_ptr<T>;
    using cached_object_weak_ptr = std::weak_ptr<T>;
    using cached_objects = aeon::utility::linear_map<std::string, cached_object_weak_ptr>;

    object_cache()
    {
        static_assert(
            std::is_base_of<cached_object, T>::value,
            "Object given to object_cache must be derived from aeon::common::cached_object."
        );
    }
    
    virtual ~object_cache()
    {
    }

protected:
    cached_object_ptr __get_cached_object(const std::string &name)
    {
        auto result = objects_.find(name);

        if (!result)
            return nullptr;

        return result->second.lock();
    }

    void __add_cached_object(const std::string &name, cached_object_ptr obj)
    {
        obj->name_ = name;

        if (objects_.insert_ex(name, obj) == objects_.end())
            throw object_cache_name_exception();
    }

    void __garbage_collect_cached_objects()
    {

    }

private:
    cached_objects objects_;
};

} // namespace common
} // namespace aeon
