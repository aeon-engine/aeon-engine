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
namespace utility
{
namespace container
{

template <typename T>
std::vector<T *> unique_ptr_to_raw_ptr(const std::vector<std::unique_ptr<T>> &c)
{
    std::vector<T *> c_ptr;
    c_ptr.reserve(c.size());

    for (auto &i : c)
    {
        c_ptr.push_back(i.get());
    }

    return std::move(c_ptr);
}

template <typename container_t, typename predicate_t>
void erase_if(container_t &items, const predicate_t &predicate)
{
    for (auto itr = items.begin(); itr != items.end();)
    {
        if (predicate(*itr))
            itr = items.erase(itr);
        else
            ++itr;
    }
}

} // namespace container
} // namespace utility
} // namespace aeon
