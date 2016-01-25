/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
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

class exception : public std::exception
{
public:
    exception(const std::string &message = "")
        : message_(message)
    {
    }

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
        name(const std::string &msg)                                                                                   \
            : base(msg)                                                                                                \
        {                                                                                                              \
        }                                                                                                              \
    }

} // namespace common
} // namespace aeon
