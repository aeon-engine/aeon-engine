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

#include <gfx/gfx_shader.h>
#include <common/logger.h>
#include <memory>

namespace aeon
{
namespace gfx
{
namespace null
{

class gfx_null_shader : public gfx::shader
{
    friend class gfx_null_shader_manager;

public:
    gfx_null_shader();
    ~gfx_null_shader() override;

    void bind() const;

    void set_projection_matrix(const glm::mat4 &matrix) override;
    void set_model_matrix(const glm::mat4 &matrix) override;
    void set_view_matrix(const glm::mat4 &matrix) override;

private:
    aeon::logger::logger logger_;
};

using gfx_null_shader_ptr = std::shared_ptr<gfx_null_shader>;

} // namespace null
} // namespace gfx
} // namespace aeon
