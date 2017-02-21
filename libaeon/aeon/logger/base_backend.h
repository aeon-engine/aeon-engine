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
namespace logger
{

class base_backend : public utility::noncopyable
{
    friend class logger_stream;

public:
    base_backend()
        : level_(log_level::message)
    {
    }

    base_backend(const log_level level)
        : level_(level)
    {
    }

    virtual ~base_backend() = default;

    void set_log_level(const log_level level)
    {
        level_ = level;
    }

    auto get_log_level() const -> log_level
    {
        return level_;
    }

    virtual void log(const std::string &message, const std::string &module, const log_level level) = 0;

private:
    void __handle_log(const std::string &message, const std::string &module, const log_level level)
    {
        if (level >= level_)
            log(message, module, level);
    }

    log_level level_;
};

} // namespace logger
} // namespace aeon
