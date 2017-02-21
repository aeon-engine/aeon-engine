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

namespace aeon
{
namespace hdf5
{

inline hdf5_dataset_properties::hdf5_dataset_properties()
    : handle_(-1)
{
    handle_ = H5Pcreate(H5P_DATASET_CREATE);

    if (handle_ < 0)
        throw std::runtime_error("H5Pcreate failed.");
}

inline hdf5_dataset_properties::~hdf5_dataset_properties()
{
    if (handle_ >= 0)
        H5Pclose(handle_);
}

inline hdf5_dataset_properties::hdf5_dataset_properties(hdf5_dataset_properties &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

inline hdf5_dataset_properties &hdf5_dataset_properties::operator=(hdf5_dataset_properties &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

inline void hdf5_dataset_properties::set_filltime(const hdf5_dataset_filltime mode) const
{
    herr_t result = 0;

    switch (mode)
    {
        case hdf5_dataset_filltime::alloc:
            result = H5Pset_fill_time(handle_, H5D_FILL_TIME_ALLOC);
            break;
        case hdf5_dataset_filltime::never:
            result = H5Pset_fill_time(handle_, H5D_FILL_TIME_NEVER);
            break;
        case hdf5_dataset_filltime::ifset:
            result = H5Pset_fill_time(handle_, H5D_FILL_TIME_IFSET);
            break;
        default:
            throw std::runtime_error("Unsupported dataset filltime.");
    }

    if (result < 0)
        throw std::runtime_error("H5Pset_fill_time failed.");
}

inline auto hdf5_dataset_properties::get_handle() const
{
    return handle_;
}

} // namespace hdf5
} // namespace aeon
