/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/scene/camera.h>

namespace aeon
{
namespace scene
{

class orthographic_camera : public camera
{
public:
    explicit orthographic_camera(scene_manager &scene_manager, const float left, const float right, const float bottom,
                                 const float top, const std::string &name = "");
    explicit orthographic_camera(scene_manager &scene_manager, const float left, const float right, const float bottom,
                                 const float top, const float near, const float far, const std::string &name = "");

    explicit orthographic_camera(scene_manager &scene_manager, const int left, const int right, const int bottom,
                                 const int top, const std::string &name = "");
    explicit orthographic_camera(scene_manager &scene_manager, const int left, const int right, const int bottom,
                                 const int top, const float near, const float far, const std::string &name = "");

    virtual ~orthographic_camera() = default;
};

} // namespace scene
} // namespace aeon
