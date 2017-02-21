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

#include <array>

namespace aeon
{
namespace hdf5
{

inline hdf5_dataspace::hdf5_dataspace()
    : handle_(-1)
    , size_(0)
{
}

inline hdf5_dataspace::hdf5_dataspace(const hid_t dataset_handle)
    : handle_(-1)
    , size_(0)
{
    handle_ = H5Dget_space(dataset_handle);

    if (handle_ < 0)
        throw std::runtime_error("H5Dget_space failed.");

    auto dimensions = H5Sget_simple_extent_ndims(handle_);

    if (dimensions != 1)
        throw std::runtime_error("Only 1D arrays are currently supported.");

    hsize_t array_size;
    H5Sget_simple_extent_dims(handle_, &array_size, nullptr);

    size_ = array_size;
}

inline hdf5_dataspace::hdf5_dataspace(const std::size_t reserve_size)
    : handle_(-1)
    , size_(reserve_size)
{
    handle_ = H5Screate(H5S_SIMPLE);

    if (handle_ < 0)
        throw std::runtime_error("H5Screate failed.");

    std::array<hsize_t, 1> dimensions = {reserve_size};

    if (H5Sset_extent_simple(handle_, 1, dimensions.data(), nullptr) < 0)
        throw std::runtime_error("H5Sset_extent_simple failed.");
}

inline hdf5_dataspace::~hdf5_dataspace()
{
    if (handle_ >= 0)
        H5Sclose(handle_);
}

inline hdf5_dataspace::hdf5_dataspace(hdf5_dataspace &&other)
    : handle_(other.handle_)
    , size_(other.size_)
{
    other.handle_ = -1;
}

inline hdf5_dataspace &hdf5_dataspace::operator=(hdf5_dataspace &&other)
{
    handle_ = other.handle_;
    size_ = other.size_;
    other.handle_ = -1;
    return *this;
}

inline auto hdf5_dataspace::get_handle() const
{
    return handle_;
}

inline auto hdf5_dataspace::get_size() const
{
    return size_;
}

} // namespace hdf5
} // namespace aeon
