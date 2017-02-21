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

class simple_sink_backend : public base_backend
{
public:
    simple_sink_backend()
        : base_backend(log_level::message)
    {
    }

    simple_sink_backend(const log_level level)
        : base_backend(level)
    {
    }

    void add_sink(log_sink *sink)
    {
        sinks_.insert(sink);
    }

    void remove_all_sinks()
    {
        sinks_.clear();
    }

private:
    void log(const std::string &message, const std::string &module, const log_level level) override
    {
        for (auto sink : sinks_)
        {
            sink->log(message, module, level);
        }
    }

    std::set<log_sink *> sinks_;
};

} // namespace logger
} // namespace aeon
