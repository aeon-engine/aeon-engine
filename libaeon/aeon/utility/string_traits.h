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
namespace string
{

template <typename T>
struct convert
{
};

template <>
struct convert<std::string>
{
    static std::string to(const std::string &v)
    {
        return v;
    }

    static std::string from(const std::string &v)
    {
        return v;
    }
};

template <>
struct convert<int>
{
    static std::string to(int v)
    {
        return std::to_string(v);
    }

    static int from(const std::string &v)
    {
        return std::stoi(v);
    }
};

template <>
struct convert<float>
{
    static std::string to(float v)
    {
        return std::to_string(v);
    }

    static float from(const std::string &v)
    {
        return std::stof(v);
    }
};

template <>
struct convert<bool>
{
    static std::string to(bool v)
    {
        return v ? "1" : "0";
    }

    static bool from(const std::string &v)
    {
        return v == "1" || v == "true";
    }
};

} // namespace string
} // namespace utility
} // namespace aeon
