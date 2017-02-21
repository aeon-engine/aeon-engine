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
#include <gmock/gmock.h>
#include <aeon/hdf5.h>

#define ENABLE_TEMPORARY_FILE_FIXTURE
#include <aeon/testing.h>

using namespace aeon;
using namespace aeon::testutils;

TEST_F(temporary_file_fixture, test_hdf5_create_group)
{
    auto file_path = get_temporary_file_path();

    hdf5::hdf5_file file;
    ASSERT_NO_THROW(file = hdf5::hdf5_file(file_path, hdf5::hdf5_file_open_mode::create));

    ASSERT_NO_THROW(file.create_group("/test"));
    ASSERT_NO_THROW(file.create_group("/a/few/layers/deep"));
    ASSERT_NO_THROW(file.create_group("/a/few/layers/even/deeper/1/2/3"));
}

TEST_F(temporary_file_fixture, test_hdf5_iterator)
{
    auto file_path = get_temporary_file_path();

    hdf5::hdf5_file file;
    ASSERT_NO_THROW(file = hdf5::hdf5_file(file_path, hdf5::hdf5_file_open_mode::create));

    ASSERT_NO_THROW(file.create_group("/test"));
    ASSERT_NO_THROW(file.create_group("/something"));
    ASSERT_NO_THROW(file.create_group("/something/recursion"));

    hdf5::hdf5_iterate iterator;
    ASSERT_NO_THROW(iterator = hdf5::hdf5_iterate(file, hdf5::iterate_mode::recursive));
    auto children = iterator.get_children();

    ASSERT_EQ(3, children.size());
}

TEST_F(temporary_file_fixture, test_hdf5_create_and_delete_groups)
{
    auto file_path = get_temporary_file_path();

    hdf5::hdf5_file file;
    ASSERT_NO_THROW(file = hdf5::hdf5_file(file_path, hdf5::hdf5_file_open_mode::create));

    ASSERT_NO_THROW(file.create_group("/test"));
    ASSERT_NO_THROW(file.create_group("/something"));
    ASSERT_NO_THROW(file.create_group("/a/few/layers/even/deeper/1/2/3"));

    ASSERT_NO_THROW(file.remove("/a"));

    hdf5::hdf5_iterate iterator;
    ASSERT_NO_THROW(iterator = hdf5::hdf5_iterate(file, hdf5::iterate_mode::recursive));
    auto children = iterator.get_children();

    ASSERT_EQ(2, children.size());
}

TEST_F(temporary_file_fixture, test_hdf5_write_data)
{
    auto file_path = get_temporary_file_path();

    hdf5::hdf5_file file;
    ASSERT_NO_THROW(file = hdf5::hdf5_file(file_path, hdf5::hdf5_file_open_mode::create));

    hdf5::hdf5_dataset dataset;
    ASSERT_NO_THROW(dataset = hdf5::hdf5_dataset(file, "/test_dataset"));
    ASSERT_NO_THROW(dataset.write({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));

    hdf5::hdf5_dataset dataset2;
    ASSERT_NO_THROW(dataset2 = hdf5::hdf5_dataset(file, "/test_dataset2"));
    ASSERT_NO_THROW(dataset2.write({1, 2, 3}));
}

TEST_F(temporary_file_fixture, test_hdf5_overwrite_data)
{
    auto file_path = get_temporary_file_path();

    hdf5::hdf5_file file;
    ASSERT_NO_THROW(file = hdf5::hdf5_file(file_path, hdf5::hdf5_file_open_mode::create));

    hdf5::hdf5_dataset dataset;
    ASSERT_NO_THROW(dataset = hdf5::hdf5_dataset(file, "/test_dataset"));
    ASSERT_NO_THROW(dataset.write({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));

    hdf5::hdf5_dataset dataset2;
    ASSERT_NO_THROW(dataset2 = hdf5::hdf5_dataset(file, "/test_dataset"));
    ASSERT_NO_THROW(dataset2.write({1, 2, 3}));
}

TEST_F(temporary_file_fixture, test_hdf5_write_read_data)
{
    auto file_path = get_temporary_file_path();

    hdf5::hdf5_file file;
    ASSERT_NO_THROW(file = hdf5::hdf5_file(file_path, hdf5::hdf5_file_open_mode::create));

    std::vector<std::uint8_t> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    hdf5::hdf5_dataset dataset;
    ASSERT_NO_THROW(dataset = hdf5::hdf5_dataset(file, "/test_dataset"));
    ASSERT_NO_THROW(dataset.write(data));

    hdf5::hdf5_dataset dataset2;
    std::vector<std::uint8_t> data2;
    ASSERT_NO_THROW(dataset2 = hdf5::hdf5_dataset(file, "/test_dataset"));
    ASSERT_NO_THROW(dataset2.read(data2));

    EXPECT_THAT(data, ::testing::ContainerEq(data2));
}
