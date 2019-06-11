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

#include <code_generators/code_generator_quaternion.h>
#include <aeon/common/string.h>
#include <string>
#include <stdexcept>

namespace aeon::serialization
{

auto code_generator_quaternion::get_type_name() const -> std::string
{
    return "quaternion";
}

auto code_generator_quaternion::generate_required_header_includes() const -> std::set<std::string>
{
    return {"aeon/math/quaternion.h"};
}

auto code_generator_quaternion::generate_cpp_type_name() const -> std::string
{
    return "std::optional<aeon::math::quaternion>";
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
        %member_name% = aeon::math::quaternion{
            %member_name%_array_items[0].number_value(),
            %member_name%_array_items[1].number_value(),
            %member_name%_array_items[2].number_value(),
            %member_name%_array_items[3].number_value()};
    }
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_quaternion::generate_array_deserialization_code(const object_member &) const -> std::string
{
    throw std::runtime_error("A quaternion can not be used as array.");
}

auto code_generator_quaternion::generate_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    if (%member_name%)
    {
        auto %member_name%_value = %member_name%.value_or(aeon::math::quaternion{});
        json_obj["%member_name%"] = json11::Json::array { %member_name%_value.w, %member_name%_value.x, %member_name%_value.y, %member_name%_value.z };
    }
)code";
    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_quaternion::generate_array_serialization_code(const object_member &) const -> std::string
{
    throw std::runtime_error("A quaternion can not be used as array.");
}
} // namespace aeon::serialization
