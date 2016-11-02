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

#include <aeon/gfx/gfx_buffer.h>
#include <aeon/common/exception.h>
#include <aeon/common/logger.h>
#include <GL/glew.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace gl
{

DEFINE_EXCEPTION_OBJECT(gfx_opengl_buffer_exception, aeon::common::exception, "GL Buffer error");

class gfx_gl_buffer : public gfx::buffer
{
public:
    explicit gfx_gl_buffer(buffer_type type);
    virtual ~gfx_gl_buffer();

    void set_data(int size, const void *data, buffer_usage usage) override;

    void bind() override;

    bool has_data() const override;

private:
    GLenum __buffer_type_as_gl_enum() const;
    GLenum __buffer_usage_as_gl_enum(buffer_usage usage) const;

    aeon::logger::logger logger_;

    GLuint handle_;
    bool has_data_;
};

} // namespace gl
} // namespace gfx
} // namespace aeon
