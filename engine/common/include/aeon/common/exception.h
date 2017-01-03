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
