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

inline hdf5_datatype::hdf5_datatype()
    : handle_(-1)
{
}

inline hdf5_datatype::hdf5_datatype(const hdf5_array_data_type data_type, const hdf5_array_byte_order byte_order)
    : handle_(-1)
{
    assert(data_type == hdf5_array_data_type::uint8);
    assert(byte_order == hdf5_array_byte_order::little_endian);

    handle_ = H5Tcopy(H5T_NATIVE_UINT8);
    auto status = H5Tset_order(handle_, H5T_ORDER_LE);

    if (status < 0)
        throw std::runtime_error("H5Tset_order failed.");
}

inline hdf5_datatype::~hdf5_datatype()
{
    if (handle_ >= 0)
        H5Tclose(handle_);
}

inline hdf5_datatype::hdf5_datatype(hdf5_datatype &&other)
    : handle_(other.handle_)
{
    other.handle_ = -1;
}

inline hdf5_datatype &hdf5_datatype::operator=(hdf5_datatype &&other)
{
    handle_ = other.handle_;
    other.handle_ = -1;
    return *this;
}

inline auto hdf5_datatype::get_handle() const
{
    return handle_;
}

} // namespace hdf5
} // namespace aeon
