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
#include <chrono>

namespace aeon
{
namespace hdf5
{

enum class hdf5_object_type
{
    group,
    dataset,
    named_datatype,
    invalid
};

class hdf5_object
{
    friend class hdf5_iterate;

public:
    hdf5_object() = default;
    explicit hdf5_object(const std::string &name, const H5O_info_t *info);
    ~hdf5_object() = default;

    auto get_name() const;

    auto get_type() const;

    auto get_last_access_time() const;

    auto get_modification_time() const;

    auto get_metadata_modification_time() const;

    auto get_created_time() const;

private:
    std::string name_;
    hdf5_object_type type_;
    std::chrono::system_clock::time_point last_access_time_;
    std::chrono::system_clock::time_point modification_time_;
    std::chrono::system_clock::time_point metadata_modification_time_;
    std::chrono::system_clock::time_point created_time_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_object_impl.h>
