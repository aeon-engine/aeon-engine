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

#include <scene/viewport.h>

namespace aeon
{
namespace scene
{

viewport::viewport(camera_ptr camera, const common::types::rectangle<float> &rect, int zorder)
    : camera_(camera)
    , rectangle_(rect)
    , zorder_(zorder)
{
}

viewport::~viewport()
{
}

void viewport::set_rectangle(const common::types::rectangle<float> &rect)
{
    rectangle_ = rect;
}

int viewport::get_zorder() const
{
    return zorder_;
}

void viewport::set_camera(camera_ptr camera)
{
    camera_ = camera;
}

camera_ptr viewport::get_camera() const
{
    return camera_;
}

} // namespace scene
} // namespace aeon
