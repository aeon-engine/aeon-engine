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

#include <managed_interface/scene/camera.h>
#include <managed_interface/core/types.h>
#include <mono/metadata/object.h>
#include <aeon/gfx/gfx_viewport.h>
#include <memory>

namespace aeon
{
namespace mono
{

register_basic_mono_converter_for_wrapper(std::shared_ptr<gfx::viewport>);

namespace managed_interface
{

class viewport
{
public:
    static void register_internal_calls();

private:
    static void create_internal(MonoObject *this_ptr, std::shared_ptr<scene::camera> camera, std::string name,
                                int zOrder);
    static void create_internal2(MonoObject *this_ptr, std::shared_ptr<scene::camera> camera,
                                 common::types::rectangle<float> rectangle, std::string name, int zOrder);
    static void set_zorder(std::shared_ptr<gfx::viewport> this_ptr, int value);
    static int get_zorder(std::shared_ptr<gfx::viewport> this_ptr);
    static void set_camera_internal(std::shared_ptr<gfx::viewport> this_ptr, std::shared_ptr<scene::camera> camera);
    static void set_rectangle_internal(std::shared_ptr<gfx::viewport> this_ptr,
                                       common::types::rectangle<float> rectangle);
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
