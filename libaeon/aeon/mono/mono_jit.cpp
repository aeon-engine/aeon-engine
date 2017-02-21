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
#include <mono_build_config.h>

namespace aeon
{
namespace mono
{

mono_jit::mono_jit()
    : mono_jit("AeonMono")
{
}

mono_jit::mono_jit(const std::string &domain)
    : domain_(nullptr)
{
    mono_set_dirs(AEON_MONO_ASSEMBLY_DIR, AEON_MONO_CONFIG_DIR);
    domain_ = mono_jit_init(domain.c_str());

    if (!domain_)
        throw mono_exception();
}

mono_jit::~mono_jit()
{
    mono_jit_cleanup(domain_);
}

mono_assembly mono_jit::load_assembly(const std::string &path) const
{
    return mono_assembly(domain_, path);
}

} // namespace mono
} // namespace aeon
