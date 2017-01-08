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

namespace aeon
{
namespace serialization
{

class object_member
{
public:
    object_member() = default;

    object_member(const std::string &type, const bool is_array)
        : type_(type)
        , is_array_(is_array)
    {
    }

    ~object_member() = default;

    auto &type() const
    {
        return type_;
    }

    auto is_array() const
    {
        return is_array_;
    }

private:
    std::string type_;
    bool is_array_;
};

class object
{
public:
    object() = default;

    object(const std::string &name, const std::map<std::string, object_member> &members)
        : name_(name)
        , members_(members)
    {
    }

    ~object() = default;

    auto &get_name() const
    {
        return name_;
    }

    auto &get_members() const
    {
        return members_;
    }

private:
    std::string name_;
    std::map<std::string, object_member> members_;
};

} // namespace serialization
} // namespace aeon
