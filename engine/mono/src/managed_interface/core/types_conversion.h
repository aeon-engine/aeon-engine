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

#include <aeon/mono/mono_type_conversion.h>
#include <managed_interface/core/types.h>
#include <aeon/common/types/rectangle.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>

namespace aeon
{
namespace mono
{
namespace managed_interface
{

#define add_mono_type_converter(cpp_type, mono_type)                                                                   \
    \
template<>                                                                                                             \
        \
struct convert_mono_type<cpp_type>                                                                                     \
    \
{                                                                                                               \
        using mono_type_name = mono_type;                                                                              \
                                                                                                                       \
        static auto to_mono(mono_assembly &assembly, cpp_type val)->mono_type                                          \
        {                                                                                                              \
            return managed_interface::converter::convert(val);                                                         \
        }                                                                                                              \
                                                                                                                       \
        static auto from_mono(mono_type val)->cpp_type                                                                 \
        {                                                                                                              \
            return managed_interface::converter::convert(val);                                                         \
        }                                                                                                              \
    \
}

struct converter
{
    // From Mono
    static auto convert(const rect &r) -> common::types::rectangle<float>;
    static auto convert(const vector2f &vec) -> glm::vec2;
    static auto convert(const vector3f &vec) -> glm::vec3;
    static auto convert(const quaternion &quat) -> glm::quat;
    static auto convert(const matrix4x4 &mat) -> glm::mat4x4;

    // To Mono
    static auto convert(const common::types::rectangle<float> &r) -> rect;
    static auto convert(const glm::vec2 &vec) -> vector2f;
    static auto convert(const glm::vec3 &vec) -> vector3f;
    static auto convert(const glm::quat &quat) -> quaternion;
    static auto convert(const glm::mat4x4 &m) -> matrix4x4;
};

///////////////////////////////////////////////////////////////////////////////

inline auto converter::convert(const rect &r) -> common::types::rectangle<float>
{
    return {r.left, r.top, r.right, r.bottom};
}

inline auto converter::convert(const vector2f &vec) -> glm::vec2
{
    return {vec.x, vec.y};
}

inline auto converter::convert(const vector3f &vec) -> glm::vec3
{
    return {vec.x, vec.y, vec.z};
}

inline auto converter::convert(const quaternion &quat) -> glm::quat
{
    return {quat.w, quat.x, quat.y, quat.z};
}

inline auto converter::convert(const matrix4x4 &mat) -> glm::mat4x4
{
    glm::mat4x4 m;
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

inline auto converter::convert(const glm::vec2 &vec) -> vector2f
{
    return {vec.x, vec.y};
}

inline auto converter::convert(const glm::vec3 &vec) -> vector3f
{
    return {vec.x, vec.y, vec.z};
}

inline auto converter::convert(const glm::quat &quat) -> quaternion
{
    return {quat.w, quat.x, quat.y, quat.z};
}

inline auto converter::convert(const glm::mat4x4 &m) -> matrix4x4
{
    return {m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]};
}

} // namespace managed_interface

add_mono_type_converter(common::types::rectangle<float>, managed_interface::rect);
add_mono_type_converter(glm::vec2, managed_interface::vector2f);
add_mono_type_converter(glm::vec3, managed_interface::vector3f);
add_mono_type_converter(glm::quat, managed_interface::quaternion);
add_mono_type_converter(glm::mat4x4, managed_interface::matrix4x4);

} // namespace mono
} // namespace aeon
