/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

#include <map>
#include <string>
#include <object.h>

namespace aeon
{
namespace serialization
{

class generator
{
public:
    generator() = default;
    ~generator() = default;

    void generate_code(const std::map<std::string, object> &objects) const;

private:
    auto __generate_base_code() const -> std::string;
    auto __generate_base_header_code() const -> std::string;

    void __generate_code_for_object(const object &obj, std::string &cpp_code, std::string &header_code) const;
    auto __generate_cpp_code_for_object(const object &obj) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization(const object &obj) const -> std::string;

    auto __generate_cpp_code_for_member_deserialization_by_type(const std::string &member_type,
                                                                const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_int(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_float(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_string(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_color(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_subtype(const std::string &name,
                                                                const std::string &subtype) const -> std::string;

    auto __generate_cpp_code_for_member_deserialization_by_array_type(const std::string &member_type,
                                                                      const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_int_array(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_float_array(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_string_array(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_color_array(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_kvstring_array(const std::string &name) const -> std::string;
    auto __generate_cpp_code_for_member_deserialization_subtype_array(const std::string &name,
                                                                      const std::string &subtype) const -> std::string;

    auto __generate_forward_declare_code(const std::map<std::string, object> &objects) const -> std::string;

    auto __generate_header_code_for_object(const object &obj) const -> std::string;
    auto __generate_header_member_code_for_object(const object &obj) const -> std::string;

    auto __convert_object_member_type_to_cpp_type(const std::string &member_type) const -> std::string;
    auto __convert_object_member_array_type_to_cpp_type(const std::string &member_type) const -> std::string;

    void __write_cpp_code_if_changed(const std::string &code) const;
    void __write_header_code_if_changed(const std::string &code) const;

    auto __file_contents_equal(const std::string &path, const std::string &content) const -> bool;
};

} // namespace serialization
} // namespace aeon
