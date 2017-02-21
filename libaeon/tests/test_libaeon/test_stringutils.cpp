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

#include <gtest/gtest.h>
#include <aeon/utility.h>

AEON_IGNORE_VS_WARNING(4189)

TEST(test_utility_string, test_utility_string_ltrim_none)
{
    std::string str = "value";
    aeon::utility::string::ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_ltrim_spaces)
{
    std::string str = "   value";
    aeon::utility::string::ltrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_ltrim_spaces_at_end)
{
    std::string str = "value  ";
    aeon::utility::string::ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_utility_string, test_utility_string_ltrim_spaces_at_end2)
{
    std::string str = "  value  ";
    aeon::utility::string::ltrim(str);
    EXPECT_EQ("value  ", str);
}

TEST(test_utility_string, test_utility_string_rtrim_spaces)
{
    std::string str = "value   ";
    aeon::utility::string::rtrim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_rtrim_spaces_at_beginning)
{
    std::string str = "   value";
    aeon::utility::string::rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_utility_string, test_utility_string_rtrim_spaces_at_beginning2)
{
    std::string str = "   value   ";
    aeon::utility::string::rtrim(str);
    EXPECT_EQ("   value", str);
}

TEST(test_utility_string, test_utility_string_trim)
{
    std::string str = "   value   ";
    aeon::utility::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_trim2)
{
    std::string str = "   value";
    aeon::utility::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_trim3)
{
    std::string str = "value  ";
    aeon::utility::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_trim4)
{
    std::string str = "value";
    aeon::utility::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_ltrimmed)
{
    EXPECT_EQ("value", aeon::utility::string::ltrimmed("   value"));
}

TEST(test_utility_string, test_utility_string_rtrimmed)
{
    EXPECT_EQ("value", aeon::utility::string::rtrimmed("value   "));
}

TEST(test_utility_string, test_utility_string_trimmed)
{
    EXPECT_EQ("value", aeon::utility::string::trimmed("   value   "));
}

TEST(test_utility_string, test_utility_string_trim_tabs)
{
    std::string str = "\t\tvalue\t\t";
    aeon::utility::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_trim_mixed)
{
    std::string str = " \t \t \t value \t \t \t ";
    aeon::utility::string::trim(str);
    EXPECT_EQ("value", str);
}

TEST(test_utility_string, test_utility_string_split_empty)
{
    std::string str = "";
    std::vector<std::string> result = aeon::utility::string::split(str, ' ');
    ASSERT_TRUE(result.empty());
}

TEST(test_utility_string, test_utility_string_split)
{
    std::string str = "one two three";
    std::vector<std::string> result = aeon::utility::string::split(str, ' ');
    ASSERT_EQ(3, result.size());
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("two", result[1]);
    EXPECT_EQ("three", result[2]);
}

TEST(test_utility_string, test_utility_string_split_double_space)
{
    std::string str = "one  two three";
    std::vector<std::string> result = aeon::utility::string::split(str, ' ');
    ASSERT_EQ(4, result.size());
    EXPECT_EQ("one", result[0]);
    EXPECT_EQ("", result[1]);
    EXPECT_EQ("two", result[2]);
    EXPECT_EQ("three", result[3]);
}

TEST(test_utility_string, test_utility_string_split_one_token)
{
    std::string str = "one";
    std::vector<std::string> result = aeon::utility::string::split(str, ' ');
    ASSERT_EQ(1, result.size());
    EXPECT_EQ("one", result[0]);
}

TEST(test_utility_string, test_utility_string_left)
{
    EXPECT_EQ("one", aeon::utility::string::left("one two three", 3));
}

TEST(test_utility_string, test_utility_string_right)
{
    EXPECT_EQ("ree", aeon::utility::string::right("one two three", 3));
}

TEST(test_utility_string, test_utility_string_args_to_vector_empty)
{
    std::vector<std::string> result = aeon::utility::string::args_to_vector(0, nullptr);
    EXPECT_TRUE(result.empty());
}
