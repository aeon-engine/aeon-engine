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

#include <subtype_code_generator.h>
#include <aeon/common/stdfilesystem.h>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <object.h>
#include <code_generator.h>

namespace aeon::serialization
{

class generator
{
public:
    generator();
    ~generator() = default;

    void generate_code(const std::vector<object> &objects) const;

private:
    auto __generate_base_code() const -> std::string;
    auto __generate_base_header_code() const -> std::string;

    void __generate_code_for_object(const object &obj, std::string &cpp_code, std::string &header_code) const;
    auto __generate_cpp_code_for_object(const object &obj) const -> std::string;

    auto __generate_cpp_code_for_member_deserialization(const object &obj) const -> std::string;
    auto __generate_cpp_deserialize_by_type(const object_member &object_member) const -> std::string;

    auto __generate_cpp_code_for_member_serialization(const object &obj) const -> std::string;
    auto __generate_cpp_serialize_by_type(const object_member &object_member) const -> std::string;

    auto __generate_additional_include_code() const -> std::string;
    auto __generate_forward_declare_code(const std::vector<object> &objects) const -> std::string;

    auto __generate_header_code_for_object(const object &obj) const -> std::string;
    auto __generate_header_member_code_for_object(const object &obj) const -> std::string;

    auto __generate_move_construct_code_for_object(const object &obj) const -> std::string;
    auto __generate_move_assignment_code_for_object(const object &obj) const -> std::string;

    auto __convert_object_member_type_to_cpp_type(const object_member &object_member) const -> std::string;
    auto __convert_object_member_array_type_to_cpp_type(const object_member &object_member) const -> std::string;

    void __write_cpp_code_if_changed(const std::string &code) const;
    void __write_header_code_if_changed(const std::string &code) const;

    auto __file_contents_equal(const std::filesystem::path &path, const std::string &content) const -> bool;

    std::map<std::string, std::unique_ptr<code_generator>> code_generators_;
    subtype_code_generator subtype_code_generator_;
};

} // namespace aeon::serialization
