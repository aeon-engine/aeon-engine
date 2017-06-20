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

#include <aeon/mono/mono_type_conversion.h>
#include <aeon/resources/providers/resource_collection_provider.h>
#include <mono/metadata/object.h>
#include <managed_interface/mono_object_wrapper.h>

namespace aeon
{
namespace mono
{

template <>
struct convert_mono_type<std::unique_ptr<resources::resource_collection_provider>>
{
    using mono_type_name = MonoObject *;

    static auto from_mono(MonoObject *object) -> std::unique_ptr<resources::resource_collection_provider>
    {
        auto &collection_provider = managed_interface::mono_object_wrapper<
            std::unique_ptr<resources::resource_collection_provider>>::get_native_object(object);
        return std::move(collection_provider);
    }
};

namespace managed_interface
{

class resource_manager
{
public:
    static void register_internal_calls();

private:
    static void mount(std::unique_ptr<resources::resource_collection_provider> provider, std::string mount_point);
    static void unmount(std::string mount_point);
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
