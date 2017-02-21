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

class stream_sink : public log_sink
{
public:
    explicit stream_sink(streams::stream &stream)
        : stream_(stream)
    {
    }

    virtual ~stream_sink() = default;

private:
    void log(const std::string &message, const std::string &module, log_level level) override
    {
        streams::stream_writer writer(stream_);

        stream_.write(reinterpret_cast<const std::uint8_t *>("["), 1);

        writer << module;

        stream_.write(reinterpret_cast<const std::uint8_t *>("] ["), 3);

        std::string log_level_string = log_level_str[static_cast<int>(level)];
        writer << log_level_string;

        stream_.write(reinterpret_cast<const std::uint8_t *>("]: "), 3);

        writer.write_line(message);
    }

    streams::stream &stream_;
};

} // namespace logger
} // namespace aeon
