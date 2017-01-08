#include "parser.h"

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

#include <parser.h>
#include <generator_objects.h>
#include <aeon/utility.h>
#include <aeon/streams.h>
#include <iostream>
#include <stdexcept>

namespace aeon
{
namespace serialization
{

auto parser::parse_object_files() const -> std::map<std::string, object>
{
    auto objects = utility::string::split(AEON_ENGINE_SERIALIZATION_GENERATOR_DATA, ';');

    auto object_map = std::map<std::string, object>();
    for (auto &object : objects)
    {
        auto obj = __parse_object_file(AEON_ENGINE_SERIALIZATION_GENERATOR_DATA_PATH "/" + object);
        object_map[obj.get_name()] = obj;
    }

    return object_map;
}

auto parser::__parse_object_file(const std::string &path) const -> object
{
    auto file_data = __read_file_to_string(path);

    std::string error_string;
    auto json = json11::Json::parse(file_data, error_string);

    if (!error_string.empty())
        throw std::runtime_error(error_string);

    std::string object_name = json["name"].string_value();
    auto object_members = json["members"].object_items();

    std::map<std::string, object_member> members_map;
    __parse_object_members(object_members, members_map);

    return object(object_name, members_map);
}

auto parser::__read_file_to_string(const std::string &path) const -> std::string
{
    streams::file_stream file_stream(path);
    auto file_raw_data = file_stream.read_to_vector();
    return std::string(file_raw_data.begin(), file_raw_data.end());
}

void parser::__parse_object_members(const std::map<std::string, json11::Json> &members,
                                    std::map<std::string, object_member> &member_map) const
{
    for (const auto &member : members)
    {
        std::string member_name = member.first;
        auto member_object = __parse_object_member(member.second);
        member_map[member_name] = member_object;
    }
}

auto parser::__parse_object_member(const json11::Json &member) const -> object_member
{
    std::string type_string = member["type"].string_value();
    bool is_array = member["array"].bool_value();
    return object_member(type_string, is_array);
}

} // namespace serialization
} // namespace aeon
