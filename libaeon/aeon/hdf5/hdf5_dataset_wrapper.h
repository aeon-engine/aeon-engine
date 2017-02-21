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
#include <string>
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

class hdf5_datatype;
class hdf5_file;
class hdf5_dataspace;
class hdf5_dataset_properties;

class hdf5_dataset_wrapper : utility::noncopyable
{
public:
    hdf5_dataset_wrapper();
    explicit hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path);
    explicit hdf5_dataset_wrapper(const hdf5_file &file, const std::string &path, const hdf5_datatype &datatype,
                                  const hdf5_dataspace &dataspace, const hdf5_dataset_properties &properties);
    ~hdf5_dataset_wrapper();

    hdf5_dataset_wrapper(hdf5_dataset_wrapper &&other);
    hdf5_dataset_wrapper &operator=(hdf5_dataset_wrapper &&other);

    auto get_handle() const;

private:
    hid_t handle_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_dataset_wrapper_impl.h>
