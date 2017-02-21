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
namespace sockets
{

class line_protocol_handler : public tcp_server<line_protocol_handler>::protocol_handler
{
public:
    line_protocol_handler(asio::ip::tcp::socket socket)
        : tcp_server<line_protocol_handler>::protocol_handler(std::move(socket))
    {
    }

    virtual ~line_protocol_handler() = default;

    void on_data(std::uint8_t *data, std::size_t size) override
    {
        circular_buffer_.write(data, size);

        for (std::size_t i = 0; i < size; ++i)
        {
            if (data[i] == '\n')
            {
                streams::stream_reader<streams::circular_buffer_stream<AEON_TCP_SOCKET_MAX_BUFF_LEN>> reader(
                    circular_buffer_);
                on_line(reader.read_line());
            }
        }
    }

    virtual void on_line(const std::string &line) = 0;

private:
    streams::circular_buffer_stream<AEON_TCP_SOCKET_MAX_BUFF_LEN> circular_buffer_;
};

} // namespace sockets
} // namespace aeon
