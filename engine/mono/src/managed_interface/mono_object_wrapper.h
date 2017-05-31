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

#include <managed_interface/core/object.h>
#include <memory>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

template <typename T>
class mono_object_wrapper : public object
{
public:
    explicit mono_object_wrapper(MonoObject *object, T obj);
    virtual ~mono_object_wrapper();

    static void create(MonoObject *object, T obj);

    static auto &get_native_object(MonoObject *object);

private:
    T native_object;
};

template <typename T>
void mono_object_wrapper<T>::create(MonoObject *object, T obj)
{
    std::make_unique<mono_object_wrapper<T>>(object, std::move(obj)).release();
}

template <typename T>
mono_object_wrapper<T>::mono_object_wrapper(MonoObject *object, T obj)
    : object(object)
    , native_object(std::move(obj))
{
}

template <typename T>
mono_object_wrapper<T>::~mono_object_wrapper() = default;

template <typename T>
auto &mono_object_wrapper<T>::get_native_object(MonoObject *object)
{
    return object::get_managed_object_as<mono_object_wrapper<T>>(object).native_object;
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
