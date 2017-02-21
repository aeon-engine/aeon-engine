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

#include <exception>
#include <string>

namespace aeon
{
namespace common
{

/*!
 * Base class for exceptions within the aeon engine.
 */
class exception : public std::exception
{
public:
    /*!
     * Constructor
     * \param message A message describing the exception.
     */
    explicit exception(const std::string &message = "")
        : message_(message)
    {
    }

    /*!
     * Get a message describing the exception.
     * \return A message describing the exception.
     */
    const char *what() const noexcept override
    {
        return message_.c_str();
    }

private:
    const std::string message_;
};

#define DEFINE_EXCEPTION_OBJECT(name, base, message)                                                                   \
    class name : public base                                                                                           \
    {                                                                                                                  \
    public:                                                                                                            \
        name()                                                                                                         \
            : base(#message)                                                                                           \
        {                                                                                                              \
        }                                                                                                              \
                                                                                                                       \
        explicit name(const std::string &msg)                                                                          \
            : base(msg)                                                                                                \
        {                                                                                                              \
        }                                                                                                              \
    }

} // namespace common
} // namespace aeon
