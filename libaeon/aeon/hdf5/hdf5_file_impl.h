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

#include <aeon/filesystem/filesystem.h>
#include <aeon/hdf5/hdf5_scoped_create_group.h>
#include <aeon/utility/string.h>
#include <string>

namespace aeon
{
namespace hdf5
{

inline hdf5_file::hdf5_file()
    : file_(-1)
{
}

inline hdf5_file::hdf5_file(const std::string &path, const hdf5_file_open_mode mode)
    : file_(-1)
{
    switch (mode)
    {
        case create:
        {
            if (filesystem::exists(path))
                throw std::runtime_error("Can not create HDF5 file. File exists.");

            file_ = H5Fcreate(path.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
        }
        break;
        case read_only:
        {
            if (!filesystem::exists(path))
                throw std::runtime_error("Can not open HDF5 file. File doesn't exist.");

            file_ = H5Fopen(path.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
        }
        break;
        case read_write:
        {
            if (!filesystem::exists(path))
                throw std::runtime_error("Can not open HDF5 file. File doesn't exist.");

            file_ = H5Fopen(path.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
        }
        break;
        default:
            assert(true && "Unknown or invalid mode.");
    }

    if (file_ < 0)
        throw std::runtime_error("Error opening hdf5 file.");
}

inline hdf5_file::~hdf5_file()
{
    if (file_ >= 0)
        H5Fclose(file_);
}

inline hdf5_file::hdf5_file(hdf5_file &&other)
    : file_(other.file_)
{
    other.file_ = -1;
}

inline hdf5_file &hdf5_file::operator=(hdf5_file &&other)
{
    file_ = other.file_;
    other.file_ = -1;
    return *this;
}

inline auto hdf5_file::exists(const std::string &path) const
{
    return path == "/" || H5Lexists(file_, path.c_str(), H5P_DEFAULT) > 0;
}

inline void hdf5_file::remove(const std::string &path) const
{
    if (H5Ldelete(file_, path.c_str(), H5P_DEFAULT) < 0)
        throw std::runtime_error("Error deleting dataset. H5Ldelete failed.");
}

inline void hdf5_file::create_group(const std::string &path) const
{
    auto groups = utility::string::split(path, '/');

    if (groups.empty())
        return;

    std::string current_path;

    for (auto &group : groups)
    {
        current_path += "/" + group;
        if (!exists(current_path))
        {
            hdf5_scoped_create_group create_group(file_, current_path);
        }
    }
}

inline auto hdf5_file::get_hid() const
{
    return file_;
}

} // namespace hdf5
} // namespace aeon
