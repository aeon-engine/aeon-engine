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

TEST(test_signals, test_signals_connect)
{
    aeon::utility::signal<> signal;
    auto connection = signal.connect([]() {});
    EXPECT_GT(connection.get_handle(), 0);
}

TEST(test_signals, test_signals_connection_default_zero)
{
    aeon::utility::signal_connection<> connection;
    EXPECT_EQ(0, connection.get_handle());
}

TEST(test_signals, test_signals_connect_parameters)
{
    aeon::utility::signal<int, int> signal;
    auto connection = signal.connect([](int, int) {});
    EXPECT_GT(connection.get_handle(), 0);
}

TEST(test_signals, test_signals_connect_operator)
{
    aeon::utility::signal<> signal;
    auto connection = signal += []() {};
    EXPECT_GT(connection.get_handle(), 0);
}

TEST(test_signals, test_signals_connect_operator_parameters)
{
    aeon::utility::signal<int, int> signal;
    auto connection = signal += [](int, int) {};
    EXPECT_GT(connection.get_handle(), 0);
}

TEST(test_signals, test_signals_connect_one_and_call)
{
    aeon::utility::signal<> signal;

    bool signal_called = false;
    signal += [&signal_called]() { signal_called = true; };

    signal();

    EXPECT_TRUE(signal_called);
}

TEST(test_signals, test_signals_connect_multiple_and_call)
{
    aeon::utility::signal<> signal;

    bool signal_called = false;
    bool signal_called2 = false;
    bool signal_called3 = false;

    signal += [&signal_called]() { signal_called = true; };
    signal += [&signal_called2]() { signal_called2 = true; };
    signal += [&signal_called3]() { signal_called3 = true; };

    signal();

    EXPECT_TRUE(signal_called);
    EXPECT_TRUE(signal_called2);
    EXPECT_TRUE(signal_called3);
}

TEST(test_signals, test_signals_connect_one_and_call_parameters)
{
    aeon::utility::signal<int, int> signal;

    bool signal_called = false;
    int value1 = 0;
    int value2 = 0;
    signal += [&signal_called, &value1, &value2](int val1, int val2) {
        signal_called = true;
        value1 = val1;
        value2 = val2;
    };

    signal(42, 1337);

    EXPECT_TRUE(signal_called);
    EXPECT_EQ(42, value1);
    EXPECT_EQ(1337, value2);
}

TEST(test_signals, test_signals_connect_multiple_and_call_with_disconnect)
{
    aeon::utility::signal<> signal;

    bool signal_called = false;
    bool signal_called2 = false;
    bool signal_called3 = false;

    signal += [&signal_called]() { signal_called = true; };
    auto connection = signal += [&signal_called2]() { signal_called2 = true; };
    signal += [&signal_called3]() { signal_called3 = true; };

    signal();

    EXPECT_TRUE(signal_called);
    EXPECT_TRUE(signal_called2);
    EXPECT_TRUE(signal_called3);

    signal_called = false;
    signal_called2 = false;
    signal_called3 = false;

    signal.disconnect(connection);

    signal();

    EXPECT_TRUE(signal_called);
    EXPECT_FALSE(signal_called2);
    EXPECT_TRUE(signal_called3);
}

TEST(test_signals, test_signals_mt_sync_execution)
{
    aeon::utility::signal_mt<> signal;
    std::array<int, 200> destination{};

    int index = 0;
    signal += [&index, &destination] { destination[index++]++; };

    std::vector<std::thread> threads;
    auto thread_func = [&signal] {
        for (int i = 0; i < 100; ++i)
        {
            signal();
            std::this_thread::sleep_for(std::chrono::microseconds(0));
        }
    };
    threads.emplace_back(thread_func);
    threads.emplace_back(thread_func);

    for (auto &itr : threads)
        itr.join();

    for (auto &itr : destination)
        EXPECT_EQ(itr, 1);
}
