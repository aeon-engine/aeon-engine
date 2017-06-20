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

#include <managed_interface/core/object.h>
#include <managed_interface/core/types.h>
#include <managed_interface/assets/atlas.h>
#include <managed_interface/scene/animated_sprite_settings.h>
#include <aeon/scene/components/animated_sprite.h>

namespace aeon
{
namespace mono
{

register_basic_mono_converter_for_wrapper(std::shared_ptr<scene::animated_sprite>);

namespace managed_interface
{

class animated_sprite
{
public:
    static void register_internal_calls();

private:
    static void ctor(MonoObject *this_ptr, std::shared_ptr<gfx::atlas> atlas, int z_order,
                     std::shared_ptr<scene::sprite_animation_settings> settings, std::string name);
    static void run(std::shared_ptr<scene::animated_sprite> this_ptr);
    static void stop(std::shared_ptr<scene::animated_sprite> this_ptr);
    static void set_animation_sequence(std::shared_ptr<scene::animated_sprite> this_ptr, int index);
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
