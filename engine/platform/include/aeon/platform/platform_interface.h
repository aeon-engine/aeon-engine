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

#include <aeon/platform/platform_filesystem_interface.h>
#include <aeon/common/exception.h>
#include <aeon/utility.h>
#include <memory>

namespace aeon
{
namespace platform
{

class platform_interface : utility::noncopyable
{
public:
    explicit platform_interface(std::unique_ptr<platform_filesystem_interface> filesystem_interface)
        : filesystem_interface_(std::move(filesystem_interface))
    {
    }

    virtual ~platform_interface() = default;

    /*!
     * Get the subsystem for filesystem interaction for this platform.
     */
    auto &get_filesystem_interface() const
    {
        platform_filesystem_interface *filesystem_interface = filesystem_interface_.get();
        return *filesystem_interface;
    }

protected:
    std::unique_ptr<platform_filesystem_interface> filesystem_interface_;
};

} // namespace platform
} // namespace aeon
