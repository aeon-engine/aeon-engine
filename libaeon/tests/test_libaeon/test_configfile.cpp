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

#define ENABLE_TEMPORARY_FILE_FIXTURE
#include <aeon/testing.h>
#include <aeon/utility.h>

using namespace aeon::testutils;

TEST_F(temporary_file_fixture, test_configfile_create)
{
    ASSERT_NO_THROW(aeon::utility::configfile file);
}

TEST_F(temporary_file_fixture, test_configfile_load_empty)
{
    aeon::utility::configfile file;
    ASSERT_THROW(file.load(get_temporary_file_path()), aeon::utility::configfile_exception);
}

TEST_F(temporary_file_fixture, test_configfile_save)
{
    aeon::utility::configfile file;

    file.set<int>("entry_test", 1337);
    file.set<int>("entry_something", 42);
    file.set<float>("one_or_another", 42.42f);

    ASSERT_NO_THROW(file.save(get_temporary_file_path()));
}

TEST_F(temporary_file_fixture, test_configfile_save_and_load)
{
    {
        aeon::utility::configfile file;

        file.set<int>("entry_test", 1337);
        file.set<std::string>("entry_something", "42");
        file.set<float>("one_or_another", 42.42f);
        file.set<bool>("one_theone", false);

        ASSERT_NO_THROW(file.save(get_temporary_file_path()));
    }
    {
        aeon::utility::configfile file;
        ASSERT_NO_THROW(file.load(get_temporary_file_path()));

        ASSERT_TRUE(file.has_entry("entry_test"));
        ASSERT_TRUE(file.has_entry("entry_something"));
        ASSERT_TRUE(file.has_entry("one_or_another"));
        ASSERT_TRUE(file.has_entry("one_theone"));

        ASSERT_EQ(1337, file.get<int>("entry_test", 0));
        ASSERT_EQ("42", file.get<std::string>("entry_something", ""));
        ASSERT_FLOAT_EQ(42.42f, file.get<float>("one_or_another", 0.0f));
        ASSERT_EQ(false, file.get<bool>("one_theone", true));
    }
}

TEST_F(temporary_file_fixture, test_configfile_has_value)
{
    aeon::utility::configfile file;

    ASSERT_FALSE(file.has_entry("entry_test"));

    file.set<int>("entry_test", 1337);

    ASSERT_TRUE(file.has_entry("entry_test"));
}

TEST_F(temporary_file_fixture, test_configfile_default_value)
{
    aeon::utility::configfile file;

    ASSERT_EQ(42, file.get<int>("entry_test", 42));

    file.set<int>("entry_test", 1337);

    ASSERT_EQ(1337, file.get<int>("entry_test", 42));
}

TEST(test_configfile, test_configfile_read_from_memory)
{
    std::string data = "test=123\nblah=42\nsomething=hello\n";
    std::vector<std::uint8_t> vec(data.size());
    memcpy(vec.data(), data.data(), data.size());

    aeon::utility::configfile file;
    ASSERT_NO_THROW(file.load(std::move(vec)));

    ASSERT_TRUE(file.has_entry("test"));
    ASSERT_TRUE(file.has_entry("blah"));
    ASSERT_TRUE(file.has_entry("something"));

    ASSERT_EQ(123, file.get<int>("test", 0));
    ASSERT_EQ(42, file.get<int>("blah", 0));
    ASSERT_EQ("hello", file.get<std::string>("something", ""));
}

TEST(test_configfile, test_configfile_read_to_memory)
{
    aeon::utility::configfile file;

    file.set<int>("entry_test", 1337);
    file.set<std::string>("entry_something", "42");
    file.set<float>("one_or_another", 42.42f);
    file.set<bool>("one_theone", false);

    std::vector<std::uint8_t> vec;
    ASSERT_NO_THROW(file.save(vec));
    ASSERT_GT(static_cast<int>(vec.size()), 0);
}
