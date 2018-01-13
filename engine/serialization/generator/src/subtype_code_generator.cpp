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

#include <subtype_code_generator.h>
#include <aeon/common/string.h>
#include <cassert>

namespace aeon
{
namespace serialization
{

auto subtype_code_generator::generate_cpp_deserialize(const object_member &object_member) const -> std::string
{
    assert(!object_member.is_base_class());
    assert(!object_member.is_array());

    std::string code = R"code(

    if (json["%member_name%"].is_object())
        %member_name% = std::make_unique<%subtype_name%>(json["%member_name%"]);
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    common::string::replace(code, "%subtype_name%", object_member.get_type());
    return code;
}

auto subtype_code_generator::generate_cpp_deserialize_array(const object_member &object_member) const -> std::string
{
    assert(!object_member.is_base_class());
    assert(object_member.is_array());

    std::string code = R"code(
    auto %member_name%_array = json["%member_name%"];

    if (%member_name%_array.is_array())
    {
        for (auto &%member_name%_array_item : %member_name%_array.array_items())
        {
            %member_name%.push_back(std::make_unique<%subtype_name%>(%member_name%_array_item));
        }
    }
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    common::string::replace(code, "%subtype_name%", object_member.get_type());
    return code;
}

auto subtype_code_generator::generate_cpp_deserialize_baseclass_array(const object_member &object_member) const
    -> std::string
{
    assert(object_member.is_base_class());
    assert(object_member.is_array());

    std::string code = R"code(
    auto %member_name%_array = json["%member_name%"];
    if (%member_name%_array.is_array())
    {
        for (auto &%member_name%_array_item : %member_name%_array.array_items())
        {
            auto %member_name%_items = %member_name%_array_item.object_items();
            auto %member_name%_subclass_typename = %member_name%_items["type"];
            auto %member_name%_subclass_data = %member_name%_items["data"];

%factory_code%
        }
    }
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());

    std::string code2 = R"code(
            if (%member_name%_subclass_typename == "%subclass_name%")
            {
                objects.push_back(std::make_unique<%subclass_name%>(%member_name%_subclass_data));
                continue;
            }
)code";

    auto factory_code = std::string();
    for (auto &subclass : object_member.get_subclasses())
    {
        auto append_factory_code = code2;
        common::string::replace(append_factory_code, "%member_name%", object_member.get_name());
        common::string::replace(append_factory_code, "%subclass_name%", subclass);
        factory_code += append_factory_code;
    }

    common::string::replace(code, "%factory_code%", factory_code);

    return code;
}

auto subtype_code_generator::generate_cpp_serialize(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    if (%member_name%)
    {
        json_obj["%member_name%"] = { *%member_name% };
    }
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto subtype_code_generator::generate_cpp_serialize_array(const object_member &object_member) const -> std::string
{
    std::string code = R"code(
    json11::Json::array %member_name%_item_array;
    for (auto &%member_name%_item : %member_name%)
    {
        if (%member_name%_item)
        {
            %member_name%_item_array.push_back({ *%member_name%_item });
        }
    }

    json_obj["%member_name%"] = %member_name%_item_array;
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

auto subtype_code_generator::generate_cpp_serialize_baseclass_array(const object_member &object_member) const
    -> std::string
{
    std::string code = R"code(
    json11::Json::array %member_name%_item_array;
    for (auto &%member_name%_item : %member_name%)
    {
        if (%member_name%_item)
        {
            json11::Json::object %member_name%_item_obj;
            %member_name%_item_obj["type"] = { %member_name%_item->get_typename() };
            %member_name%_item_obj["data"] = { *%member_name%_item };
            %member_name%_item_array.push_back(%member_name%_item_obj);
        }
    }

    json_obj["%member_name%"] = %member_name%_item_array;
)code";

    common::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

} // namespace serialization
} // namespace aeon
