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
#include <aeon/filesystem.h>

#include <fstream>

using namespace aeon::testutils;

TEST(test_filesystem, test_filesystem_exists)
{
    EXPECT_FALSE(aeon::filesystem::exists("SoMePaThThAtDoEsNtExIsT1234"));
}

TEST(test_filesystem, test_filesystem_exists2)
{
    EXPECT_FALSE(aeon::filesystem::exists("SoMe/PaTh/ThAt/DoEsNt/ExIsT/1234"));
}

TEST(test_filesystem, test_filesystem_exists_empty)
{
    EXPECT_FALSE(aeon::filesystem::exists(""));
}

TEST_F(temporary_file_fixture, test_filesystem_exists_file)
{
    EXPECT_FALSE(aeon::filesystem::exists(get_temporary_file_path()));
}

TEST_F(temporary_file_fixture, test_filesystem_exists_file2)
{
    EXPECT_FALSE(aeon::filesystem::exists(get_temporary_file_path()));

    std::ofstream f(get_temporary_file_path(), std::ios::trunc);
    EXPECT_TRUE(aeon::filesystem::exists(get_temporary_file_path()));
    f.close();

    delete_temporary_file();

    EXPECT_FALSE(aeon::filesystem::exists(get_temporary_file_path()));
}
