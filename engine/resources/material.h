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
#include <resources/wrappers/image_resource_wrapper.h>
#include <common/buffer.h>
#include <memory>

namespace aeon
{
namespace resources
{

class material : public resource
{
public:
    explicit material(resource_wrapper_ptr wrapper);
    virtual ~material() = default;

    void set_texture_data(image_ptr image);

    image_ptr get_texture()
    {
        return texture_;
    }

private:
    image_ptr texture_;
};

using material_ptr = std::shared_ptr<material>;

} // namespace resources
} // namespace aeon