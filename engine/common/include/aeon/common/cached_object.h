/*
 * Copyright (c) 2012-2017 Robin Degen
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
