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

#include <aeon/hdf5/hdf5_datatype.h>
#include <aeon/hdf5/hdf5_dataspace.h>
#include <aeon/hdf5/hdf5_dataset_properties.h>

namespace aeon
{
namespace hdf5
{

inline hdf5_dataset_wrapper::hdf5_dataset_wrapper()
    : handle_(-1)
{
}

inline hdf5_dataset_wrapper::hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path)
    : handle_(-1)
{
    handle_ = H5Dopen(file.get_hid(), path.c_str(), H5P_DEFAULT);

    if (handle_ < 0)
        throw std::runtime_error("H5Dopen failed.");
}

inline hdf5_dataset_wrapper::hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path,
                                                  const hdf5_datatype &datatype, const hdf5_dataspace &dataspace,
                                                  const hdf5_dataset_properties &properties)
    : handle_(-1)
{
    handle_ = H5Dcreate(file.get_hid(), path.c_str(), datatype.get_handle(), dataspace.get_handle(), H5P_DEFAULT,
                        properties.get_handle(), H5P_DEFAULT);

    if (handle_ < 0)
        throw std::runtime_error("H5Dcreate failed.");
}

inline hdf5_dataset_wrapper::~hdf5_dataset_wrapper()
{
    if (handle_ >= 0)
        H5Dclose(handle_);
}

inline hdf5_dataset_wrapper::hdf5_dataset_wrapper(hdf5_dataset_wrapper &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

inline hdf5_dataset_wrapper &hdf5_dataset_wrapper::operator=(hdf5_dataset_wrapper &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

inline auto hdf5_dataset_wrapper::get_handle() const
{
    return handle_;
}

} // namespace hdf5
} // namespace aeon
