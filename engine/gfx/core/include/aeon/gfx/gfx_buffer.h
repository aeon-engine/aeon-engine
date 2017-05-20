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
namespace gfx
{

enum class buffer_type
{
    array,        // Vertex attributes
    element_array // Vertex array indices
};

enum class buffer_usage
{
    stream_usage, // Modified once and used at most a few times
    static_usage, // Modified once and used many times
    dynamic_usage // Modified repeatedly and used many times
};

class buffer
{
public:
    explicit buffer(buffer_type type);
    virtual ~buffer() = default;

    auto get_type() const -> buffer_type;

    virtual void set_data(int size, const void *data, buffer_usage usage) = 0;

    virtual void bind() = 0;

    virtual auto has_data() const -> bool = 0;

protected:
    buffer_type type_;
};

} // namespace gfx
} // namespace aeon
