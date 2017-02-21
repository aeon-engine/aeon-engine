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

#include <aeon/curl.h>

namespace aeon
{
namespace curl
{

easy_wrapper::easy_wrapper()
    : curl_(nullptr)
{
    global_wrapper_ = global_wrapper::get();

    curl_ = curl_easy_init();

    if (!curl_)
        throw easy_init_exception();

    if (curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, &easy_wrapper::static_read_event_) != CURLE_OK)
        throw easy_wrapper_exception();

    if (curl_easy_setopt(curl_, CURLOPT_WRITEDATA, this) != CURLE_OK)
        throw easy_wrapper_exception();
}

easy_wrapper::~easy_wrapper()
{
    if (curl_)
        curl_easy_cleanup(curl_);

    curl_ = nullptr;
    global_wrapper_ = nullptr;
}

void easy_wrapper::get(const std::string &url, easy_wrapper_read_event on_read,
                       long milliseconds /*= AEON_CURL_DEFAULT_TIMEOUT_MS*/)
{
    if (!curl_ || url.empty() || !on_read || milliseconds == 0)
        throw easy_wrapper_exception();

    if (curl_easy_setopt(curl_, CURLOPT_TIMEOUT_MS, milliseconds) != CURLE_OK)
        throw easy_wrapper_exception();

    if (curl_easy_setopt(curl_, CURLOPT_URL, url.c_str()) != CURLE_OK)
        throw easy_wrapper_exception();

    read_event_ = on_read;

    if (curl_easy_perform(curl_) != CURLE_OK)
        throw easy_wrapper_exception();
}

size_t easy_wrapper::static_read_event_(void *buffer, size_t size, size_t nmemb, easy_wrapper *wrapper)
{
    return wrapper->read_event_(buffer, size * nmemb);
}

} // namespace curl
} // namespace aeon
