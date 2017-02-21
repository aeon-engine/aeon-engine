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

namespace aeon
{
namespace mono
{

class mono_class;
class mono_class_instance;
class mono_string;

class mono_assembly : public utility::noncopyable
{
public:
    explicit mono_assembly(MonoDomain *domain, const std::string &path);
    ~mono_assembly();

    mono_assembly(mono_assembly &&o);
    mono_assembly &operator=(mono_assembly &&o);

    int execute();
    int execute(int argc, char *argv[]);

    mono_class get_class(const std::string &name);
    mono_class_instance new_class_instance(const mono_class &cls);
    mono_string new_string(const std::string &str);

private:
    MonoDomain *domain_;
    std::string path_;
    MonoAssembly *assembly_;
    MonoImage *image_;
};

} // namespace mono
} // namespace aeon
