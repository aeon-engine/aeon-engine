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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <aeon/midi.h>
#include <aeon/streams.h>

using namespace aeon;

class test_midi_file_reader : public midi::midi_file_reader
{
public:
    test_midi_file_reader() = default;
    virtual ~test_midi_file_reader() = default;

    std::uint32_t read_vtime(streams::memory_stream &stream)
    {
        return midi::midi_file_reader::read_vtime(stream);
    }
};

TEST(test_midi_file, test_read_vtime)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x00};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime2)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x40};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0x40, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime3)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x7f};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0x7f, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime4)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x81, 0x00};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0x80, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime5)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0xC0, 0x00};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0x2000, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime6)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0xff, 0x7f};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0x3fff, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime7)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x81, 0x80, 0x00};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0x4000, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime8)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0xff, 0xff, 0x7f};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0x1fffff, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime9)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0xff, 0xff, 0xff, 0x7f};
    streams::memory_stream mem_stream(std::move(data), streams::access_mode::read);

    ASSERT_EQ(0x0fffffff, reader.read_vtime(mem_stream));
}
