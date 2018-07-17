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

#pragma once

#include <aeon/mono/mono_type_conversion.h>
#include <managed_interface/core/types.h>
#include <aeon/common/types/rectangle.h>
#include <aeon/math/vector2.h>
#include <aeon/math/vector3.h>
#include <aeon/math/mat4.h>
#include <aeon/math/quaternion.h>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

#define add_mono_type_converter(cpp_type, mono_type)                                                                   \
                                                                                                                       \
    template <>                                                                                                        \
                                                                                                                       \
    struct convert_mono_type<cpp_type>                                                                                 \
                                                                                                                       \
    {                                                                                                                  \
        using mono_type_name = mono_type;                                                                              \
                                                                                                                       \
        static auto to_mono(mono_assembly &assembly, cpp_type val) -> mono_type                                        \
        {                                                                                                              \
            return managed_interface::converter::convert(val);                                                         \
        }                                                                                                              \
                                                                                                                       \
        static auto from_mono(mono_type val) -> cpp_type                                                               \
        {                                                                                                              \
            return managed_interface::converter::convert(val);                                                         \
        }                                                                                                              \
    }

struct converter
{
    // From Mono
    static auto convert(const rect &r) -> common::types::rectangle<float>;
    static auto convert(const vector2f &vec) -> math::vector2<float>;
    static auto convert(const vector3f &vec) -> math::vector3<float>;
    static auto convert(const quaternion &quat) -> math::quaternion;
    static auto convert(const matrix4x4 &mat) -> math::mat4;

    // To Mono
    static auto convert(const common::types::rectangle<float> &r) -> rect;
    static auto convert(const math::vector2<float> &vec) -> vector2f;
    static auto convert(const math::vector3<float> &vec) -> vector3f;
    static auto convert(const math::quaternion &quat) -> quaternion;
    static auto convert(const math::mat4 &m) -> matrix4x4;
};

///////////////////////////////////////////////////////////////////////////////

inline auto converter::convert(const rect &r) -> common::types::rectangle<float>
{
    return {r.left, r.top, r.right, r.bottom};
}

inline auto converter::convert(const vector2f &vec) -> math::vector2<float>
{
    return {vec.x, vec.y};
}

inline auto converter::convert(const vector3f &vec) -> math::vector3<float>
{
    return {vec.x, vec.y, vec.z};
}

inline auto converter::convert(const quaternion &quat) -> math::quaternion
{
    return {quat.w, quat.x, quat.y, quat.z};
}

inline auto converter::convert(const matrix4x4 &mat) -> math::mat4
{
    math::mat4 m;
    m[0][0] = mat.m00;
    m[0][1] = mat.m01;
    m[0][2] = mat.m02;
    m[0][3] = mat.m03;

    m[1][0] = mat.m10;
    m[1][1] = mat.m11;
    m[1][2] = mat.m12;
    m[1][3] = mat.m13;

    m[2][0] = mat.m20;
    m[2][1] = mat.m21;
    m[2][2] = mat.m22;
    m[2][3] = mat.m23;

    m[3][0] = mat.m30;
    m[3][1] = mat.m31;
    m[3][2] = mat.m32;
    m[3][3] = mat.m33;
    return m;
}

///////////////////////////////////////////////////////////////////////////////

inline auto converter::convert(const common::types::rectangle<float> &r) -> rect
{
    return {r.left(), r.top(), r.right(), r.bottom()};
}

inline auto converter::convert(const math::vector2<float> &vec) -> vector2f
{
    return {vec.x, vec.y};
}

inline auto converter::convert(const math::vector3<float> &vec) -> vector3f
{
    return {vec.x, vec.y, vec.z};
}

inline auto converter::convert(const math::quaternion &quat) -> quaternion
{
    return {quat.w, quat.x, quat.y, quat.z};
}

inline auto converter::convert(const math::mat4 &m) -> matrix4x4
{
    return {m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]};
}

} // namespace managed_interface

add_mono_type_converter(common::types::rectangle<float>, managed_interface::rect);
add_mono_type_converter(math::vector2<float>, managed_interface::vector2f);
add_mono_type_converter(math::vector3<float>, managed_interface::vector3f);
add_mono_type_converter(math::quaternion, managed_interface::quaternion);
add_mono_type_converter(math::mat4, managed_interface::matrix4x4);

} // namespace mono
} // namespace aeon
