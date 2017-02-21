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
namespace streams
{

class stream_name_mixin
{
public:
    stream_name_mixin()
        : name_(AEON_STREAM_DEFAULT_NAME)
        , has_name_(false)
    {
    }

    explicit stream_name_mixin(const std::string &name)
        : name_(name)
        , has_name_(true)
    {
    }

    virtual ~stream_name_mixin() = default;

    stream_name_mixin(stream_name_mixin &&o) = default;
    stream_name_mixin &operator=(stream_name_mixin &&other) = default;

    std::string get_name() const
    {
        return name_;
    }

    void set_name(const std::string &name)
    {
        name_ = name;
    }

    bool has_name() const
    {
        return has_name_;
    }

private:
    std::string name_;
    bool has_name_;
};

} // namespace streams
} // namespace aeon
