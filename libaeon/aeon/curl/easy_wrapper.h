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
namespace curl
{

typedef std::function<std::size_t(void *, std::size_t)> easy_wrapper_read_event;
class easy_wrapper : public utility::noncopyable
{
public:
    easy_wrapper();
    ~easy_wrapper();

    void get(const std::string &url, easy_wrapper_read_event on_read, long milliseconds = AEON_CURL_DEFAULT_TIMEOUT_MS);

private:
    static size_t static_read_event_(void *buffer, size_t size, size_t nmemb, easy_wrapper *wrapper);

    CURL *curl_;
    global_wrapper_ptr global_wrapper_;
    easy_wrapper_read_event read_event_;
};

typedef std::shared_ptr<easy_wrapper> easy_wrapper_ptr;

} // namespace curl
} // namespace aeon
