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

inline hdf5_object::hdf5_object(const std::string &name, const H5O_info_t *info)
    : name_(name)
    , type_(hdf5_object_type::invalid)
    , last_access_time_(std::chrono::system_clock::from_time_t(info->atime))
    , modification_time_(std::chrono::system_clock::from_time_t(info->mtime))
    , metadata_modification_time_(std::chrono::system_clock::from_time_t(info->ctime))
    , created_time_(std::chrono::system_clock::from_time_t(info->btime))
{
    switch (info->type)
    {
        case H5O_TYPE_GROUP:
            type_ = hdf5_object_type::group;
            break;
        case H5O_TYPE_DATASET:
            type_ = hdf5_object_type::dataset;
            break;
        case H5O_TYPE_NAMED_DATATYPE:
            type_ = hdf5_object_type::named_datatype;
            break;
        case H5O_TYPE_NTYPES:
        case H5O_TYPE_UNKNOWN:
        default:
            type_ = hdf5_object_type::invalid;
    }
}

inline auto hdf5_object::get_name() const
{
    return name_;
}

inline auto hdf5_object::get_type() const
{
    return type_;
}

inline auto hdf5_object::get_last_access_time() const
{
    return last_access_time_;
}

inline auto hdf5_object::get_modification_time() const
{
    return modification_time_;
}

inline auto hdf5_object::get_metadata_modification_time() const
{
    return metadata_modification_time_;
}

inline auto hdf5_object::get_created_time() const
{
    return created_time_;
}

} // namespace hdf5
} // namespace aeon
