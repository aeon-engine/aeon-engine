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

#include <hdf5.h>
#include <cstddef>
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

enum class hdf5_array_data_type
{
    uint8
};

enum class hdf5_array_byte_order
{
    little_endian
};

class hdf5_datatype : utility::noncopyable
{
public:
    hdf5_datatype();
    explicit hdf5_datatype(const hdf5_array_data_type data_type, const hdf5_array_byte_order byte_order);
    ~hdf5_datatype();

    hdf5_datatype(hdf5_datatype &&other);
    hdf5_datatype &operator=(hdf5_datatype &&other);

    auto get_handle() const;

private:
    hid_t handle_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_datatype_impl.h>
