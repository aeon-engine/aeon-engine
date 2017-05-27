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

#include <managed_interface/Object.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_class.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

mono_class_field Object::native_object_field;

static void Object_Finalize(MonoObject *this_ptr)
{
    mono_class_instance cls(this_ptr);

    // TODO: Add additional overloads or template for set_field_value
    // so that nullptr can be passed in directly.
    Object *null_obj = nullptr;
    cls.set_field_value<Object *>(Object::native_object_field, null_obj);
    delete &Object::get_managed_object_as<Object>(this_ptr);
}

void Object::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Object::Finalize", Object_Finalize);
}

void Object::initialize_class_field(mono_assembly &assembly)
{
    auto object_class = assembly.get_class("AeonEngineMono", "Object");
    native_object_field = object_class.get_field("m_NativePtr");
}

Object::Object(MonoObject *object)
    : managed_object_(object)
    , gc_handle_(object)
{
    mono_class_instance cls(object);

    // TODO: Add additional overloads or template for set_field_value
    // so that "this" can be passed in directly.
    Object *obj = this;
    cls.set_field_value<Object *>(native_object_field, obj);
}

Object::~Object() = default;

auto Object::get_managed_object() const -> MonoObject *
{
    return managed_object_;
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
