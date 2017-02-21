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

#include <aeon/mono.h>

namespace aeon
{
namespace mono
{

mono_class_instance::mono_class_instance(MonoDomain *domain, MonoClass *cls)
    : mono_object(domain)
    , object_(nullptr)
    , class_(cls)
{
    object_ = mono_object_new(domain, cls);
    mono_runtime_object_init(object_);
    handle_ = mono_gchandle(object_);
}

mono_class_instance::~mono_class_instance()
{
}

mono_class_instance::mono_class_instance(mono_class_instance &&o)
    : mono_object(std::move(o))
    , object_(o.object_)
    , class_(o.class_)
{
}

mono_class_instance &mono_class_instance::operator=(mono_class_instance &&o)
{
    mono_object::operator=(std::move(o));
    object_ = o.object_;
    class_ = o.class_;
    return *this;
}

mono_method mono_class_instance::get_method(const std::string &name, int argc /*= 0*/)
{
    return mono_method(class_, object_, name, argc);
}

MonoObject *mono_class_instance::get_mono_object() const
{
    return object_;
}

} // namespace mono
} // namespace aeon
