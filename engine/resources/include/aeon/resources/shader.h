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

#include <aeon/resources/resource.h>
#include <aeon/resources/exceptions.h>
#include <aeon/resources/wrappers/shader_resource_wrapper.h>
#include <aeon/data/shader.h>
#include <aeon/common/logger.h>
#include <memory>

namespace aeon
{
namespace resources
{

class shader : public resource
{
public:
    explicit shader(const std::shared_ptr<resource_wrapper> &wrapper, data::shader &&shader_data);
    virtual ~shader();

    auto get_material_resource_wrapper() const
    {
        return std::dynamic_pointer_cast<shader_resource_wrapper>(get_resource_wrapper());
    }

    const auto &get_data() const
    {
        return shader_data_;
    }

private:
    logger::logger logger_;
    data::shader shader_data_;
};

} // namespace resources
} // namespace aeon
