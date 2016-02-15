/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

#include <memory>

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

    buffer_type get_type() const;

    virtual void set_data(int size, const void *data, buffer_usage usage) = 0;

    virtual void bind() = 0;

protected:
    buffer_type type_;
};

using buffer_ptr = std::shared_ptr<buffer>;

} // namespace gfx
} // namespace aeon
