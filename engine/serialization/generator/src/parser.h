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

#include <object.h>
#include <json11.hpp>
#include <string>
#include <map>
#include <set>

namespace aeon
{
namespace serialization
{

class parser
{
public:
    parser() = default;
    ~parser() = default;

    auto parse_object_files() const -> std::vector<object>;

private:
    auto __parse_object_file(const std::string &path) const -> object;
    auto __read_file_to_string(const std::string &path) const -> std::string;

    void __parse_object_members(const std::map<std::string, json11::Json> &members,
                                std::map<std::string, object_member> &member_map) const;
    auto __parse_object_member(const std::string &member_name, const json11::Json &member) const -> object_member;

    void __move_base_classes_to_front(std::vector<object> &objects) const;
    auto __get_base_classes_from_objects(const std::vector<object> &objects) const -> std::set<std::string>;
    void __append_subclasses_to_baseclass_objects(std::vector<object> &objects) const;
    auto __get_subclasses_from_base_class(const std::string &base_class, const std::vector<object> &objects) const
        -> std::set<std::string>;
};

} // namespace serialization
} // namespace aeon
