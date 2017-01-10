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

#include <code_generators/code_generator_string.h>
#include <aeon/utility.h>
#include <string>

namespace aeon
{
namespace serialization
{

auto code_generator_string::get_type_name() const -> std::string
{
    return "string";
}

auto code_generator_string::generate_required_header_includes() const -> std::set<std::string>
{
    return {"string"};
}

auto code_generator_string::generate_cpp_type_name() const -> std::string
{
    return "aeon::utility::optional<std::string>";
}

auto code_generator_string::generate_cpp_array_type_name() const -> std::string
{
    return "std::vector<std::string>";
}

auto code_generator_string::generate_deserialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    %member_name% = json["%member_name%"].string_value();
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_string::generate_array_deserialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array = json["%member_name%"];

    if (%member_name%_array.is_array())
    {
        for (auto &%member_name%_array_item : %member_name%_array.array_items())
        {
            %member_name%.push_back(%member_name%_array_item.string_value());
        }
    }
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_string::generate_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    if (%member_name%.has_value())
    {
        json_obj["%member_name%"] = { %member_name%.get_value() };
    }
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_string::generate_array_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    json_obj["%member_name%"] = json11::Json::array { %member_name% };
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

} // namespace serialization
} // namespace aeon
