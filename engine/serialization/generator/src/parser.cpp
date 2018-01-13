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

#include <parser.h>
#include <generator_objects.h>
#include <aeon/streams/file_stream.h>
#include <aeon/common/string.h>
#include <iostream>
#include <stdexcept>

namespace aeon
{
namespace serialization
{

auto parser::parse_object_files() const -> std::vector<object>
{
    auto object_paths = common::string::split(AEON_ENGINE_SERIALIZATION_GENERATOR_DATA, ';');

    auto objects = std::vector<object>();
    for (auto &object : object_paths)
    {
        auto obj = __parse_object_file(AEON_ENGINE_SERIALIZATION_GENERATOR_DATA_PATH "/" + object);

        std::cout << "Parsed: " << obj.get_name() << std::endl;
        objects.push_back(obj);
    }

    __move_base_classes_to_front(objects);
    __append_subclasses_to_baseclass_objects(objects);
    return objects;
}

auto parser::__parse_object_file(const std::string &path) const -> object
{
    auto file_data = __read_file_to_string(path);

    std::string error_string;
    auto json = json11::Json::parse(file_data, error_string);

    if (!error_string.empty())
        throw std::runtime_error(error_string);

    std::string object_name = json["name"].string_value();
    std::string base_class = json["base"].string_value();
    auto object_members = json["members"].object_items();

    std::map<std::string, object_member> members_map;
    __parse_object_members(object_members, members_map);

    return object(object_name, base_class, members_map);
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
        auto member_object = __parse_object_member(member_name, member.second);

        member_map[member_name] = member_object;
    }
}

auto parser::__parse_object_member(const std::string &member_name, const json11::Json &member) const -> object_member
{
    auto is_array = member.is_array();

    if (!is_array)
        return object_member(member_name, member.string_value(), is_array);

    auto array_value = member.array_items();

    if (array_value.size() != 1)
        throw std::runtime_error("When defining an array data type, this array can only contain 1 element.");

    return object_member(member_name, array_value.at(0).string_value(), is_array);
}

void parser::__move_base_classes_to_front(std::vector<object> &objects) const
{
    auto base_classes = __get_base_classes_from_objects(objects);

    for (auto itr = objects.begin(); itr != objects.end(); ++itr)
    {
        auto base_class_name = itr->get_name();
        // If the name of the object is a base class of something
        if (base_classes.find(base_class_name) != base_classes.end())
        {
            auto object = *itr;
            objects.erase(itr);
            object.is_base_class_ = true;
            itr = objects.insert(objects.begin(), object);

            // Also mark the members that this is a base class
            for (auto &obj : objects)
            {
                for (auto &member : obj.get_members())
                {
                    if (member.second.get_type() == base_class_name)
                        member.second.is_base_class_ = true;
                }
            }
        }
    }
}

auto parser::__get_base_classes_from_objects(const std::vector<object> &objects) const -> std::set<std::string>
{
    auto base_classes = std::set<std::string>();

    for (auto &obj : objects)
    {
        if (obj.has_base_class())
            base_classes.insert(obj.get_base_class());
    }

    return base_classes;
}

void parser::__append_subclasses_to_baseclass_objects(std::vector<object> &objects) const
{
    for (auto &obj : objects)
    {
        for (auto &member : obj.get_members())
        {
            auto &object_member = member.second;
            if (!object_member.is_base_class())
                continue;

            auto subclasses = __get_subclasses_from_base_class(object_member.get_type(), objects);
            object_member.subclasses_.insert(subclasses.begin(), subclasses.end());
        }
    }
}

auto parser::__get_subclasses_from_base_class(const std::string &base_class, const std::vector<object> &objects) const
    -> std::set<std::string>
{
    auto subclasses = std::set<std::string>();

    for (auto &obj : objects)
    {
        if (obj.get_base_class() == base_class)
            subclasses.insert(obj.get_name());
    }

    return subclasses;
}

} // namespace serialization
} // namespace aeon
