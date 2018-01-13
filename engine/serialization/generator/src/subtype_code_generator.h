/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <string>
#include <object.h>

namespace aeon
{
namespace serialization
{

class subtype_code_generator
{
public:
    subtype_code_generator() = default;
    virtual ~subtype_code_generator() = default;

    auto generate_cpp_deserialize(const object_member &object_member) const -> std::string;

    auto generate_cpp_deserialize_array(const object_member &object_member) const -> std::string;

    auto generate_cpp_deserialize_baseclass_array(const object_member &object_member) const -> std::string;

    auto generate_cpp_serialize(const object_member &object_member) const -> std::string;

    auto generate_cpp_serialize_array(const object_member &object_member) const -> std::string;

    auto generate_cpp_serialize_baseclass_array(const object_member &object_member) const -> std::string;
};

} // namespace serialization
} // namespace aeon
