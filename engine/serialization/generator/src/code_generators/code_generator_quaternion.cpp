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

#include <code_generators/code_generator_quaternion.h>
#include <aeon/utility.h>
#include <string>
#include <stdexcept>

namespace aeon
{
namespace serialization
{

auto code_generator_quaternion::get_type_name() const -> std::string
{
    return "quaternion";
}

auto code_generator_quaternion::generate_required_header_includes() const -> std::set<std::string>
{
    return {"glm/gtc/quaternion.hpp"};
}

auto code_generator_quaternion::generate_cpp_type_name() const -> std::string
{
    return "aeon::utility::optional<glm::quat>";
}

auto code_generator_quaternion::generate_cpp_array_type_name() const -> std::string
{
    throw std::runtime_error("A quaternion can not be used as array.");
}

auto code_generator_quaternion::generate_deserialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array_items = json["%member_name%"].array_items();

    if (!%member_name%_array_items.empty())
    {
        %member_name% = glm::quat(
            static_cast<float>(%member_name%_array_items[0].number_value()),
            static_cast<float>(%member_name%_array_items[1].number_value()),
            static_cast<float>(%member_name%_array_items[2].number_value()),
            static_cast<float>(%member_name%_array_items[3].number_value()));
    }
)code";

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_quaternion::generate_array_deserialization_code(const object_member &) const -> std::string
{
    throw std::runtime_error("A quaternion can not be used as array.");
}

auto code_generator_quaternion::generate_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    if (%member_name%.has_value())
    {
        auto %member_name%_value = %member_name%.get_value();
        json_obj["%member_name%"] = json11::Json::array { %member_name%_value.x, %member_name%_value.y, %member_name%_value.z, %member_name%_value.w };
    }
)code";
    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_quaternion::generate_array_serialization_code(const object_member &) const -> std::string
{
    throw std::runtime_error("A quaternion can not be used as array.");
}

} // namespace serialization
} // namespace aeon
