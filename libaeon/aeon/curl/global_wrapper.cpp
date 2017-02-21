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

std::mutex global_wrapper::mutex_;
global_wrapper_ptr global_wrapper::wrapper_;

global_wrapper::global_wrapper()
    : initialized_(false)
{
    if (wrapper_)
        throw global_init_exception();

    CURLcode result = curl_global_init(CURL_GLOBAL_DEFAULT);

    if (result != 0)
        throw global_init_exception();

    initialized_ = true;
}

global_wrapper::~global_wrapper()
{
    if (initialized_)
        curl_global_cleanup();

    initialized_ = false;
}

aeon::curl::global_wrapper_ptr global_wrapper::get()
{
    std::lock_guard<std::mutex> g(mutex_);

    if (!wrapper_)
    {
        // Set to a temporary variable first, since the constructor checks for
        // the value of wrapper_ to prevent multiple instances.
        global_wrapper_ptr w = std::make_shared<global_wrapper>();
        wrapper_ = w;
    }

    return wrapper_;
}

} // namespace curl
} // namespace aeon
