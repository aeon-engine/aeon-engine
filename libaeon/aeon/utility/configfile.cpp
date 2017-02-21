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

#include <aeon/utility.h>

namespace aeon
{
namespace utility
{

bool configfile::has_entry(const std::string &key)
{
    auto itr = entries_.find(key);

    return (itr != entries_.end());
}

void configfile::load(streams::stream &stream)
{
    if (!stream.good())
        throw configfile_exception();

    entries_.clear();

    // Loop through all lines
    int linenumber = 0;
    std::string line;

    // A stream reader on a file stream is optimized for reading lines if the file was opened in text mode.
    // This will likely break on files opened as binary.
    if (stream.is<streams::file_stream>())
    {
        streams::stream_reader<streams::file_stream> reader(stream.as<streams::file_stream>());
        while (!stream.eof())
        {
            line = reader.read_line();
            ++linenumber;
            __read_line(line);
        }
    }
    else
    {
        streams::stream_reader<streams::stream> reader(stream);
        while (!stream.eof())
        {
            line = reader.read_line();
            ++linenumber;
            __read_line(line);
        }
    }
}

void configfile::save(streams::stream &stream)
{
    if (!stream.good())
        throw configfile_exception();

    streams::stream_writer writer(stream);

    for (auto itr : entries_)
    {
        std::string line = itr.first + "=" + itr.second;
        writer.write_line(line);
    }
}

void configfile::load(const std::string &path)
{
    try
    {
        streams::file_stream stream(path, streams::access_mode::read, streams::file_mode::text);
        load(stream);
    }
    catch (const streams::file_stream_exception &)
    {
        throw configfile_exception();
    }
}

void configfile::save(const std::string &path)
{
    streams::file_stream stream(path, streams::access_mode::read_write | streams::access_mode::truncate,
                                streams::file_mode::text);

    save(stream);
}

void configfile::load(std::vector<std::uint8_t> &&data)
{
    streams::memory_stream stream(std::move(data), streams::access_mode::read);
    load(stream);
}

void configfile::save(std::vector<std::uint8_t> &data)
{
    streams::memory_stream stream;
    save(stream);
    data = stream.read_to_vector();
}

void configfile::__read_line(const std::string &line)
{
    if (line.empty())
        return;

    // Ignore comments
    if (line[0] == '#')
        return;

    size_t pos = line.find_first_of('=');

    if (pos == std::string::npos || pos == 0)
        return;

    std::string key = line.substr(0, pos);
    std::string val = line.substr(pos + 1);

    entries_[key] = val;
}

} // namespace utility
} // namespace aeon
