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
namespace webserver
{

enum class status_code
{
    ok = 200,
    not_found = 404,
    internal_server_error = 500,
};

class http_protocol_handler : public sockets::line_protocol_handler
{
    enum class http_state
    {
        method,
        headers,
        reply
    };

public:
    explicit http_protocol_handler(asio::ip::tcp::socket socket);
    void on_line(const std::string &line) override;

    void respond(const std::string &content_type, const std::string &data, status_code code = status_code::ok);
    void respond(const std::string &content_type, streams::stream_ptr data, status_code code = status_code::ok);

    void respond_default(status_code code);

    virtual void on_http_request(http_request &request) = 0;

private:
    const char *__http_status_to_string(status_code code) const;

    http_state state_;
    http_request request_;
};

} // namespace webserver
} // namespace aeon
