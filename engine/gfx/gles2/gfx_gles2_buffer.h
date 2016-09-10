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
#include <GLES2/gl2.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gles2
{

DEFINE_EXCEPTION_OBJECT(gfx_gles2_buffer_exception, aeon::common::exception, "Gles2 Buffer error");

class gfx_gles2_buffer : public gfx::buffer
{
public:
    explicit gfx_gles2_buffer(buffer_type type);
    virtual ~gfx_gles2_buffer();

    void set_data(int size, const void *data, buffer_usage usage) override;

    void bind() override;

    bool has_data() const override;

private:
    GLenum __buffer_type_as_gl_enum() const;
    GLenum __buffer_usage_as_gl_enum(buffer_usage usage) const;

    mutable aeon::logger::logger logger_;

    GLuint handle_;
    bool has_data_;
};

using gfx_gles2_buffer_ptr = std::shared_ptr<gfx_gles2_buffer>;

} // namespace gles2
} // namespace gfx
} // namespace aeon
