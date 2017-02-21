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

mono_method::mono_method(MonoClass *cls, const std::string &name, int argc)
    : class_(cls)
    , name_(name)
    , argc_(argc)
    , method_(nullptr)
    , object_(nullptr)
{
    method_ = mono_class_get_method_from_name(cls, name.c_str(), argc);
}

mono_method::mono_method(MonoClass *cls, MonoObject *object, const std::string &name, int argc)
    : class_(cls)
    , name_(name)
    , argc_(argc)
    , method_(nullptr)
    , object_(object)
{
    method_ = mono_class_get_method_from_name(cls, name.c_str(), argc);
}

mono_method::~mono_method()
{
}

mono_method::mono_method(mono_method &&o)
    : class_(o.class_)
    , name_(std::move(o.name_))
    , argc_(o.argc_)
    , method_(o.method_)
    , object_(o.object_)
{
}

mono_method &mono_method::operator=(mono_method &&o)
{
    class_ = o.class_;
    name_ = std::move(o.name_);
    argc_ = o.argc_;
    method_ = o.method_;
    object_ = o.object_;
    return *this;
}

void mono_method::operator()()
{
    void *params[1] = {nullptr};
    execute(params);
}

void mono_method::operator()(std::vector<mono_object *> params)
{
    std::vector<MonoObject *> real_params;
    for (auto p : params)
    {
        real_params.push_back(p->get_mono_object());
    }

    execute(reinterpret_cast<void **>(real_params.data()));
}

void mono_method::execute(void **params)
{
    MonoObject *ret_value = mono_runtime_invoke(method_, object_, params, nullptr);

    if (!ret_value)
        return;
}

} // namespace mono
} // namespace aeon
