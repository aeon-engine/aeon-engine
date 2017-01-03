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

#include <type_traits>
#include <aeon/common/exception.h>
#include <aeon/common/cached_object.h>
#include <aeon/utility.h>
#include <map>

namespace aeon
{
namespace common
{

DEFINE_EXCEPTION_OBJECT(object_cache_exception, exception, "object_cache_exception");
DEFINE_EXCEPTION_OBJECT(object_cache_name_exception, object_cache_exception,
                        "There is already an object cached with the same name.");

/*!
 * Generic templated base class for cachable objects, like assets. Objects are cached by name.
 * If an object is still referenced anywhere, get_cached_object will return the existing object,
 * otherwise it will return a nullptr.
 *
 * This class does not take ownership of the cached objects, as it merely stores weak pointers.
 */
template <typename T>
class object_cache : utility::noncopyable
{
public:
    using cached_objects = std::map<std::string, std::weak_ptr<T>>;

    /*!
     * Constructor
     */
    object_cache()
    {
        static_assert(std::is_base_of<cached_object, T>::value,
                      "Object given to object_cache must be derived from aeon::common::cached_object.");
    }

    /*!
     * Destructor
     */
    virtual ~object_cache() = default;

    /*!
     * Get a cached object by name. This method will return a shared pointer to the requested object
     * or a nullptr. If the object was found to be expired, a garbage collection will be triggered to
     * clean up expired weak pointers.
     */
    auto get_cached_object(const std::string &name) -> std::shared_ptr<T>
    {
        auto result = objects_.find(name);

        if (result == objects_.end())
            return nullptr;

        auto object = result->second;

        if (object.expired())
        {
            garbage_collect_cached_objects();
            return nullptr;
        }

        return object.lock();
    }

    /*!
     * Register a newly created object to be cached. If an object with the same name is found, which is not yet expired,
     * an object_cache_name_exception is thrown. This method will take a weak pointer of the given shared pointer to
     * store internally.
     */
    void add_cached_object(const std::string &name, const std::shared_ptr<T> &obj)
    {
        obj->name_ = name;

        auto result = objects_.find(name);
        if (result != objects_.end())
        {
            if (!result->second.expired())
            {
                throw object_cache_name_exception();
            }

            garbage_collect_cached_objects();
        }

        objects_[name] = obj;
    }

    /*!
     * Garbage collect all expired cached objects.
     */
    void garbage_collect_cached_objects()
    {
        utility::container::erase_if(objects_, [](const auto &obj) { return obj.second.expired(); });
    }

private:
    cached_objects objects_;
};

} // namespace common
} // namespace aeon
