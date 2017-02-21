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

#include <aeon/utility/noncopyable.h>

namespace aeon
{
namespace hdf5
{

enum class iterate_mode
{
    normal,
    recursive
};

class hdf5_file;

class hdf5_iterate : public utility::noncopyable
{
public:
    hdf5_iterate();

    explicit hdf5_iterate(const hdf5_file &file, const iterate_mode mode = iterate_mode::normal);

    explicit hdf5_iterate(const hdf5_file &file, const std::string &path,
                          const iterate_mode mode = iterate_mode::normal);

    ~hdf5_iterate() = default;

    hdf5_iterate(hdf5_iterate &&other);
    hdf5_iterate &operator=(hdf5_iterate &&other);

    const auto &get_children() const;

    auto begin() const;
    auto end() const;

    auto cbegin() const;
    auto cend() const;

private:
    static herr_t __iterate_callback(hid_t obj, const char *name, const H5O_info_t *info, void *op_data);

    herr_t __iterate_callback(const std::string &name, const H5O_info_t *info);

    iterate_mode mode_;
    std::vector<hdf5_object> children_;
};

} // namespace hdf5
} // namespace aeon

#include <aeon/hdf5/hdf5_object_iterator_impl.h>
