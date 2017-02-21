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

mono_assembly::mono_assembly(MonoDomain *domain, const std::string &path)
    : domain_(domain)
    , path_(path)
    , assembly_(nullptr)
    , image_(nullptr)
{
    assembly_ = mono_domain_assembly_open(domain, path.c_str());

    if (!assembly_)
        throw mono_exception();

    image_ = mono_assembly_get_image(assembly_);
}

mono_assembly::~mono_assembly()
{
}

mono_assembly::mono_assembly(mono_assembly &&o)
    : domain_(o.domain_)
    , path_(std::move(o.path_))
    , assembly_(o.assembly_)
    , image_(o.image_)
{
}

mono_assembly &mono_assembly::operator=(mono_assembly &&o)
{
    domain_ = o.domain_;
    path_ = std::move(o.path_);
    assembly_ = o.assembly_;
    image_ = o.image_;
    return *this;
}

int mono_assembly::execute()
{
    char *argv[1] = {const_cast<char *>(path_.c_str())};
    return execute(1, argv);
}

int mono_assembly::execute(int argc, char *argv[])
{
    return mono_jit_exec(domain_, assembly_, argc, argv);
}

mono_class mono_assembly::get_class(const std::string &name)
{
    return mono_class(image_, name);
}

mono_class_instance mono_assembly::new_class_instance(const mono_class &cls)
{
    return mono_class_instance(domain_, cls.get_mono_class_ptr());
}

mono_string mono_assembly::new_string(const std::string &str)
{
    return mono_string(domain_, str);
}

} // namespace mono
} // namespace aeon
