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

#include <aeon/resources/providers/resource_collection_provider.h>
#include <managed_interface/Object.h>
#include <memory>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

class ResourceCollectionProvider : public Object
{
public:
    explicit ResourceCollectionProvider(MonoObject *object,
                                        std::unique_ptr<resources::resource_collection_provider> provider);
    virtual ~ResourceCollectionProvider();

    std::unique_ptr<resources::resource_collection_provider> provider;
};

inline ResourceCollectionProvider::ResourceCollectionProvider(
    MonoObject *object, std::unique_ptr<resources::resource_collection_provider> provider)
    : Object(object)
    , provider(std::move(provider))
{
}

inline ResourceCollectionProvider::~ResourceCollectionProvider() = default;

} // namespace managed_interface
} // namespace mono
} // namespace aeon
