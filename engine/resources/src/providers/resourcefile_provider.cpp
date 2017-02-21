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

#include <aeon/resources/providers/resourcefile_provider.h>

namespace aeon
{
namespace resources
{

resourcefile_provider::resourcefile_provider(const std::string &base_path)
    : base_path_(base_path)
{
}

auto resourcefile_provider::exists(const std::string &) const -> bool
{
    throw resourcefile_provider_not_implemented_exception();
}

auto resourcefile_provider::list(const std::string &) const -> std::vector<resource_node>
{
    throw resourcefile_provider_not_implemented_exception();
}

void resourcefile_provider::read(const std::string &, std::vector<std::uint8_t> &)
{
    throw resourcefile_provider_not_implemented_exception();
}

auto resourcefile_provider::get_encoding(const std::string &) const -> resource_encoding
{
    throw resourcefile_provider_not_implemented_exception();
}

} // namespace resources
} // namespace aeon
