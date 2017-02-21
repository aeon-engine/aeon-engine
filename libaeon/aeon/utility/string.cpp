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

#include <aeon/utility.h>

namespace aeon
{
namespace utility
{
namespace string
{

std::vector<std::string> &split(const std::string &str, char delim, std::vector<std::string> &elements)
{
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        elements.push_back(item);
    }

    return elements;
}

std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> elements;
    split(str, delim, elements);
    return elements;
}

void ltrim(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

void rtrim(std::string &str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
              str.end());
}

void trim(std::string &str)
{
    ltrim(str);
    rtrim(str);
}

std::string ltrimmed(const std::string &str)
{
    std::string trimstr = str;
    ltrim(trimstr);
    return trimstr;
}

std::string rtrimmed(const std::string &str)
{
    std::string trimstr = str;
    rtrim(trimstr);
    return trimstr;
}

std::string trimmed(const std::string &str)
{
    std::string trimstr = str;
    trim(trimstr);
    return trimstr;
}

std::string left(const std::string &str, int len)
{
    return str.substr(0, len);
}

std::string right(const std::string &str, int len)
{
    return str.substr(str.size() - len);
}

std::vector<std::string> args_to_vector(int argc, char *argv[])
{
    std::vector<std::string> vec;

    for (int i = 0; i < argc; ++i)
    {
        vec.push_back(argv[i]);
    }

    return vec;
}

void replace(std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
        return;

    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

} // namespace string
} // namespace utility
} // namespace aeon
