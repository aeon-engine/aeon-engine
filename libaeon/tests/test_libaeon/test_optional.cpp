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
#include <aeon/platform.h>
#include <aeon/utility.h>

AEON_IGNORE_VS_WARNING(4189)

#define UNUSED(expr)                                                                                                   \
    do                                                                                                                 \
    {                                                                                                                  \
        (void)(expr);                                                                                                  \
    } while (0)

TEST(test_utility, test_utility_optional_create_int)
{
    aeon::utility::optional<int> test;
    ASSERT_FALSE(test.has_value());
}

TEST(test_utility, test_utility_optional_create_float)
{
    aeon::utility::optional<float> test;
    ASSERT_FALSE(test.has_value());
}

TEST(test_utility, test_utility_optional_create_string)
{
    aeon::utility::optional<std::string> test;
    ASSERT_FALSE(test.has_value());
}

TEST(test_utility, test_utility_optional_create_int_with_value)
{
    aeon::utility::optional<int> test = 1337;
    ASSERT_TRUE(test.has_value());

    int testvalue = test;
    ASSERT_EQ(1337, testvalue);
}

TEST(test_utility, test_utility_optional_create_float_with_value)
{
    aeon::utility::optional<float> test = 1337.0f;
    ASSERT_TRUE(test.has_value());
}

TEST(test_utility, test_utility_optional_create_string_with_value)
{
    aeon::utility::optional<std::string> test = std::string("1337!");
    ASSERT_TRUE(test.has_value());
}

TEST(test_utility, test_utility_optional_change_int_value)
{
    aeon::utility::optional<int> test = 1337;
    ASSERT_TRUE(test.has_value());

    test = 1338;
    ASSERT_TRUE(test.has_value());
}

TEST(test_utility, test_utility_optional_change_int_value2)
{
    aeon::utility::optional<int> test;
    ASSERT_FALSE(test.has_value());

    test = 1338;
    ASSERT_TRUE(test.has_value());
}

TEST(test_utility, test_utility_optional_change_float_value)
{
    aeon::utility::optional<float> test = 1337.0f;
    ASSERT_TRUE(test.has_value());

    test = 1338.1f;
    ASSERT_TRUE(test.has_value());
}

TEST(test_utility, test_utility_optional_change_float_value2)
{
    aeon::utility::optional<float> test;
    ASSERT_FALSE(test.has_value());

    test = 1338.1f;
    ASSERT_TRUE(test.has_value());
}

TEST(test_utility, test_utility_optional_change_string_value)
{
    aeon::utility::optional<std::string> test = std::string("1337!");
    ASSERT_TRUE(test.has_value());

    test = std::string("42?");
    ASSERT_TRUE(test.has_value());
}

TEST(test_utility, test_utility_optional_change_string_value2)
{
    aeon::utility::optional<std::string> test;
    ASSERT_FALSE(test.has_value());

    test = std::string("42?");
    ASSERT_TRUE(test.has_value());
}

TEST(test_utility, test_utility_optional_reset_int)
{
    aeon::utility::optional<int> test = 3;
    ASSERT_TRUE(test.has_value());

    test.reset();
    ASSERT_FALSE(test.has_value());
}

TEST(test_utility, test_utility_optional_reset_float)
{
    aeon::utility::optional<float> test = 3.0f;
    ASSERT_TRUE(test.has_value());

    test.reset();
    ASSERT_FALSE(test.has_value());
}

TEST(test_utility, test_utility_optional_exception_int)
{
    aeon::utility::optional<int> test;

    ASSERT_FALSE(test.has_value());
    ASSERT_THROW(int value = test; UNUSED(value);, aeon::utility::optional_value_exception);
}

TEST(test_utility, test_utility_optional_exception_int2)
{
    aeon::utility::optional<int> test;

    ASSERT_FALSE(test.has_value());

    ASSERT_THROW(int value = test; UNUSED(value);, aeon::utility::optional_value_exception);

    test = 1337;
    ASSERT_TRUE(test.has_value());
    int value = test;
    ASSERT_EQ(1337, value);
}

TEST(test_utility, test_utility_optional_exception_float)
{
    aeon::utility::optional<float> test;

    ASSERT_FALSE(test.has_value());
    ASSERT_THROW(float value = test; UNUSED(value);, aeon::utility::optional_value_exception);
}

TEST(test_utility, test_utility_optional_exception_float2)
{
    aeon::utility::optional<float> test;

    ASSERT_FALSE(test.has_value());

    ASSERT_THROW(float value = test; UNUSED(value);, aeon::utility::optional_value_exception);

    test = 1337.0f;
    ASSERT_TRUE(test.has_value());
    float value = test;
    ASSERT_EQ(1337.0f, value);
}

TEST(test_utility, test_utility_optional_exception_string)
{
    aeon::utility::optional<std::string> test;

    ASSERT_FALSE(test.has_value());
    ASSERT_THROW(std::string value = test, aeon::utility::optional_value_exception);
}

TEST(test_utility, test_utility_optional_exception_string2)
{
    aeon::utility::optional<std::string> test;

    ASSERT_FALSE(test.has_value());
    ASSERT_THROW(std::string value = test, aeon::utility::optional_value_exception);

    test = std::string("Hello!");
    ASSERT_TRUE(test.has_value());
    std::string value = test;
    ASSERT_EQ(std::string("Hello!"), value);
}

TEST(test_utility, test_utility_optional_compare_int)
{
    aeon::utility::optional<int> test = 3;

    ASSERT_TRUE(test == 3);
}

TEST(test_utility, test_utility_optional_compare_float)
{
    aeon::utility::optional<float> test = 3.1f;
    ASSERT_TRUE(test == 3.1f);
}

TEST(test_utility, test_utility_optional_compare_string)
{
    aeon::utility::optional<std::string> test = std::string("Testing");
    ASSERT_TRUE(std::string(test) == std::string("Testing"));
}
