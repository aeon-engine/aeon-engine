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
#include <set>

#include <code_generators/code_generator_color.h>
#include <code_generators/code_generator_float.h>
#include <code_generators/code_generator_int.h>
#include <code_generators/code_generator_kvstring.h>
#include <code_generators/code_generator_quaternion.h>
#include <code_generators/code_generator_string.h>
#include <code_generators/code_generator_vec3.h>

#define register_code_generator(type)                                                                                  \
    {                                                                                                                  \
        auto generator = std::make_unique<type>();                                                                     \
        auto generator_name = generator->get_type_name();                                                              \
        code_generators_[generator_name] = std::move(generator);                                                       \
    }

namespace aeon
{
namespace serialization
{

generator::generator()
{
    register_code_generator(code_generator_color);
    register_code_generator(code_generator_float);
    register_code_generator(code_generator_int);
    register_code_generator(code_generator_kvstring);
    register_code_generator(code_generator_quaternion);
    register_code_generator(code_generator_string);
    register_code_generator(code_generator_vec3);
}

void generator::generate_code(const std::vector<object> &objects) const
{
    auto cpp_body_code = std::string();
    auto header_body_code = std::string();

    for (auto &object : objects)
    {
        auto append_cpp_body_code = std::string();
        auto append_header_body_code = std::string();
        __generate_code_for_object(object, append_cpp_body_code, append_header_body_code);

        cpp_body_code += append_cpp_body_code;
        header_body_code += append_header_body_code;
    }

    auto cpp_code = __generate_base_code();
    utility::string::replace(cpp_code, "%body%", cpp_body_code);
    __write_cpp_code_if_changed(cpp_code);

    auto header_code = __generate_base_header_code();
    utility::string::replace(header_code, "%additional_includes%", __generate_additional_include_code());
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
#include <json11.hpp>
#include <memory>

%additional_includes%

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
    %object_initializer_list%
{
    %deserialize_members_code%
}

auto %object_name%::get_typename() const -> std::string
{
    return "%object_name%";
}

auto %object_name%::to_json() const -> json11::Json
{
    %serialize_members_code%
}
)code";

    if (!obj.has_base_class())
        utility::string::replace(code, "%object_initializer_list%", "");
    else
        utility::string::replace(code, "%object_initializer_list%", ": " + obj.get_base_class() + "(json)");

    utility::string::replace(code, "%object_name%", obj.get_name());
    utility::string::replace(code, "%deserialize_members_code%", __generate_cpp_code_for_member_deserialization(obj));
    utility::string::replace(code, "%serialize_members_code%", __generate_cpp_code_for_member_serialization(obj));

    return code;
}

auto generator::__generate_cpp_code_for_member_deserialization(const object &obj) const -> std::string
{
    auto member_deserialization_code = std::string();

    for (const auto &object_member : obj.get_members())
    {
        member_deserialization_code += __generate_cpp_deserialize_by_type(object_member.second);
    }

    return member_deserialization_code;
}

auto generator::__generate_cpp_deserialize_by_type(const object_member &object_member) const -> std::string
{
    auto result = code_generators_.find(object_member.get_type());

    if (result == code_generators_.end())
    {
        if (object_member.is_array())
        {
            if (object_member.is_base_class())
                return subtype_code_generator_.generate_cpp_deserialize_baseclass_array(object_member);

            return subtype_code_generator_.generate_cpp_deserialize_array(object_member);
        }

        return subtype_code_generator_.generate_cpp_deserialize(object_member);
    }

    if (object_member.is_array())
        return result->second->generate_array_deserialization_code(object_member);

    return result->second->generate_deserialization_code(object_member);
}

auto generator::__generate_cpp_code_for_member_serialization(const object &obj) const -> std::string
{
    std::string code = R"code(
%pre_serialize_code%
%serialize_code%
    return json_obj;
)code";

    if (obj.has_base_class())
    {
        std::string base_class_code = R"code(
    json11::Json::object json_obj = %base_class_name%::to_json().object_items();
)code";

        utility::string::replace(base_class_code, "%base_class_name%", obj.get_base_class());
        utility::string::replace(code, "%pre_serialize_code%", base_class_code);
    }
    else
    {
        utility::string::replace(code, "%pre_serialize_code%", "json11::Json::object json_obj;");
    }

    auto serialize_code = std::string();
    for (auto &member : obj.get_members())
    {
        serialize_code += __generate_cpp_serialize_by_type(member.second);
    }

    utility::string::replace(code, "%serialize_code%", serialize_code);

    return code;
}

auto generator::__generate_cpp_serialize_by_type(const object_member &object_member) const -> std::string
{
    auto result = code_generators_.find(object_member.get_type());

    if (result == code_generators_.end())
    {
        if (object_member.is_array())
        {
            if (object_member.is_base_class())
                return subtype_code_generator_.generate_cpp_serialize_baseclass_array(object_member);

            return subtype_code_generator_.generate_cpp_serialize_array(object_member);
        }

        return subtype_code_generator_.generate_cpp_serialize(object_member);
    }

    if (object_member.is_array())
        return result->second->generate_array_serialization_code(object_member);

    return result->second->generate_serialization_code(object_member);
}

auto generator::__generate_additional_include_code() const -> std::string
{
    std::set<std::string> includes;

    for (auto &code_gen : code_generators_)
    {
        auto required_includes = code_gen.second->generate_required_header_includes();
        includes.insert(required_includes.begin(), required_includes.end());
    }

    auto code = std::string();
    for (auto &required_include : includes)
    {
        code += "#include <" + required_include + ">\n";
    }

    return code;
}

auto generator::__generate_forward_declare_code(const std::vector<object> &objects) const -> std::string
{
    auto forward_declare_code = std::string();

    for (auto &object : objects)
    {
        auto type_name = object.get_name();
        forward_declare_code += "struct " + type_name + ";\n";
    }

    return forward_declare_code;
}

auto generator::__generate_header_code_for_object(const object &obj) const -> std::string
{
    auto member_code = __generate_header_member_code_for_object(obj);

    std::string code = R"code(
struct %object_name% %object_derives%
{
    %object_name%() = default;
    explicit %object_name%(const json11::Json &json);
    virtual ~%object_name%() = default;

    virtual auto get_typename() const -> std::string;

    virtual auto to_json() const -> json11::Json;

%object_members%
};
)code";

    if (!obj.has_base_class())
        utility::string::replace(code, "%object_derives%", "");
    else
        utility::string::replace(code, "%object_derives%", ": public " + obj.get_base_class());

    utility::string::replace(code, "%object_name%", obj.get_name());
    utility::string::replace(code, "%object_members%", member_code);

    return code;
}

auto generator::__generate_header_member_code_for_object(const object &obj) const -> std::string
{
    std::string code;
    for (const auto &member : obj.get_members())
    {
        auto object_member = member.second;

        auto cpp_type = std::string();
        if (!object_member.is_array())
            cpp_type = __convert_object_member_type_to_cpp_type(object_member);
        else
            cpp_type = __convert_object_member_array_type_to_cpp_type(object_member);

        code += "    " + cpp_type + " " + object_member.get_name() + ";\n";
    }
    return code;
}

auto generator::__convert_object_member_type_to_cpp_type(const object_member &object_member) const -> std::string
{
    auto result = code_generators_.find(object_member.get_type());

    if (result != code_generators_.end())
        return result->second->generate_cpp_type_name();

    return "std::unique_ptr<" + object_member.get_type() + ">";
}

auto generator::__convert_object_member_array_type_to_cpp_type(const object_member &object_member) const -> std::string
{
    auto result = code_generators_.find(object_member.get_type());

    if (result != code_generators_.end())
        return result->second->generate_cpp_array_type_name();

    return "std::vector<std::unique_ptr<" + object_member.get_type() + ">>";
}

void generator::__write_cpp_code_if_changed(const std::string &code) const
{
    auto file_path = AEON_ENGINE_SERIALIZATION_GENERATOR_DESTINATION "/objects_generated.cpp";

    if (!__file_contents_equal(file_path, code))
    {
        std::cout << "Writing generated cpp file." << std::endl;
        streams::file_stream cpp_file(file_path, streams::access_mode::write, streams::file_mode::binary);
        cpp_file.write_line(code);
    }
    else
    {
        std::cout << "Skipping write of generated cpp file (didn't change)." << std::endl;
    }
}

void generator::__write_header_code_if_changed(const std::string &code) const
{
    auto file_path = AEON_ENGINE_SERIALIZATION_GENERATOR_DESTINATION "/objects_generated.h";

    if (!__file_contents_equal(file_path, code))
    {
        std::cout << "Writing generated header file." << std::endl;
        streams::file_stream header_file(file_path, streams::access_mode::write, streams::file_mode::binary);
        header_file.write_line(code);
    }
    else
    {
        std::cout << "Skipping write of generated header file (didn't change)." << std::endl;
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
