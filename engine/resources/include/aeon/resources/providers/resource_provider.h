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
#include <aeon/resources/exceptions.h>
#include <vector>
#include <string>
#include <memory>

namespace aeon
{
namespace resources
{

DEFINE_EXCEPTION_OBJECT(resource_provider_exception, resource_exception, "Generic Resource Provider exception.");

enum class resource_node_type
{
    file,
    directory
};

class resource_node
{
public:
    explicit resource_node(const std::string &name_, resource_node_type type_)
        : name(name_)
        , type(type_)
    {
    }

    std::string name;
    resource_node_type type;
};

class resource_manager;
class resource_provider
{
    friend class resource_manager;

public:
    resource_provider()
        : manager_(nullptr)
    {
    }

    virtual ~resource_provider() = default;

    virtual auto exists(const std::string &path) const -> bool = 0;

    virtual auto list(const std::string &path) const -> std::vector<resource_node> = 0;

    virtual void read(const std::string &path, std::vector<std::uint8_t> &buffer) = 0;

    virtual auto get_encoding(const std::string &path) const -> resource_encoding = 0;

protected:
    auto __get_resource_manager() const
    {
        return manager_;
    }

private:
    resource_manager *manager_;
};

} // namespace resources
} // namespace aeon
