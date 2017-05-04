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

#include <aeon/resources/resource_encoding.h>
#include <ostream>
#include <string>

namespace aeon
{
namespace resources
{

enum class resource_type
{
    data,
    group
};

class resource_info
{
public:
    explicit resource_info(const std::string &name_, const resource_type type_, const resource_encoding &encoding)
        : name_(name_)
        , type_(type_)
        , encoding_(encoding)
    {
    }

    auto get_name() const;
    auto get_type() const;
    auto get_encoding() const;

    std::string name_;
    resource_type type_;
    resource_encoding encoding_;
};

inline auto resource_info::get_name() const
{
    return name_;
}

inline auto resource_info::get_type() const
{
    return type_;
}

inline auto resource_info::get_encoding() const
{
    return encoding_;
}

inline auto &operator<<(std::ostream &os, const resource_info &info)
{
    auto type_string = (info.get_type() == resource_type::data) ? "Data" : "Group";
    return os << "[resource_encoding](Name: " << info.get_name() << " Type: " << type_string
              << " Encoding: " << info.get_encoding().get_name() << ")";
}

} // namespace resources
} // namespace aeon
