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

#include <aeon/scene/camera.h>
#include <memory>

namespace aeon
{
namespace scene
{

class orthographic_camera : public camera
{
public:
    explicit orthographic_camera(scene_manager *scene_manager, const float left, const float right, const float bottom,
                                 const float top, const std::string &name = "");
    explicit orthographic_camera(scene_manager *scene_manager, const float left, const float right, const float bottom,
                                 const float top, const float near, const float far, const std::string &name = "");

    explicit orthographic_camera(scene_manager *scene_manager, const int left, const int right, const int bottom,
                                 const int top, const std::string &name = "");
    explicit orthographic_camera(scene_manager *scene_manager, const int left, const int right, const int bottom,
                                 const int top, const float near, const float far, const std::string &name = "");

    virtual ~orthographic_camera() = default;
};

} // namespace scene
} // namespace aeon
