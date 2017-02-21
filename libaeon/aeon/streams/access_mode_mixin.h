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

namespace aeon
{
namespace streams
{

/*!
 * The available access modes for the class that uses the access_mode_mixin.
 * This allows an implementation to for it's access permissions.
 *
 * This is implemented as an anonymous enum within a class, since enum classes
 * do not support bit flags at this moment.
 */
class access_mode
{
public:
    enum : int
    {
        none = 0x00,       /**< No access */
        read = 0x01,       /**< Read-Only */
        write = 0x02,      /**< Write-Only */
        read_write = 0x03, /**< Read-Write (Full access) */
        truncate = 0x04,   /**< Truncate */
    };
};

class access_mode_mixin
{
public:
    access_mode_mixin()
        : access_mode_(access_mode::none)
    {
    }

    access_mode_mixin(int access)
        : access_mode_(access)
    {
    }

    virtual ~access_mode_mixin() = default;

    access_mode_mixin(access_mode_mixin &&o) = default;
    access_mode_mixin &operator=(access_mode_mixin &&other) = default;

    virtual int get_access_mode() const
    {
        return access_mode_;
    }

    virtual bool is_readable() const
    {
        return (access_mode_ & access_mode::read) != 0;
    }

    virtual bool is_writable() const
    {
        return (access_mode_ & access_mode::write) != 0;
    }

    virtual bool is_truncated() const
    {
        return (access_mode_ & access_mode::truncate) != 0;
    }

protected:
    void set_access_mode(int access)
    {
        access_mode_ = access;
    }

    /*!
     * Bitflags representing the access mode of this stream.
     * May be read and or write.
     * \sa access_mode
     */
    int access_mode_;
};

} // namespace streams
} // namespace aeon
