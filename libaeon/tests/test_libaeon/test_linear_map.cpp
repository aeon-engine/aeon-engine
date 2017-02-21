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

struct test_fixture_linear_map_default_data : public ::testing::Test
{
    test_fixture_linear_map_default_data()
    {
        linear_map_["One"] = 1;
        linear_map_["Two"] = 2;
        linear_map_["Three"] = 3;
        linear_map_["Four"] = 4;
        linear_map_["Five"] = 5;
    }

    void SetUp() override
    {
        ASSERT_EQ(5, linear_map_.size());
    }

    aeon::utility::linear_map<std::string, int> linear_map_;
};

TEST_F(test_fixture_linear_map_default_data, test_linear_map_at)
{
    int at_one = linear_map_.at("One");
    int at_two = linear_map_.at("Two");
    int at_three = linear_map_.at("Three");
    int at_four = linear_map_.at("Four");
    int at_five = linear_map_.at("Five");

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(3, at_three);
    ASSERT_EQ(4, at_four);
    ASSERT_EQ(5, at_five);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_index_operator)
{
    int at_one = linear_map_["One"];
    int at_two = linear_map_["Two"];
    int at_three = linear_map_["Three"];
    int at_four = linear_map_["Four"];
    int at_five = linear_map_["Five"];

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(3, at_three);
    ASSERT_EQ(4, at_four);
    ASSERT_EQ(5, at_five);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_index_operator_overwrite)
{
    linear_map_["Three"] = 42;
    linear_map_["Four"] = 32;

    int at_one = linear_map_["One"];
    int at_two = linear_map_["Two"];
    int at_three = linear_map_["Three"];
    int at_four = linear_map_["Four"];
    int at_five = linear_map_["Five"];

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(42, at_three);
    ASSERT_EQ(32, at_four);
    ASSERT_EQ(5, at_five);

    ASSERT_EQ(5, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_insert_ex_collision)
{
    auto result = linear_map_.insert_ex("Three", 15);
    ASSERT_TRUE(result == linear_map_.end());

    int at_three = linear_map_["Three"];
    ASSERT_EQ(3, at_three);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_index_operator_default)
{
    int cant_find = linear_map_["Something! 123"];

    ASSERT_EQ(0, cant_find);
    ASSERT_EQ(6, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_empty_and_clear)
{
    ASSERT_FALSE(linear_map_.empty());
    linear_map_.clear();
    ASSERT_TRUE(linear_map_.empty());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_find)
{
    auto result = linear_map_.find("Three");

    ASSERT_EQ("Three", result->first);
    ASSERT_EQ(3, result->second);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_not_found)
{
    auto result = linear_map_.find("Something! 123");

    ASSERT_TRUE(result == linear_map_.end());
    ASSERT_EQ(5, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_iterate)
{
    int loop_times = 0;
    for (auto item : linear_map_)
    {
        if (item.first == "One")
            ASSERT_EQ(1, item.second);

        if (item.first == "Two")
            ASSERT_EQ(2, item.second);

        if (item.first == "Three")
            ASSERT_EQ(3, item.second);

        if (item.first == "Four")
            ASSERT_EQ(4, item.second);

        if (item.first == "Five")
            ASSERT_EQ(5, item.second);

        ++loop_times;
    }

    ASSERT_EQ(5, linear_map_.size());
    ASSERT_EQ(5, loop_times);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_erase_by_key)
{
    linear_map_.erase("Something! 123");
    ASSERT_EQ(5, linear_map_.size());

    linear_map_.erase("Three");
    ASSERT_EQ(4, linear_map_.size());

    linear_map_.erase("Two");
    ASSERT_EQ(3, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_erase_by_iterator)
{
    ASSERT_EQ(5, linear_map_.size());

    auto result = linear_map_.find("Three");
    linear_map_.erase(result);

    ASSERT_EQ(4, linear_map_.size());

    result = linear_map_.find("Two");
    linear_map_.erase(result);

    ASSERT_EQ(3, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_erase_if)
{
    ASSERT_EQ(5, linear_map_.size());
    linear_map_.erase_if([](const aeon::utility::linear_map<std::string, int>::pair_type &pair) {
        return (pair.first == "Two" || pair.first == "Four");
    });
    ASSERT_EQ(3, linear_map_.size());
}
