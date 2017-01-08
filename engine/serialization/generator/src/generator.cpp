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

#include <generator.h>
#include <aeon/utility.h>
#include <aeon/streams.h>
#include <aeon/filesystem.h>
#include <generator_objects.h>

namespace aeon
{
namespace serialization
{

void generator::generate_code(const std::map<std::string, object> &objects) const
{
    auto cpp_body_code = std::string();
    auto header_body_code = std::string();

    for (auto &object : objects)
    {
        auto append_cpp_body_code = std::string();
        auto append_header_body_code = std::string();
        __generate_code_for_object(object.second, append_cpp_body_code, append_header_body_code);

        cpp_body_code += append_cpp_body_code;
        header_body_code += append_header_body_code;
    }

    auto cpp_code = __generate_base_code();
    utility::string::replace(cpp_code, "%body%", cpp_body_code);
    __write_cpp_code_if_changed(cpp_code);

    auto header_code = __generate_base_header_code();
    utility::string::replace(header_code, "%forward_declare%", __generate_forward_declare_code(objects));
    utility::string::replace(header_code, "%body%", header_body_code);
    __write_header_code_if_changed(header_code);
}

auto generator::__generate_base_code() const -> std::string
{
    return R"code(
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

#include <objects_generated.h>

namespace aeon
{
namespace serialization
{

%body%

} // namespace serialization
} // namespace aeon

)code";
}

auto generator::__generate_base_header_code() const -> std::string
{
    return R"code(
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

#include <aeon/utility.h>
#include <aeon/common/types/color.h>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <json11.hpp>
#include <memory>
#include <map>
#include <vector>

namespace aeon
{
namespace serialization
{

%forward_declare%

%body%

} // namespace serialization
} // namespace aeon

)code";
}

void generator::__generate_code_for_object(const object &obj, std::string &cpp_code, std::string &header_code) const
{
    cpp_code = __generate_cpp_code_for_object(obj);
    header_code = __generate_header_code_for_object(obj);
}

auto generator::__generate_cpp_code_for_object(const object &obj) const -> std::string
{
    std::string code = R"code(

%object_name%::%object_name%(const json11::Json &json)
{
    %deserialize_members_code%
}

)code";

    utility::string::replace(code, "%object_name%", obj.get_name());
    utility::string::replace(code, "%deserialize_members_code%", __generate_cpp_code_for_member_deserialization(obj));

    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization(const object &obj) const -> std::string
{
    auto member_deserialization_code = std::string();

    for (auto &object_member : obj.get_members())
    {
        auto member_name = object_member.first;
        auto member_type = object_member.second.type();
        auto member_is_array = object_member.second.is_array();

        if (!member_is_array)
            member_deserialization_code +=
                __generate_cpp_code_for_member_deserialization_by_type(member_type, member_name);
        else
            member_deserialization_code +=
                __generate_cpp_code_for_member_deserialization_by_array_type(member_type, member_name);
    }

    return member_deserialization_code;
}

auto generator::__generate_cpp_code_for_member_deserialization_by_type(const std::string &member_type,
                                                                       const std::string &name) const -> std::string
{
    if (member_type == "int")
        return __generate_cpp_code_for_member_deserialization_int(name);

    if (member_type == "float")
        return __generate_cpp_code_for_member_deserialization_float(name);

    if (member_type == "string")
        return __generate_cpp_code_for_member_deserialization_string(name);

    if (member_type == "color")
        return __generate_cpp_code_for_member_deserialization_color(name);

    if (member_type == "vec3")
        return __generate_cpp_code_for_member_deserialization_vec3(name);

    if (member_type == "quaternion")
        return __generate_cpp_code_for_member_deserialization_quaternion(name);

    return __generate_cpp_code_for_member_deserialization_subtype(name, member_type);
}

auto generator::__generate_cpp_code_for_member_deserialization_int(const std::string &name) const -> std::string
{
    std::string code = R"code(
    %member_name% = json["%member_name%"].int_value();
)code";

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_float(const std::string &name) const -> std::string
{
    std::string code = R"code(
    %member_name% = static_cast<float>(json["%member_name%"].number_value());
)code";

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_string(const std::string &name) const -> std::string
{
    std::string code = R"code(

    if (json["%member_name%"].is_string())
        %member_name% = json["%member_name%"].string_value();
)code";

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_color(const std::string &name) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array_items = json["%member_name%"].array_items();

    if (!%member_name%_array_items.empty())
    {
        %member_name% = aeon::common::types::color(
            static_cast<float>(%member_name%_array_items[0].number_value()),
            static_cast<float>(%member_name%_array_items[1].number_value()),
            static_cast<float>(%member_name%_array_items[2].number_value()),
            static_cast<float>(%member_name%_array_items[3].number_value()));
    }
)code";

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_vec3(const std::string &name) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array_items = json["%member_name%"].array_items();

    if (!%member_name%_array_items.empty())
    {
        %member_name% = glm::vec3(
            static_cast<float>(%member_name%_array_items[0].number_value()),
            static_cast<float>(%member_name%_array_items[1].number_value()),
            static_cast<float>(%member_name%_array_items[2].number_value()));
    }
)code";

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_quaternion(const std::string &name) const -> std::string
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

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_subtype(const std::string &name,
                                                                       const std::string &subtype) const -> std::string
{
    std::string code = R"code(

    if (json["%member_name%"].is_object())
        %member_name% = std::make_unique<%subtype_name%>(json["%member_name%"]);
)code";

    utility::string::replace(code, "%member_name%", name);
    utility::string::replace(code, "%subtype_name%", subtype);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_by_array_type(const std::string &member_type,
                                                                             const std::string &name) const
    -> std::string
{
    if (member_type == "int")
        return __generate_cpp_code_for_member_deserialization_int_array(name);

    if (member_type == "float")
        return __generate_cpp_code_for_member_deserialization_float_array(name);

    if (member_type == "string")
        return __generate_cpp_code_for_member_deserialization_string_array(name);

    if (member_type == "color")
        return __generate_cpp_code_for_member_deserialization_color_array(name);

    if (member_type == "kvstring")
        return __generate_cpp_code_for_member_deserialization_kvstring_array(name);

    return __generate_cpp_code_for_member_deserialization_subtype_array(name, member_type);
}

auto generator::__generate_cpp_code_for_member_deserialization_int_array(const std::string &name) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array = json["%member_name%"];

    if (%member_name%_array.is_array())
    {
        for (auto &%member_name%_array_item : %member_name%_array.array_items())
        {
            %member_name%.push_back(%member_name%_array_item.int_value());
        }
    }
)code";

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_float_array(const std::string &name) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array = json["%member_name%"];

    if (%member_name%_array.is_array())
    {
        for (auto &%member_name%_array_item : %member_name%_array.array_items())
        {
            %member_name%.push_back(static_cast<float>(%member_name%_array_item.number_value()));
        }
    }
)code";

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_string_array(const std::string &name) const
    -> std::string
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

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_color_array(const std::string &name) const -> std::string
{
    std::string code = R"code(
    auto %member_name%_array = json["%member_name%"];

    if (%member_name%_array.is_array())
    {
        for (auto &%member_name%_array_item : %member_name%_array.array_items())
        {
            auto %member_name%_array_color_items = %member_name%_array_item.array_items();
            if (!%member_name%_array_color_items.empty())
            {
                %member_name%.push_back(aeon::common::types::color(
                    static_cast<float>(%member_name%_array_color_items[0].number_value()),
                    static_cast<float>(%member_name%_array_color_items[1].number_value()),
                    static_cast<float>(%member_name%_array_color_items[2].number_value()),
                    static_cast<float>(%member_name%_array_color_items[3].number_value())));
            }
        }
    }
)code";

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_kvstring_array(const std::string &name) const
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

    utility::string::replace(code, "%member_name%", name);
    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization_subtype_array(const std::string &name,
                                                                             const std::string &subtype) const
    -> std::string
{
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

    utility::string::replace(code, "%member_name%", name);
    utility::string::replace(code, "%subtype_name%", subtype);
    return code;
}

auto generator::__generate_forward_declare_code(const std::map<std::string, object> &objects) const -> std::string
{
    auto forward_declare_code = std::string();

    for (auto &object : objects)
    {
        auto type_name = object.first;
        forward_declare_code += "struct " + type_name + ";\n";
    }

    return forward_declare_code;
}

auto generator::__generate_header_code_for_object(const object &obj) const -> std::string
{
    auto member_code = __generate_header_member_code_for_object(obj);

    std::string code = R"code(
struct %object_name%
{
    %object_name%() = default;
    explicit %object_name%(const json11::Json &json);
    ~%object_name%() = default;

%object_members%
};
)code";

    utility::string::replace(code, "%object_name%", obj.get_name());
    utility::string::replace(code, "%object_members%", member_code);

    return code;
}

auto generator::__generate_header_member_code_for_object(const object &obj) const -> std::string
{
    std::string code;
    for (const auto &member : obj.get_members())
    {
        auto member_name = member.first;
        auto member_type = member.second.type();
        auto member_is_array = member.second.is_array();

        auto cpp_type = std::string();
        if (!member_is_array)
            cpp_type = __convert_object_member_type_to_cpp_type(member_type);
        else
            cpp_type = __convert_object_member_array_type_to_cpp_type(member_type);

        code += "    " + cpp_type + " " + member_name + ";\n";
    }
    return code;
}

auto generator::__convert_object_member_type_to_cpp_type(const std::string &member_type) const -> std::string
{
    if (member_type == "int")
        return "aeon::utility::optional<int>";

    if (member_type == "float")
        return "aeon::utility::optional<float>";

    if (member_type == "string")
        return "aeon::utility::optional<std::string>";

    if (member_type == "color")
        return "aeon::utility::optional<aeon::common::types::color>";

    if (member_type == "vec3")
        return "glm::vec3";

    if (member_type == "quaternion")
        return "glm::quat";

    if (member_type == "kvstring")
        throw std::runtime_error("A kvstring (key value pair) can only be used as array.");

    return "std::unique_ptr<" + member_type + ">";
}

auto generator::__convert_object_member_array_type_to_cpp_type(const std::string &member_type) const -> std::string
{
    if (member_type == "int")
        return "std::vector<int>";

    if (member_type == "float")
        return "std::vector<float>";

    if (member_type == "string")
        return "std::vector<std::string>";

    if (member_type == "color")
        return "std::vector<aeon::common::types::color>";

    if (member_type == "kvstring")
        return "std::map<std::string, std::string>";

    if (member_type == "vec3")
        throw std::runtime_error("A vec3 can only be used outside of an array.");

    if (member_type == "quaternion")
        throw std::runtime_error("A quaternion can only be used outside of an array.");

    return "std::vector<std::unique_ptr<" + member_type + ">>";
}

void generator::__write_cpp_code_if_changed(const std::string &code) const
{
    auto file_path = AEON_ENGINE_SERIALIZATION_GENERATOR_DESTINATION "/objects_generated.cpp";

    if (!__file_contents_equal(file_path, code))
    {
        streams::file_stream cpp_file(file_path, streams::access_mode::write, streams::file_mode::binary);
        cpp_file.write_line(code);
    }
}

void generator::__write_header_code_if_changed(const std::string &code) const
{
    auto file_path = AEON_ENGINE_SERIALIZATION_GENERATOR_DESTINATION "/objects_generated.h";

    if (!__file_contents_equal(file_path, code))
    {
        streams::file_stream header_file(file_path, streams::access_mode::write, streams::file_mode::binary);
        header_file.write_line(code);
    }
}

auto generator::__file_contents_equal(const std::string &path, const std::string &content) const -> bool
{
    if (!filesystem::exists(path))
        return false;

    streams::file_stream file_stream(path);
    auto file_raw_data = file_stream.read_to_vector();
    auto file_content = std::string(file_raw_data.begin(), file_raw_data.end());

    return file_content == (content + "\n");
}

} // namespace serialization
} // namespace aeon
