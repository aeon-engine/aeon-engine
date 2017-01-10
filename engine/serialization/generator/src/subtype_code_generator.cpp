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

#include <subtype_code_generator.h>
#include <aeon/utility.h>

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

    utility::string::replace(code, "%member_name%", object_member.get_name());
    utility::string::replace(code, "%subtype_name%", object_member.get_type());
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

    utility::string::replace(code, "%member_name%", object_member.get_name());
    utility::string::replace(code, "%subtype_name%", object_member.get_type());
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

    utility::string::replace(code, "%member_name%", object_member.get_name());

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
        utility::string::replace(append_factory_code, "%member_name%", object_member.get_name());
        utility::string::replace(append_factory_code, "%subclass_name%", subclass);
        factory_code += append_factory_code;
    }

    utility::string::replace(code, "%factory_code%", factory_code);

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

    utility::string::replace(code, "%member_name%", object_member.get_name());
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

    utility::string::replace(code, "%member_name%", object_member.get_name());
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

    utility::string::replace(code, "%member_name%", object_member.get_name());
    return code;
}

} // namespace serialization
} // namespace aeon
