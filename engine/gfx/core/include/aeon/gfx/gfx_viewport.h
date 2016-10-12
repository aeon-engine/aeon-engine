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

#include <aeon/common/types/rectangle.h>
#include <aeon/common/has_z_order.h>
#include <aeon/gfx/gfx_camera.h>
#include <memory>

namespace aeon
{
namespace gfx
{

class viewport : public common::has_z_order
{
public:
    explicit viewport(gfx::gfx_camera_ptr camera, const common::types::rectangle<float> &rect, int zorder);
    virtual ~viewport() = default;

    void set_rectangle(const common::types::rectangle<float> &rect);

    void set_camera(gfx::gfx_camera_ptr camera);
    gfx::gfx_camera_ptr get_camera() const;

    void update(float dt);

    common::types::rectangle<float> get_rectangle() const;

private:
    gfx::gfx_camera_ptr camera_;
    common::types::rectangle<float> rectangle_;
};

using viewport_ptr = std::shared_ptr<viewport>;

} // namespace gfx
} // namespace aeon
