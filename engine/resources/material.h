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

#include <resources/resource.h>
#include <resources/exceptions.h>
#include <resources/wrappers/material_resource_wrapper.h>
#include <resources/image.h>
#include <resources/shader.h>
#include <memory>

namespace aeon
{
namespace resources
{

class material : public resource
{
public:
    explicit material(resource_wrapper_ptr wrapper, shader_ptr shader, image_ptr texture);
    virtual ~material() = default;

    shader_ptr get_shader() const
    {
        return shader_;
    }

    image_ptr get_texture() const
    {
        return texture_;
    }

    material_resource_wrapper_ptr get_material_resource_wrapper()
    {
        return std::dynamic_pointer_cast<material_resource_wrapper>(get_resource_wrapper());
    }

private:
    shader_ptr shader_;
    image_ptr texture_;
};

using material_ptr = std::shared_ptr<material>;

} // namespace resources
} // namespace aeon
