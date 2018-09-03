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

#include <aeon/mono/mono_assembly.h>
#include <aeon/mono/mono_gc_handle.h>
#include <aeon/mono/mono_class.h>
#include <aeon/mono/mono_class_field.h>
#include <aeon/mono/mono_class_instance.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

class object
{
public:
    static void register_internal_calls();
    static void initialize_class_field(mono_assembly &assembly);

    explicit object(MonoObject *object);
    virtual ~object();

    object(const object &) noexcept = delete;
    auto operator=(const object &) noexcept -> object & = delete;

    object(object &&) noexcept = delete;
    auto operator=(object &&) noexcept -> object & = delete;

    auto get_managed_object() const -> MonoObject *;

    static mono_class object_class;
    static mono_class_field native_object_field;

    template <typename T>
    static auto &get_managed_object_as(MonoObject *this_ptr);

private:
    static void finalize(MonoObject *this_ptr);

    MonoObject *managed_object_;
    mono_gc_handle gc_handle_;
    mono_scoped_gc_handle gc_scoped_handle_;
};

template <typename T>
auto &object::get_managed_object_as(MonoObject *this_ptr)
{
    mono_class_instance cls(this_ptr);
    return *cls.get_field_value<T *>(native_object_field);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
