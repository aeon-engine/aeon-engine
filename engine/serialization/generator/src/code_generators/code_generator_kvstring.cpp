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

#include <code_generators/code_generator_kvstring.h>
#include <aeon/common/string.h>
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

    common::string::replace(code, "%member_name%", object_member.get_name());
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

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

} // namespace serialization
} // namespace aeon
