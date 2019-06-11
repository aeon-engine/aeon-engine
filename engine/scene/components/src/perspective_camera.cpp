/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/scene/components/perspective_camera.h>
#include <aeon/math/mat4.h>
#include <aeon/math/math.h>
#include <aeon/math/units.h>

namespace aeon::scene
{

perspective_camera::perspective_camera(scene_manager &scene_manager, const float fov_y, const float aspect_ratio,
                                       const float near, const float far, const std::string &name)
    : camera(name, scene_manager)
{
    projection_matrix_ = math::mat4::projection(math::unitf<math::degree>{fov_y}, aspect_ratio, near, far);
}

perspective_camera::perspective_camera(scene_manager &scene_manager, const float fov, const float width,
                                       const float height, const float near, const float far, const std::string &name)
    : camera(name, scene_manager)
{
    projection_matrix_ = math::mat4::projection_fov(fov, width, height, near, far);
}
} // namespace aeon::scene
