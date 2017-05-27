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

#include <managed_interface/Sprite.h>
#include <managed_interface/Types.h>
#include <aeon/mono/mono_jit.h>
#include <memory>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

static void Sprite_Ctor(MonoObject *this_ptr)
{
    std::make_unique<Sprite>(this_ptr).release();
}

static void Sprite_set_Size(MonoObject *this_ptr, Vector2F value)
{
    Object::get_managed_object_as<Sprite>(this_ptr).set_Size({value.x, value.y});
}

static Vector2F Sprite_get_Size(MonoObject *this_ptr)
{
    auto value = Object::get_managed_object_as<Sprite>(this_ptr).get_Size();
    return { value.x, value.y };
}

void Sprite::register_internal_calls()
{
    mono_jit::add_internal_call("Aeon.Sprite::.ctor", Sprite_Ctor);
    mono_jit::add_internal_call("Aeon.Sprite::set_Size", Sprite_set_Size);
    mono_jit::add_internal_call("Aeon.Sprite::get_Size", Sprite_get_Size);
}

Sprite::Sprite(MonoObject *object)
    : Object(object)
{
}

Sprite::~Sprite() = default;

void Sprite::set_Size(const glm::vec2 value)
{
    (void) value;
}

auto Sprite::get_Size() -> glm::vec2
{
    return {1337, 42};
}

} // namespace managed_interface
} // namespace mono
} // namespace aeon
