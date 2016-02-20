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
#include <resources/wrappers/shader_resource_wrapper.h>
#include <common/buffer.h>
#include <common/logger.h>
#include <memory>

namespace aeon
{
namespace resources
{

class shader : public resource
{
public:
    explicit shader(resource_wrapper_ptr wrapper, const std::string &vertex_source, const std::string &fragment_source);
    virtual ~shader();

    shader_resource_wrapper_ptr get_material_resource_wrapper()
    {
        return std::dynamic_pointer_cast<shader_resource_wrapper>(get_resource_wrapper());
    }

    std::string get_vertex_source() const
    {
        return vertex_source_;
    }

    std::string get_fragment_source() const
    {
        return fragment_source_;
    }

private:
    aeon::logger::logger logger_;
    std::string vertex_source_;
    std::string fragment_source_;
};

using shader_ptr = std::shared_ptr<shader>;

} // namespace resources
} // namespace aeon
