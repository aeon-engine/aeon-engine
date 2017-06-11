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
#include <aeon/scene/components/sprite_animation_settings.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

class animated_sprite_settings
{
public:
    static void register_internal_calls();

    static auto get_animated_sprite_settings_from_mono_object(MonoObject *object) -> scene::sprite_animation_settings &;

private:
    static void ctor(MonoObject *this_ptr, vector2f frame_size);
    static void generate_sequence(MonoObject *this_ptr, int index, int frame_offset, int frame_count,
                                  scene::animation_sequence_type type);
    static void set_default_sequence(MonoObject *this_ptr, int index);
    static void set_start_condition(MonoObject *this_ptr, scene::animation_start_condition condition);
    static void set_repeat(MonoObject *this_ptr, scene::animation_repeat repeat);
    static void set_speed(MonoObject *this_ptr, float speed);
};

} // namespace managed_interface
} // namespace mono
} // namespace aeon
