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

namespace aeon::resources
{

class resource_encoding
{
public:
    resource_encoding(const std::string &name);
    ~resource_encoding() = default;

    auto get_name() const;

    auto operator==(const resource_encoding &other) const;
    auto operator!=(const resource_encoding &other) const;

    auto operator<(const resource_encoding &other) const;
    auto operator>(const resource_encoding &other) const;

private:
    std::string name_;
};

inline resource_encoding::resource_encoding(const std::string &name)
    : name_(name)
{
}

inline auto resource_encoding::get_name() const
{
    return name_;
}

inline auto resource_encoding::operator==(const resource_encoding &other) const
{
    return name_ == other.name_;
}

inline auto resource_encoding::operator!=(const resource_encoding &other) const
{
    return !(*this == other);
}

inline auto resource_encoding::operator<(const resource_encoding &other) const
{
    return name_ < other.name_;
}

inline auto resource_encoding::operator>(const resource_encoding &other) const
{
    return name_ > other.name_;
}

inline auto &operator<<(std::ostream &os, const resource_encoding &encoding)
{
    return os << encoding.get_name();
}

} // namespace aeon::resources
