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

#include <gfx/gfx_buffer.h>
#include <common/exception.h>
#include <common/logger.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace null
{

DEFINE_EXCEPTION_OBJECT(gfx_null_buffer_exception, aeon::common::exception, "NULL GFX Buffer error");

class gfx_null_buffer : public gfx::buffer
{
public:
    explicit gfx_null_buffer(buffer_type type);
    virtual ~gfx_null_buffer();

    void set_data(int size, const void *data, buffer_usage usage) override;

    void bind() override;

    bool has_data() const override;

private:
    aeon::logger::logger logger_;

    bool has_data_;
};

using buffer_ptr = std::shared_ptr<gfx_null_buffer>;

} // namespace null
} // namespace gfx
} // namespace aeon
