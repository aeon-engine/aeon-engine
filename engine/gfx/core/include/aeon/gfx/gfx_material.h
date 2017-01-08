/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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
#include <aeon/common/exception.h>
#include <memory>
#include <string>
#include <map>

namespace aeon
{
namespace gfx
{

DEFINE_EXCEPTION_OBJECT(gfx_material_exception, aeon::common::exception, "Material exception.");

class shader;
class texture;
class material : public common::cached_object
{
public:
    material() = default;
    virtual ~material() = default;

    virtual void bind() = 0;

    virtual shader *get_shader() const = 0;
    virtual texture *get_sampler(const std::string &name) const = 0;

    /*!
     * Returns true if any of the samplers in this material has an alpha channel.
     */
    virtual bool sampler_has_alpha() const = 0;
};

} // namespace gfx
} // namespace aeon
