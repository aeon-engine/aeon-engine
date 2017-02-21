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
#include <aeon/streams.h>

TEST(test_circular_buffer_stream, test_circular_buffer_stream_read_write_basic)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t data1[] = {'A', 'B', 'C', 'D', 'E'};
    std::size_t result = buffer.write(data1, sizeof(data1));
    ASSERT_EQ(sizeof(data1), result);
    ASSERT_EQ(sizeof(data1), buffer.size());

    std::uint8_t data1_readback[sizeof(data1)] = {0};
    result = buffer.read(data1_readback, sizeof(data1_readback));
    ASSERT_EQ(sizeof(data1_readback), result);
    ASSERT_EQ(0, buffer.size());

    ASSERT_THAT(data1_readback, ::testing::ElementsAreArray(data1));

    std::uint8_t data2[] = {'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
    result = buffer.write(data2, sizeof(data2));
    ASSERT_EQ(sizeof(data2), result);
    ASSERT_EQ(sizeof(data2), buffer.size());

    std::uint8_t data2_readback[sizeof(data2)] = {0};
    result = buffer.read(data2_readback, sizeof(data2_readback));
    ASSERT_EQ(sizeof(data2_readback), result);
    ASSERT_EQ(0, buffer.size());

    ASSERT_THAT(data2_readback, ::testing::ElementsAreArray(data2));
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_read_write)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t magic_data[100];
    std::memset(magic_data, 'A', sizeof(magic_data));
    std::size_t result = buffer.write(magic_data, sizeof(magic_data));

    ASSERT_EQ(sizeof(magic_data), result);
    ASSERT_EQ(sizeof(magic_data), buffer.size());

    std::uint8_t readbackdata[sizeof(magic_data)];
    result = buffer.read(readbackdata, sizeof(readbackdata));

    ASSERT_EQ(sizeof(readbackdata), result);
    ASSERT_EQ(0, buffer.size());

    ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(magic_data));
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_write_too_big)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t magic_data[100];
    std::memset(magic_data, 'A', sizeof(magic_data));
    std::size_t result = buffer.write(magic_data, sizeof(magic_data));

    ASSERT_EQ(sizeof(magic_data), result);
    ASSERT_EQ(sizeof(magic_data), buffer.size());

    // Write data that is too big.
    std::uint8_t fake_data[101];
    std::memset(fake_data, 'B', sizeof(fake_data));
    result = buffer.write(fake_data, sizeof(fake_data));

    ASSERT_EQ(0, result);
    ASSERT_EQ(sizeof(magic_data), buffer.size());

    // Now read back the original data and see if it's untouched
    std::uint8_t readbackdata[sizeof(magic_data)];
    result = buffer.read(readbackdata, sizeof(readbackdata));

    ASSERT_EQ(sizeof(readbackdata), result);
    ASSERT_EQ(0, buffer.size());

    ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(magic_data));
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_read_too_big)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t data[101];
    std::size_t result = buffer.read(data, sizeof(data));

    // The read should have failed.
    ASSERT_EQ(0, result);
    ASSERT_EQ(0, buffer.size());
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_write_wrap_around)
{
    aeon::streams::circular_buffer_stream<100> buffer;

    std::uint8_t magic_data[50];
    std::memset(magic_data, 'A', sizeof(magic_data));

    std::size_t result = buffer.write(magic_data, sizeof(magic_data));

    ASSERT_EQ(sizeof(magic_data), result);
    ASSERT_EQ(sizeof(magic_data), buffer.size());

    // Now write some more data that would cause an exception
    std::uint8_t magic_data2[60];
    std::memset(magic_data2, 'B', sizeof(magic_data2));

    ASSERT_THROW(buffer.write(magic_data2, sizeof(magic_data2)), aeon::streams::circular_buffer_stream_exception);

    ASSERT_EQ(sizeof(magic_data), buffer.size());

    // Try to read back the 50 bytes we wrote earlier
    std::uint8_t readbackdata2[sizeof(magic_data)];
    result = buffer.read(readbackdata2, sizeof(readbackdata2));

    ASSERT_EQ(sizeof(readbackdata2), result);
    ASSERT_EQ(0, buffer.size());

    ASSERT_THAT(readbackdata2, ::testing::ElementsAreArray(magic_data));
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_read_write_multiple)
{
    aeon::streams::circular_buffer_stream<50> buffer;

    std::uint8_t base_character = 'A';

    for (int i = 0; i < 26; ++i)
    {
        std::uint8_t magic_data[28];
        std::memset(magic_data, base_character + i, sizeof(magic_data));
        std::size_t result = buffer.write(magic_data, sizeof(magic_data));

        ASSERT_EQ(sizeof(magic_data), result);
        ASSERT_EQ(sizeof(magic_data), buffer.size());

        std::uint8_t readbackdata[sizeof(magic_data)];
        result = buffer.read(readbackdata, sizeof(readbackdata));

        ASSERT_EQ(sizeof(readbackdata), result);
        ASSERT_EQ(0, buffer.size());

        ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(magic_data));
    }
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_overread)
{
    aeon::streams::circular_buffer_stream<10> buffer;
    ASSERT_EQ(0, buffer.size());

    std::uint8_t data[5];
    std::size_t result = buffer.read(data, sizeof(data));

    ASSERT_EQ(0, result);
    ASSERT_EQ(0, buffer.size());
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_default_size)
{
    aeon::streams::circular_buffer_stream<10> buffer;
    ASSERT_EQ(0, buffer.size());
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_maximum_size)
{
    aeon::streams::circular_buffer_stream<10> buffer;
    ASSERT_EQ(10, buffer.max_size());
}

/*
TEST(test_circular_buffer_stream, test_circular_buffer_stream_move_constructor)
{
    aeon::streams::circular_buffer_stream<10> buffer;

    std::uint8_t data[5] = {'A', 'B', 'C', 'D', 'E'};
    std::size_t result = buffer.write(data, sizeof(data));

    ASSERT_EQ(sizeof(data), result);
    ASSERT_EQ(sizeof(data), buffer.size());
    ASSERT_EQ(10, buffer.max_size());

    aeon::streams::circular_buffer_stream<10> buffer2 = std::move(buffer);

    ASSERT_EQ(sizeof(data), buffer2.size());
    ASSERT_EQ(10, buffer2.max_size());

    std::uint8_t readbackdata[sizeof(data)];
    result = buffer2.read(readbackdata, sizeof(readbackdata));

    ASSERT_EQ(sizeof(readbackdata), result);
    ASSERT_EQ(0, buffer2.size());

    ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(data));
}
*/

TEST(test_circular_buffer_stream, test_circular_buffer_stream_move_assignment)
{
    aeon::streams::circular_buffer_stream<10> buffer;

    std::uint8_t data[] = {'A', 'B', 'C', 'D', 'E'};
    std::size_t result = buffer.write(data, sizeof(data));

    ASSERT_EQ(sizeof(data), result);
    ASSERT_EQ(sizeof(data), buffer.size());
    ASSERT_EQ(10, buffer.max_size());

    aeon::streams::circular_buffer_stream<10> buffer2;
    ASSERT_EQ(0, buffer2.size());

    buffer2 = std::move(buffer);

    ASSERT_EQ(sizeof(data), buffer2.size());
    ASSERT_EQ(10, buffer2.max_size());

    std::uint8_t readbackdata[sizeof(data)];
    result = buffer2.read(readbackdata, sizeof(readbackdata));

    ASSERT_EQ(sizeof(readbackdata), result);
    ASSERT_EQ(0, buffer2.size());

    ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(data));
}

TEST(test_circular_buffer_stream, test_circular_buffer_stream_peek)
{
    aeon::streams::circular_buffer_stream<10> buffer;

    std::uint8_t data[] = {'A', 'B', 'C', 'D', 'E'};
    std::size_t result = buffer.write(data, sizeof(data));
    ASSERT_EQ(result, sizeof(data));

    std::uint8_t peek_value = 0;
    bool peek_result = buffer.peek(peek_value);
    ASSERT_TRUE(peek_result);
    ASSERT_EQ('A', peek_value);

    std::uint8_t dummy[3];
    result = buffer.read(dummy, sizeof(dummy));
    ASSERT_EQ(sizeof(dummy), result);

    peek_value = 0;
    peek_result = buffer.peek(peek_value);
    ASSERT_TRUE(peek_result);
    ASSERT_EQ('D', peek_value);

    result = buffer.write(data, sizeof(data));
    ASSERT_EQ(sizeof(data), result);

    peek_value = 0;
    peek_result = buffer.peek(peek_value);
    ASSERT_TRUE(peek_result);
    ASSERT_EQ('D', peek_value);
}
