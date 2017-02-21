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

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Appends tokens to the given elements vector and returns it.
 */
std::vector<std::string> &split(const std::string &str, char delim, std::vector<std::string> &elements);

/*!
 * Split/tokenize a string into a vector of strings based on a delimiter.
 * Returns a vector of split elements.
 */
std::vector<std::string> split(const std::string &str, char delim);

/*!
 * Trim from the start of a string
 */
void ltrim(std::string &str);

/*!
 * Trim from the ending of a string
 */
void rtrim(std::string &str);

/*!
 * Trim a string at the start and end.
 */
void trim(std::string &str);

/*!
 * Trim from the start of a string
 */
std::string ltrimmed(const std::string &str);

/*!
 * Trim from the ending of a string
 */
std::string rtrimmed(const std::string &str);

/*!
 * Trim a string at the start and end.
 */
std::string trimmed(const std::string &str);

/*!
 * Get len characters from the left of the string.
 */
std::string left(const std::string &str, int len);

/*!
 * Get len characters from the right of the string.
 */
std::string right(const std::string &str, int len);

/*!
 * Convert standard argc and argv arguments into a vector of strings.
 */
std::vector<std::string> args_to_vector(int argc, char *argv[]);

/*!
 * Replace all occurances of a string with another string.
 */
void replace(std::string &str, const std::string &from, const std::string &to);

} // namespace string
} // namespace utility
} // namespace aeon
