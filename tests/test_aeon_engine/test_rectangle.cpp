/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <gtest/gtest.h>
#include <aeon/platform.h>
#include <aeon/common/types/rectangle.h>

AEON_IGNORE_VS_WARNING(4189)

using namespace aeon;

TEST(test_rectangle, test_rectangle_default_createint)
{
    common::types::rectangle<int> test;

    EXPECT_EQ(test.left(), 0);
    EXPECT_EQ(test.top(), 0);
    EXPECT_EQ(test.right(), 0);
    EXPECT_EQ(test.bottom(), 0);
}

TEST(test_rectangle, test_rectangle_default_create_float)
{
    common::types::rectangle<float> test;

    EXPECT_EQ(test.left(), 0);
    EXPECT_EQ(test.top(), 0);
    EXPECT_EQ(test.right(), 0);
    EXPECT_EQ(test.bottom(), 0);
}

TEST(test_rectangle, test_rectangle_default_create_double)
{
    common::types::rectangle<double> test;

    EXPECT_EQ(test.left(), 0);
    EXPECT_EQ(test.top(), 0);
    EXPECT_EQ(test.right(), 0);
    EXPECT_EQ(test.bottom(), 0);
}

TEST(test_rectangle, test_rectangle_create_int)
{
    common::types::rectangle<int> test(1, 2, 3, 4);

    EXPECT_EQ(test.left(), 1);
    EXPECT_EQ(test.top(), 2);
    EXPECT_EQ(test.right(), 3);
    EXPECT_EQ(test.bottom(), 4);
}

TEST(test_rectangle, test_rectangle_create_float)
{
    common::types::rectangle<float> test(1.1f, 2.2f, 3.3f, 4.4f);

    EXPECT_EQ(test.left(), 1.1f);
    EXPECT_EQ(test.top(), 2.2f);
    EXPECT_EQ(test.right(), 3.3f);
    EXPECT_EQ(test.bottom(), 4.4f);
}

TEST(test_rectangle, test_rectangle_create_double)
{
    common::types::rectangle<double> test(1.1, 2.2, 3.3, 4.4);

    EXPECT_EQ(test.left(), 1.1);
    EXPECT_EQ(test.top(), 2.2);
    EXPECT_EQ(test.right(), 3.3);
    EXPECT_EQ(test.bottom(), 4.4);
}

TEST(test_rectangle, test_rectangle_is_empty_int)
{
    common::types::rectangle<int> test(10, 20, 30, 40);
    EXPECT_FALSE(test.is_empty());
}

TEST(test_rectangle, test_rectangle_is_empty_float)
{
    common::types::rectangle<float> test(10.1f, 20.2f, 30.3f, 40.4f);
    EXPECT_FALSE(test.is_empty());
}

TEST(test_rectangle, test_rectangle_is_empty_vertical_int)
{
    common::types::rectangle<int> test(10, 0, 20, 0);
    EXPECT_TRUE(test.is_empty());
}

TEST(test_rectangle, test_rectangle_is_empty_vertical_float)
{
    common::types::rectangle<float> test(10.3f, 0.0f, 20.56f, 0.0f);
    EXPECT_TRUE(test.is_empty());
}

TEST(test_rectangle, test_rectangle_is_empty_vertical_double)
{
    common::types::rectangle<double> test(10.3, 0.0, 20.56, 0.0);
    EXPECT_TRUE(test.is_empty());
}

TEST(test_rectangle, test_rectangle_is_empty_horizontal_int)
{
    common::types::rectangle<int> test(0, 10, 0, 20);
    EXPECT_TRUE(test.is_empty());
}

TEST(test_rectangle, test_rectangle_is_empty_horizontal_float)
{
    common::types::rectangle<float> test(0.0f, 10.3f, 0.0f, 20.56f);
    EXPECT_TRUE(test.is_empty());
}

TEST(test_rectangle, test_rectangle_is_empty_horizontal_double)
{
    common::types::rectangle<double> test(0.0, 10.3, 0.0, 20.56);
    EXPECT_TRUE(test.is_empty());
}

TEST(test_rectangle, test_rectangle_int_size_int)
{
    common::types::rectangle<int> test(0, 0, 30, 40);
    glm::vec2 RectSize = test.size<int>();
    EXPECT_EQ(RectSize.x, 30);
    EXPECT_EQ(RectSize.y, 40);
}

TEST(test_rectangle, test_rectangle_int_size_float)
{
    common::types::rectangle<int> test(0, 0, 30, 40);
    glm::vec2 RectSize = test.size<float>();
    EXPECT_FLOAT_EQ(30.0f, RectSize.x);
    EXPECT_FLOAT_EQ(40.0f, RectSize.y);
}

TEST(test_rectangle, test_rectangle_copy_constructor)
{
    common::types::rectangle<float> test(10.0f, 20.0f, 30.0f, 40.0f);
    common::types::rectangle<int> test2(test);

    EXPECT_EQ(test2.left(), 10);
    EXPECT_EQ(test2.top(), 20);
    EXPECT_EQ(test2.right(), 30);
    EXPECT_EQ(test2.bottom(), 40);
}

TEST(test_rectangle, test_rectangle_int_equals)
{
    common::types::rectangle<int> test(100, 200, 300, 400);
    common::types::rectangle<int> test2(100, 200, 300, 400);

    EXPECT_TRUE((test == test2));
}

TEST(test_rectangle, test_rectangle_int_not_equals)
{
    common::types::rectangle<int> test(100, 200, 300, 400);
    common::types::rectangle<int> test2(101, 200, 300, 400);

    EXPECT_TRUE((test != test2));
}

TEST(test_rectangle, test_rectangle_int_not_equals2)
{
    common::types::rectangle<int> test(100, 200, 300, 400);
    common::types::rectangle<int> test2(100, 201, 300, 400);

    EXPECT_TRUE((test != test2));
}

TEST(test_rectangle, test_rectangle_int_not_equals3)
{
    common::types::rectangle<int> test(100, 200, 300, 400);
    common::types::rectangle<int> test2(100, 200, 301, 400);

    EXPECT_TRUE((test != test2));
}

TEST(test_rectangle, test_rectangle_int_not_equals4)
{
    common::types::rectangle<int> test(100, 200, 300, 400);
    common::types::rectangle<int> test2(100, 200, 300, 401);

    EXPECT_TRUE((test != test2));
}

TEST(test_rectangle, test_rectangle_float_equals)
{
    common::types::rectangle<float> test(100.0f, 200.0f, 300.0f, 400.0f);
    common::types::rectangle<float> test2(100.0f, 200.0f, 300.0f, 400.0f);

    EXPECT_TRUE((test == test2));
}

TEST(test_rectangle, test_rectangleFloatNotEquals)
{
    common::types::rectangle<float> test(100.0f, 200.0f, 300.0f, 400.0f);
    common::types::rectangle<float> test2(101.0f, 200.0f, 300.0f, 400.0f);

    EXPECT_TRUE((test != test2));
}

TEST(test_rectangle, test_rectangle_float_not_equals2)
{
    common::types::rectangle<float> test(100.0f, 200.0f, 300.0f, 400.0f);
    common::types::rectangle<float> test2(100.0f, 201.0f, 300.0f, 400.0f);

    EXPECT_TRUE((test != test2));
}

TEST(test_rectangle, test_rectangle_float_not_equals3)
{
    common::types::rectangle<float> test(100.0f, 200.0f, 300.0f, 400.0f);
    common::types::rectangle<float> test2(100.0f, 200.0f, 301.0f, 400.0f);

    EXPECT_TRUE((test != test2));
}

TEST(test_rectangle, test_rectangle_float_not_equals4)
{
    common::types::rectangle<float> test(100.0f, 200.0f, 300.0f, 400.0f);
    common::types::rectangle<float> test2(100.0f, 200.0f, 300.0f, 401.0f);

    EXPECT_TRUE((test != test2));
}
