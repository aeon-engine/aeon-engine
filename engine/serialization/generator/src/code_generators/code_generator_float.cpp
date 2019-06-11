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

#include <code_generators/code_generator_float.h>
#include <aeon/common/string.h>
#include <string>

namespace aeon::serialization
{

auto code_generator_float::get_type_name() const -> std::string
{
    return "float";
}

auto code_generator_float::generate_required_header_includes() const -> std::set<std::string>
{
    return {};
}

auto code_generator_float::generate_cpp_type_name() const -> std::string
{
    return "std::optional<float>";
}

auto code_generator_float::generate_cpp_array_type_name() const -> std::string
{
    return "std::vector<float>";
}

auto code_generator_float::generate_deserialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    if (json["%member_name%"].is_number())
        %member_name% = static_cast<float>(json["%member_name%"].number_value());
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_float::generate_array_deserialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array = json["%member_name%"];

    if (%member_name%_array.is_array())
    {
        for (auto &%member_name%_array_item : %member_name%_array.array_items())
        {
            %member_name%.push_back(static_cast<float>(
                %member_name%_array_item.number_value()));
        }
    }
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_float::generate_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    if (%member_name%)
    {
        json_obj["%member_name%"] = { %member_name%.value_or(0) };
    }
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto code_generator_float::generate_array_serialization_code(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    json_obj["%member_name%"] = json11::Json::array { %member_name% };
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}
} // namespace aeon::serialization
