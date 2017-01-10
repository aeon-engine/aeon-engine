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
