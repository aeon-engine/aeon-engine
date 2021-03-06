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

#include <aeon/io/io_filesystem_interface.h>
#include <memory>

namespace aeon::io
{

class io_interface
{
public:
    explicit io_interface(std::unique_ptr<io_filesystem_interface> filesystem_interface)
        : filesystem_interface_(std::move(filesystem_interface))
    {
    }

    virtual ~io_interface() = default;

    io_interface(const io_interface &) noexcept = delete;
    auto operator=(const io_interface &) noexcept -> io_interface & = delete;

    io_interface(io_interface &&) noexcept = default;
    auto operator=(io_interface &&) noexcept -> io_interface & = default;

    /*!
     * Get the subsystem for filesystem interaction.
     */
    auto &get_filesystem_interface() const
    {
        return *filesystem_interface_;
    }

protected:
    std::unique_ptr<io_filesystem_interface> filesystem_interface_;
};

} // namespace aeon::io
