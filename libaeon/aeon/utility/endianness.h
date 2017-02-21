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
namespace endianness
{

template <typename T>
T swap16(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint16_t), "swap16 used on type of different size.");

    typedef typename std::conditional<std::is_integral<T>::value, T, std::uint16_t>::type swap_type;

    swap_type swap =
        (((*(static_cast<swap_type *>(&val)) & 0x00FF) << 8) | ((*(static_cast<swap_type *>(&val)) & 0xFF00) >> 8));

    return *(static_cast<T *>(&swap));
}

template <typename T>
T swap32(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint32_t), "swap32 used on type of different size.");

    typedef typename std::conditional<std::is_integral<T>::value, T, std::uint32_t>::type swap_type;

    swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x000000FF) << 24) |
                      ((*(static_cast<swap_type *>(&val)) & 0x0000FF00) << 8) |
                      ((*(static_cast<swap_type *>(&val)) & 0x00FF0000) >> 8) |
                      ((*(static_cast<swap_type *>(&val)) & 0xFF000000) >> 24));

    return *(static_cast<T *>(&swap));
}

template <typename T>
T swap64(T val)
{
    static_assert(sizeof(T) == sizeof(std::uint64_t), "swap64 used on type of different size.");

    typedef typename std::conditional<std::is_integral<T>::value, T, std::uint64_t>::type swap_type;

    swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x00000000000000FFULL) << 56) |
                      ((*(static_cast<swap_type *>(&val)) & 0x000000000000FF00ULL) << 40) |
                      ((*(static_cast<swap_type *>(&val)) & 0x0000000000FF0000ULL) << 24) |
                      ((*(static_cast<swap_type *>(&val)) & 0x00000000FF000000ULL) << 8) |
                      ((*(static_cast<swap_type *>(&val)) & 0x000000FF00000000ULL) >> 8) |
                      ((*(static_cast<swap_type *>(&val)) & 0x0000FF0000000000ULL) >> 24) |
                      ((*(static_cast<swap_type *>(&val)) & 0x00FF000000000000ULL) >> 40) |
                      ((*(static_cast<swap_type *>(&val)) & 0xFF00000000000000ULL) >> 56));

    return *(static_cast<T *>(&swap));
}

template <typename T>
T swap(T val)
{
    switch (sizeof(T))
    {
        case 1:
            return val;
        case 2:
        {
            typedef typename std::conditional<std::is_integral<T>::value, T, std::uint16_t>::type swap_type;

            swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x00FF) << 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0xFF00) >> 8));

            return *(static_cast<T *>(&swap));
        }
        case 4:
        {
            typedef typename std::conditional<std::is_integral<T>::value, T, std::uint32_t>::type swap_type;

            swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x000000FF) << 24) |
                              ((*(static_cast<swap_type *>(&val)) & 0x0000FF00) << 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0x00FF0000) >> 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0xFF000000) >> 24));

            return *(static_cast<T *>(&swap));
        }
        case 8:
        {
            typedef typename std::conditional<std::is_integral<T>::value, T, std::uint64_t>::type swap_type;

            swap_type swap = (((*(static_cast<swap_type *>(&val)) & 0x00000000000000FFULL) << 56) |
                              ((*(static_cast<swap_type *>(&val)) & 0x000000000000FF00ULL) << 40) |
                              ((*(static_cast<swap_type *>(&val)) & 0x0000000000FF0000ULL) << 24) |
                              ((*(static_cast<swap_type *>(&val)) & 0x00000000FF000000ULL) << 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0x000000FF00000000ULL) >> 8) |
                              ((*(static_cast<swap_type *>(&val)) & 0x0000FF0000000000ULL) >> 24) |
                              ((*(static_cast<swap_type *>(&val)) & 0x00FF000000000000ULL) >> 40) |
                              ((*(static_cast<swap_type *>(&val)) & 0xFF00000000000000ULL) >> 56));

            return *(static_cast<T *>(&swap));
        }
        default:
            throw std::runtime_error("Unsupported type for endianness swap.");
    }

    throw std::runtime_error("Unsupported type for endianness swap.");
}

} // namespace endianness
} // namespace utility
} // namespace aeon
