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

#include <generator.h>
#include <generator_objects.h>
#include <code_generators/code_generator_color.h>
#include <code_generators/code_generator_float.h>
#include <code_generators/code_generator_int.h>
#include <code_generators/code_generator_kvstring.h>
#include <code_generators/code_generator_quaternion.h>
#include <code_generators/code_generator_string.h>
#include <code_generators/code_generator_vec3.h>
#include <code_generators/code_generator_rectangle.h>

#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/common/string.h>

#include <set>
#include <iostream>

#define register_code_generator(type)                                                                                  \
    {                                                                                                                  \
        auto generator = std::make_unique<type>();                                                                     \
        auto generator_name = generator->get_type_name();                                                              \
        code_generators_[generator_name] = std::move(generator);                                                       \
    }

namespace aeon::serialization
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
    register_code_generator(code_generator_rectangle);
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
    common::string::replace(cpp_code, "%body%", cpp_body_code);
    __write_cpp_code_if_changed(cpp_code);

    auto header_code = __generate_base_header_code();
    common::string::replace(header_code, "%additional_includes%", __generate_additional_include_code());
    common::string::replace(header_code, "%forward_declare%", __generate_forward_declare_code(objects));
    common::string::replace(header_code, "%body%", header_body_code);
    __write_header_code_if_changed(header_code);
}

auto generator::__generate_base_code() const -> std::string
{
    return R"code(
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

#pragma once

#include <json11.hpp>
#include <optional>
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

%object_name%::%object_name%(%object_name% &&other) noexcept
    : %move_construct_code%
{
}

%object_name% &%object_name%::operator=(%object_name% &&other) noexcept
{
    %move_assign_code%
    return *this;
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
        common::string::replace(code, "%object_initializer_list%", "");
    else
        common::string::replace(code, "%object_initializer_list%", ": " + obj.get_base_class() + "(json)");

    common::string::replace(code, "%object_name%", obj.get_name());
    common::string::replace(code, "%deserialize_members_code%", __generate_cpp_code_for_member_deserialization(obj));
    common::string::replace(code, "%serialize_members_code%", __generate_cpp_code_for_member_serialization(obj));

    common::string::replace(code, "%move_construct_code%", __generate_move_construct_code_for_object(obj));
    common::string::replace(code, "%move_assign_code%", __generate_move_assignment_code_for_object(obj));

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

        common::string::replace(base_class_code, "%base_class_name%", obj.get_base_class());
        common::string::replace(code, "%pre_serialize_code%", base_class_code);
    }
    else
    {
        common::string::replace(code, "%pre_serialize_code%", "json11::Json::object json_obj;");
    }

    auto serialize_code = std::string();
    for (auto &member : obj.get_members())
    {
        serialize_code += __generate_cpp_serialize_by_type(member.second);
    }

    common::string::replace(code, "%serialize_code%", serialize_code);

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

    %object_name%(%object_name% &&other) noexcept;
    %object_name% &operator=(%object_name% &&other) noexcept;

    virtual auto get_typename() const -> std::string;

    virtual auto to_json() const -> json11::Json;

%object_members%
};
)code";

    if (!obj.has_base_class())
        common::string::replace(code, "%object_derives%", "");
    else
        common::string::replace(code, "%object_derives%", ": public " + obj.get_base_class());

    common::string::replace(code, "%object_name%", obj.get_name());
    common::string::replace(code, "%object_members%", member_code);

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

auto generator::__generate_move_construct_code_for_object(const object &obj) const -> std::string
{
    auto code = std::string();

    for (auto &object : obj.get_members())
    {
        code += object.second.get_name() + "(std::move(other." + object.second.get_name() + "))\n,";
    }

    code.erase(code.size() - 1);

    return code;
}

auto generator::__generate_move_assignment_code_for_object(const object &obj) const -> std::string
{
    auto code = std::string();

    for (auto &object : obj.get_members())
    {
        code += object.second.get_name() + " = std::move(other." + object.second.get_name() + ");\n";
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
    std::filesystem::path file_path = AEON_ENGINE_SERIALIZATION_GENERATOR_DESTINATION "/objects_generated.cpp";

    if (!__file_contents_equal(file_path, code))
    {
        std::cout << "Writing generated cpp file." << std::endl;
        streams::file_sink_device cpp_file{file_path};
        streams::stream_writer writer{cpp_file};
        writer << code;
    }
    else
    {
        std::cout << "Skipping write of generated cpp file (didn't change)." << std::endl;
    }
}

void generator::__write_header_code_if_changed(const std::string &code) const
{
    std::filesystem::path file_path = AEON_ENGINE_SERIALIZATION_GENERATOR_DESTINATION "/objects_generated.h";

    if (!__file_contents_equal(file_path, code))
    {
        std::cout << "Writing generated header file." << std::endl;
        streams::file_sink_device header_file{file_path};
        streams::stream_writer writer{header_file};
        writer << code;
    }
    else
    {
        std::cout << "Skipping write of generated header file (didn't change)." << std::endl;
    }
}

auto generator::__file_contents_equal(const std::filesystem::path &path, const std::string &content) const -> bool
{
    if (!std::filesystem::exists(path))
        return false;

    streams::file_source_device file_stream{path};
    streams::stream_reader reader{file_stream};
    std::string file_content;
    reader.read_to_string(file_content);

    return file_content == content;
}
} // namespace aeon::serialization
