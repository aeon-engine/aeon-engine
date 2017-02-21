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

#include <code_generator.h>

namespace aeon
{
namespace serialization
{

class code_generator_kvstring : public code_generator
{
public:
    code_generator_kvstring() = default;
    ~code_generator_kvstring() = default;

    auto get_type_name() const -> std::string override;

    auto generate_required_header_includes() const -> std::set<std::string> override;

    auto generate_cpp_type_name() const -> std::string override;

    auto generate_cpp_array_type_name() const -> std::string override;

    auto generate_deserialization_code(const object_member &object_member) const -> std::string override;

    auto generate_array_deserialization_code(const object_member &object_member) const -> std::string override;

    auto generate_serialization_code(const object_member &object_member) const -> std::string override;

    auto generate_array_serialization_code(const object_member &object_member) const -> std::string override;
};

} // namespace serialization
} // namespace aeon
