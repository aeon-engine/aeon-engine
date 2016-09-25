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

#include <aeon/common/cached_object.h>
#include <glm/mat4x4.hpp>
#include <memory>

namespace aeon
{
namespace gfx
{

class shader : public common::cached_object
{
public:
    shader();
    virtual ~shader();

    virtual void set_projection_matrix(const glm::mat4 &matrix) = 0;
    virtual void set_model_matrix(const glm::mat4 &matrix) = 0;
    virtual void set_view_matrix(const glm::mat4 &matrix) = 0;
};

using shader_ptr = std::shared_ptr<shader>;

} // namespace gfx
} // namespace aeon
