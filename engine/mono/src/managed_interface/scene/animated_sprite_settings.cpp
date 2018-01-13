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

#include <managed_interface/scene/animated_sprite_settings.h>
#include <managed_interface/mono_object_wrapper.h>
#include <managed_interface/core/types_conversion.h>
#include <aeon/mono/mono_jit.h>
#include <aeon/mono/mono_jit_manager.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

void animated_sprite_settings::register_internal_calls()
{
    mono_jit::add_internal_call("AeonEngineMono.Scene.SpriteAnimationSettings::.ctor(AeonEngineMono.Types.Vector2f)",
                                aeon_mono_auto_wrap(animated_sprite_settings::ctor));
    mono_jit::add_internal_call("AeonEngineMono.Scene.SpriteAnimationSettings::GenerateSequence(int,int,int,"
                                "AeonEngineMono.Scene.AnimationSequenceType)",
                                aeon_mono_auto_wrap(animated_sprite_settings::generate_sequence));
    mono_jit::add_internal_call("AeonEngineMono.Scene.SpriteAnimationSettings::set_DefaultSequence(int)",
                                aeon_mono_auto_wrap(animated_sprite_settings::set_default_sequence));
    mono_jit::add_internal_call("AeonEngineMono.Scene.SpriteAnimationSettings::set_StartCondition(AeonEngineMono.Scene."
                                "AnimationStartCondition)",
                                aeon_mono_auto_wrap(animated_sprite_settings::set_start_condition));
    mono_jit::add_internal_call(
        "AeonEngineMono.Scene.SpriteAnimationSettings::set_Repeat(AeonEngineMono.Scene.AnimationRepeat)",
        aeon_mono_auto_wrap(animated_sprite_settings::set_repeat));
    mono_jit::add_internal_call("AeonEngineMono.Scene.SpriteAnimationSettings::set_Speed(single)",
                                aeon_mono_auto_wrap(animated_sprite_settings::set_speed));
}

void animated_sprite_settings::ctor(MonoObject *this_ptr, glm::vec2 frame_size)
{
    mono_object_wrapper<std::shared_ptr<scene::sprite_animation_settings>>::create(
        this_ptr, std::make_shared<scene::sprite_animation_settings>(frame_size));
}

void animated_sprite_settings::generate_sequence(std::shared_ptr<scene::sprite_animation_settings> this_ptr, int index,
                                                 int frame_offset, int frame_count, scene::animation_sequence_type type)
{
    this_ptr->generate_sequence(index, frame_offset, frame_count, type);
}

void animated_sprite_settings::set_default_sequence(std::shared_ptr<scene::sprite_animation_settings> this_ptr,
                                                    int index)
{
    this_ptr->set_default_sequence(index);
}

void animated_sprite_settings::set_start_condition(std::shared_ptr<scene::sprite_animation_settings> this_ptr,
                                                   scene::animation_start_condition condition)
{
    this_ptr->set_start_condition(condition);
}

void animated_sprite_settings::set_repeat(std::shared_ptr<scene::sprite_animation_settings> this_ptr,
                                          scene::animation_repeat repeat)
{
    this_ptr->set_repeat(repeat);
}

void animated_sprite_settings::set_speed(std::shared_ptr<scene::sprite_animation_settings> this_ptr, float speed)
{
    this_ptr->set_speed(speed);
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
