/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/common/container.h>
#include <aeon/common/exception.h>
#include <aeon/common/cached_object.h>
#include <aeon/common/noncopyable.h>
#include <map>
#include <type_traits>
#include <memory>

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
class object_cache : common::noncopyable
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
        common::container::erase_if(objects_, [](const auto &obj) { return obj.second.expired(); });
    }

private:
    cached_objects objects_;
};

} // namespace common
} // namespace aeon
