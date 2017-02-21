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

class mono_assembly;

/*!
 * Class to initialize the Mono JIT. This class must be instanced
 * only once. When this class is deleted, the JIT is cleaned up.
 *
 * Due to the way Mono works, a cleaned up JIT can not be reinitialized
 * at runtime after it was cleaned up. You must keep this class instanced
 * during the full runtime of the application.
 */
class mono_jit : utility::noncopyable
{
public:
    mono_jit();
    explicit mono_jit(const std::string &domain);
    ~mono_jit();

    mono_assembly load_assembly(const std::string &path) const;

private:
    MonoDomain *domain_;
};

} // namespace mono
} // namespace aeon
