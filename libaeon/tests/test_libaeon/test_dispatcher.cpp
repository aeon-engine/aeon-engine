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

TEST(test_dispatcher, test_dispatcher_basic_run)
{
    aeon::utility::dispatcher dispatcher;

    std::thread t([&]() { dispatcher.run(); });

    bool called1 = false;
    dispatcher.post([&called1]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        called1 = true;
    });

    bool called2 = false;
    dispatcher.post([&called2]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        called2 = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    dispatcher.stop();

    t.join();

    EXPECT_TRUE(called1);
    EXPECT_TRUE(called2);
}

TEST(test_dispatcher, test_dispatcher_call_void)
{
    aeon::utility::dispatcher dispatcher;

    std::thread t([&]() { dispatcher.run(); });

    bool called = false;
    dispatcher.call([&called]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        called = true;
    });

    EXPECT_TRUE(called);

    dispatcher.stop();
    t.join();
}

TEST(test_dispatcher, test_dispatcher_call_int)
{
    aeon::utility::dispatcher dispatcher;

    std::thread t([&]() { dispatcher.run(); });

    bool called = false;
    int value = dispatcher.call<int>([&called]() {
        called = true;
        return 1337;
    });

    EXPECT_TRUE(called);
    EXPECT_EQ(1337, value);

    dispatcher.stop();
    t.join();
}
