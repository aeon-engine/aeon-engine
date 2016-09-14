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

#include <gfx/null/gfx_null_buffer.h>

namespace aeon
{
namespace gfx
{
namespace null
{

gfx_null_buffer::gfx_null_buffer(buffer_type type)
    : gfx::buffer(type)
    , logger_(common::logger::get_singleton(), "Gfx::Null::Buffer")
    , has_data_(false)
{
    AEON_LOG_TRACE(logger_) << "Created buffer." << std::endl;
}

gfx_null_buffer::~gfx_null_buffer()
{
    AEON_LOG_TRACE(logger_) << "Deleting buffer." << std::endl;
}

void gfx_null_buffer::set_data(int size, const void *, buffer_usage)
{
    AEON_LOG_TRACE(logger_) << "Setting buffer data "
                            << "(" << size << " bytes.)" << std::endl;
    has_data_ = true;
}

void gfx_null_buffer::bind()
{
}

bool gfx_null_buffer::has_data() const
{
    return has_data_;
}

} // namespace null
} // namespace gfx
} // namespace aeon
