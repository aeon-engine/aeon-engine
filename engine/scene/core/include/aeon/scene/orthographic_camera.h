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

#include <aeon/scene/camera.h>
#include <memory>

namespace aeon
{
namespace scene
{

class orthographic_camera : public camera
{
public:
    explicit orthographic_camera(scene_manager *scene_manager, float left, float right, float bottom, float top);
    explicit orthographic_camera(scene_manager *scene_manager, float left, float right, float bottom, float top,
                                 float near, float far);

    explicit orthographic_camera(scene_manager *scene_manager, int left, int right, int bottom, int top);
    explicit orthographic_camera(scene_manager *scene_manager, int left, int right, int bottom, int top, float near,
                                 float far);

    virtual ~orthographic_camera() = default;
};

} // namespace scene
} // namespace aeon
