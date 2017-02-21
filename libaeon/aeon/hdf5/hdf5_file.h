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
#include <hdf5.h>
#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

enum hdf5_file_open_mode
{
    create,
    read_only,
    read_write
};

class hdf5_file : public utility::noncopyable
{
public:
    hdf5_file();
    explicit hdf5_file(const std::string &path, const hdf5_file_open_mode mode);
    ~hdf5_file();

    hdf5_file(hdf5_file &&other);
    hdf5_file &operator=(hdf5_file &&other);

    auto exists(const std::string &path) const;

    void remove(const std::string &path) const;

    void create_group(const std::string &path) const;

    auto get_hid() const;

private:
    hid_t file_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_file_impl.h>
