/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2015 Robin Degen
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

#include <resources/wrappers/image_resource_wrapper.h>
#include <resources/image.h>
#include <common/cached_object.h>
#include <glm/vec2.hpp>
#include <memory>

namespace aeon
{
namespace gfx
{

class texture : public common::cached_object
{
public:
    explicit texture(resources::image_ptr image);
    virtual ~texture();

    virtual void bind() = 0;

    glm::vec2 get_size() const;

protected:
    glm::vec2 size_;

private:
    /* Object that points to the image resource for this texture. This object does
     * not actually contain any resource data.
     */
    resources::image_resource_wrapper_ptr image_wrapper_;
};

using texture_ptr = std::shared_ptr<texture>;

} // namespace gfx
} // namespace aeon
