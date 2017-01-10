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
