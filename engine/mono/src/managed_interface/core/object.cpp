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

#include <managed_interface/core/object.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_class.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

mono_class object::object_class;
mono_class_field object::native_object_field;

void object::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Core.Object::Finalize", &object::finalize);
}

void object::initialize_class_field(mono_assembly &assembly)
{
    object_class = assembly.get_class("AeonEngineMono.Core", "Object");
    native_object_field = object_class.get_field("m_NativePtr");
}

object::object(MonoObject *mono_object)
    : managed_object_(mono_object)
    , gc_handle_(mono_object)
    , gc_scoped_handle_(gc_handle_)
{
    mono_class_instance cls(mono_object);

    assert(mono_class_is_subclass_of(cls.get_class().get_mono_class_ptr(), object_class.get_mono_class_ptr(), false) &&
           "Mono wrapper classes must inherit from Object.");

    // TODO: Add additional overloads or template for set_field_value
    // so that "this" can be passed in directly.
    auto obj = this;
    cls.set_field_value<object *>(native_object_field, obj);
}

object::~object() = default;

auto object::get_managed_object() const -> MonoObject *
{
    return managed_object_;
}

void object::finalize(MonoObject *this_ptr)
{
    mono_class_instance cls(this_ptr);

    // TODO: Add additional overloads or template for set_field_value
    // so that nullptr can be passed in directly.
    object *null_obj = nullptr;
    cls.set_field_value<object *>(object::native_object_field, null_obj);
    delete &object::get_managed_object_as<object>(this_ptr);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
