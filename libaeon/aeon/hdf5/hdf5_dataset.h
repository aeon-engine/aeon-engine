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

#include <string>
#include <vector>
#include <hdf5.h>
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

class hdf5_file;

class hdf5_dataset : utility::noncopyable
{
public:
    hdf5_dataset();
    explicit hdf5_dataset(hdf5_file &file, const std::string &path);
    ~hdf5_dataset();

    hdf5_dataset(hdf5_dataset &&other);
    hdf5_dataset &operator=(hdf5_dataset &&other);

    void write(const std::uint8_t *data, const std::size_t size);
    void write(const std::vector<std::uint8_t> &data);

    void read(std::vector<std::uint8_t> &data);

private:
    hdf5_file *file_;
    hdf5_datatype datatype_;
    hdf5_dataset_properties properties_;
    std::string path_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_dataset_impl.h>
