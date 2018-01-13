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

#include <string>
#include <map>
#include <set>

namespace aeon
{
namespace serialization
{

class object_member
{
    friend class parser;

public:
    object_member() = default;

    object_member(const std::string &name, const std::string &type, const bool is_array)
        : name_(name)
        , type_(type)
        , is_array_(is_array)
        , is_base_class_(false)
        , subclasses_()
    {
    }

    ~object_member() = default;

    auto &get_name() const
    {
        return name_;
    }

    auto &get_type() const
    {
        return type_;
    }

    auto is_array() const
    {
        return is_array_;
    }

    auto is_base_class() const
    {
        return is_base_class_;
    }

    auto get_subclasses() const
    {
        return subclasses_;
    }

private:
    std::string name_;
    std::string type_;
    bool is_array_;

    bool is_base_class_;
    std::set<std::string> subclasses_;
};

class object
{
    friend class parser;

public:
    object() = default;

    object(const std::string &name, const std::string &base_class, const std::map<std::string, object_member> &members)
        : name_(name)
        , base_class_(base_class)
        , is_base_class_(false)
        , members_(members)
    {
    }

    ~object() = default;

    auto &get_name() const
    {
        return name_;
    }

    auto get_base_class() const
    {
        return base_class_;
    }

    auto has_base_class() const
    {
        return !base_class_.empty();
    }

    auto &get_members()
    {
        return members_;
    }

    auto &get_members() const
    {
        return members_;
    }

    auto is_base_class() const
    {
        return is_base_class_;
    }

private:
    std::string name_;
    std::string base_class_;
    bool is_base_class_;
    std::map<std::string, object_member> members_;
};

} // namespace serialization
} // namespace aeon
