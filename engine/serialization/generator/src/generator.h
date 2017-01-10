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

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <object.h>
#include <code_generator.h>
#include <subtype_code_generator.h>

namespace aeon
{
namespace serialization
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

    auto __convert_object_member_type_to_cpp_type(const object_member &object_member) const -> std::string;
    auto __convert_object_member_array_type_to_cpp_type(const object_member &object_member) const -> std::string;

    void __write_cpp_code_if_changed(const std::string &code) const;
    void __write_header_code_if_changed(const std::string &code) const;

    auto __file_contents_equal(const std::string &path, const std::string &content) const -> bool;

    std::map<std::string, std::unique_ptr<code_generator>> code_generators_;
    subtype_code_generator subtype_code_generator_;
};

} // namespace serialization
} // namespace aeon
