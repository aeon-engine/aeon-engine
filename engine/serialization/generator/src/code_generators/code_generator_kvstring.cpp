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

#include <code_generators/code_generator_kvstring.h>
#include <aeon/utility.h>
#include <string>
#include <stdexcept>

namespace aeon
{
namespace serialization
{

auto code_generator_kvstring::get_type_name() const -> std::string
{
    return "kvstring";
}

auto code_generator_kvstring::generate_required_header_includes() const -> std::set<std::string>
{
    return {"string", "map"};
}

auto code_generator_kvstring::generate_cpp_type_name() const -> std::string
{
    throw std::runtime_error("A kvstring (key value pair) can only be used as array.");
}

auto code_generator_kvstring::generate_cpp_array_type_name() const -> std::string
{
    return "std::map<std::string, std::string>";
}

auto code_generator_kvstring::generate_deserialization_code(const object_member &) const -> std::string
{
    throw std::runtime_error("A kvstring (key value pair) can only be used as array.");
}

auto code_generator_kvstring::generate_array_deserialization_code(const object_member &object_member) const
    -> std::string
{
    std::string code = R"code(
    auto %member_name%_object = json["%member_name%"];

    if (%member_name%_object.is_object())
    {
        auto %member_name%_object_map = %member_name%_object.object_items();
        for (auto &%member_name%_object_map_item : %member_name%_object_map)
        {
            %member_name%[%member_name%_object_map_item.first] = %member_name%_object_map_item.second.string_value();
        }
    }
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_kvstring::generate_serialization_code(const object_member &) const -> std::string
{
    throw std::runtime_error("A kvstring (key value pair) can only be used as array.");
}

auto code_generator_kvstring::generate_array_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    json11::Json::object %member_name%_item_obj;
    for (auto &%member_name%_item : %member_name%)
    {
        %member_name%_item_obj[%member_name%_item.first] = { %member_name%_item.second };
    }

    json_obj["%member_name%"] = json11::Json::array { %member_name%_item_obj };
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

} // namespace serialization
} // namespace aeon
