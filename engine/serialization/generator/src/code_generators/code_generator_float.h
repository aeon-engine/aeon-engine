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

#include <code_generator.h>

namespace aeon
{
namespace serialization
{

class code_generator_float : public code_generator
{
public:
    code_generator_float() = default;
    ~code_generator_float() = default;

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
