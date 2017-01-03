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

#include <string>

namespace aeon
{
namespace common
{

/*!
 * Base class used for object caching. To make sure certain objects like assets
 * are not created multiple times, they are cached by "cache name"
 * (usually file path) by the object_cache.
 *
 * All objects that can be cached in the object_cache class must be dirived from
 * this class.
 */
class cached_object
{
    template <typename T>
    friend class object_cache;

public:
    /*!
     * Constructor
     */
    cached_object()
        : name_("Unnamed")
    {
    }

    /*!
     * Destructor
     */
    virtual ~cached_object() = default;

    /*!
     * Get the cached name of this object. Usually this is a file name or path.
     * \return The cached name of this object.
     */
    const auto &get_cached_name() const
    {
        return name_;
    }

private:
    std::string name_;
};

} // namespace common
} // namespace aeon
