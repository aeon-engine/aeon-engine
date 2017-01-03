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

#include <aeon/resources/wrappers/image_resource_wrapper.h>
#include <aeon/resources/image.h>
#include <aeon/common/cached_object.h>
#include <glm/vec2.hpp>
#include <memory>

namespace aeon
{
namespace gfx
{

class texture : public common::cached_object
{
public:
    explicit texture() = default;
    virtual ~texture() = default;

    virtual glm::vec2 get_size() const = 0;
};

} // namespace gfx
} // namespace aeon
