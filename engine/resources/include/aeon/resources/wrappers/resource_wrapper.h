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

#include <aeon/resources/exceptions.h>
#include <aeon/resources/resource_type.h>
#include <aeon/resources/resource_encoding.h>
#include <aeon/resources/providers/resource_provider.h>
#include <aeon/common/logger.h>
#include <memory>
#include <string>

namespace aeon
{
namespace resources
{

// resource
DEFINE_EXCEPTION_OBJECT(resource_closed_exception, resource_exception,
                        "Resource is no longer available. It may have been unmounted.");

DEFINE_EXCEPTION_OBJECT(resource_type_exception, resource_exception,
                        "Unknown resource encoding or actual type does not match expected resource type.");

class resource_manager;
class resource_wrapper : public std::enable_shared_from_this<resource_wrapper>
{
public:
    virtual ~resource_wrapper() = default;

    auto get_type() const -> resource_type;

    auto get_encoding() const
    {
        return encoding_;
    }

    const auto &get_path() const
    {
        return path_;
    }

    void read_raw(std::vector<std::uint8_t> &buffer) const;

    void read_raw(std::string &buffer) const;

protected:
    explicit resource_wrapper(resource_manager &parent, const std::string &path,
                              const std::weak_ptr<resource_provider> &provider);

    auto &__get_parent() const
    {
        return parent_;
    }

    auto __get_provider() const
    {
        return provider_;
    }

private:
    aeon::logger::logger logger_;
    resource_manager &parent_;
    std::string path_;
    std::weak_ptr<resource_provider> provider_;
    resource_encoding encoding_;
};

} // namespace resources
} // namespace aeon
