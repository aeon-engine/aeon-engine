/*
 * Copyright (c) 2012-2017 Robin Degen
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
