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

inline hdf5_dataset::hdf5_dataset()
    : file_(nullptr)
    , datatype_()
    , properties_()
    , path_()
{
}

inline hdf5_dataset::hdf5_dataset(hdf5_file &file, const std::string &path)
    : file_(&file)
    , datatype_(hdf5_array_data_type::uint8, hdf5_array_byte_order::little_endian)
    , properties_()
    , path_(path)
{
    properties_.set_filltime(hdf5_dataset_filltime::never);
}

inline hdf5_dataset::~hdf5_dataset() = default;

inline hdf5_dataset::hdf5_dataset(hdf5_dataset &&other)
    : file_(other.file_)
    , datatype_(std::move(other.datatype_))
    , properties_(std::move(other.properties_))
    , path_(std::move(other.path_))
{
}

inline hdf5_dataset &hdf5_dataset::operator=(hdf5_dataset &&other)
{
    file_ = std::move(other.file_);
    datatype_ = std::move(other.datatype_);
    properties_ = std::move(other.properties_);
    path_ = std::move(other.path_);
    return *this;
}

inline void hdf5_dataset::write(const std::uint8_t *data, const std::size_t size)
{
    if (file_->exists(path_))
        file_->remove(path_);

    auto dataspace = hdf5_dataspace(size);
    auto dataset = hdf5_dataset_wrapper(*file_, path_, datatype_, dataspace, properties_);

    auto result = H5Dwrite(dataset.get_handle(), H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

    if (result < 0)
        throw std::runtime_error("Could not write to dataset. H5Dwrite failed.");
}

inline void hdf5_dataset::write(const std::vector<std::uint8_t> &data)
{
    write(data.data(), data.size());
}

inline void hdf5_dataset::read(std::vector<std::uint8_t> &data)
{
    auto dataset = hdf5_dataset_wrapper(*file_, path_);
    auto dataspace = hdf5_dataspace(dataset.get_handle());
    data.resize(dataspace.get_size());

    auto result = H5Dread(dataset.get_handle(), H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data.data());

    if (result < 0)
        throw std::runtime_error("Could not read from dataset. H5Dread failed.");
}

} // namespace hdf5
} // namespace aeon
