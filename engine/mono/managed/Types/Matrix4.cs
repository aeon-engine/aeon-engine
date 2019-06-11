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

using System;
using AeonEngineMono.Core;

namespace AeonEngineMono.Types
{
    public struct Matrix4
    {
        public float m00 { get; set; }
        public float m10 { get; set; }
        public float m20 { get; set; }
        public float m30 { get; set; }
        public float m01 { get; set; }
        public float m11 { get; set; }
        public float m21 { get; set; }
        public float m31 { get; set; }
        public float m02 { get; set; }
        public float m12 { get; set; }
        public float m22 { get; set; }
        public float m32 { get; set; }
        public float m03 { get; set; }
        public float m13 { get; set; }
        public float m23 { get; set; }
        public float m33 { get; set; }

        public float this[int row, int column]
        {
            get { return this[row + (column * 4)]; }
            set { this[row + (column * 4)] = value; }
        }

        public float this[int index]
        {
            get
            {
                switch (index)
                {
                    case 0:
                        return this.m00;
                    case 1:
                        return this.m10;
                    case 2:
                        return this.m20;
                    case 3:
                        return this.m30;
                    case 4:
                        return this.m01;
                    case 5:
                        return this.m11;
                    case 6:
                        return this.m21;
                    case 7:
                        return this.m31;
                    case 8:
                        return this.m02;
                    case 9:
                        return this.m12;
                    case 10:
                        return this.m22;
                    case 11:
                        return this.m32;
                    case 12:
                        return this.m03;
                    case 13:
                        return this.m13;
                    case 14:
                        return this.m23;
                    case 15:
                        return this.m33;
                    default:
                        throw new IndexOutOfRangeException("Index out of range.");
                }
            }
            set
            {
                switch (index)
                {
                    case 0:
                        this.m00 = value;
                        break;
                    case 1:
                        this.m10 = value;
                        break;
                    case 2:
                        this.m20 = value;
                        break;
                    case 3:
                        this.m30 = value;
                        break;
                    case 4:
                        this.m01 = value;
                        break;
                    case 5:
                        this.m11 = value;
                        break;
                    case 6:
                        this.m21 = value;
                        break;
                    case 7:
                        this.m31 = value;
                        break;
                    case 8:
                        this.m02 = value;
                        break;
                    case 9:
                        this.m12 = value;
                        break;
                    case 10:
                        this.m22 = value;
                        break;
                    case 11:
                        this.m32 = value;
                        break;
                    case 12:
                        this.m03 = value;
                        break;
                    case 13:
                        this.m13 = value;
                        break;
                    case 14:
                        this.m23 = value;
                        break;
                    case 15:
                        this.m33 = value;
                        break;
                    default:
                        throw new IndexOutOfRangeException("Index out of range.");
                }
            }
        }

        public static Matrix4 Zero
        {
            get
            {
                return new Matrix4
                {
                    m00 = 0f,
                    m01 = 0f,
                    m02 = 0f,
                    m03 = 0f,

                    m10 = 0f,
                    m11 = 0f,
                    m12 = 0f,
                    m13 = 0f,

                    m20 = 0f,
                    m21 = 0f,
                    m22 = 0f,
                    m23 = 0f,

                    m30 = 0f,
                    m31 = 0f,
                    m32 = 0f,
                    m33 = 0f
                };
            }
        }

        public static Matrix4 Identity
        {
            get
            {
                return new Matrix4
                {
                    m00 = 1f,
                    m01 = 0f,
                    m02 = 0f,
                    m03 = 0f,

                    m10 = 0f,
                    m11 = 1f,
                    m12 = 0f,
                    m13 = 0f,

                    m20 = 0f,
                    m21 = 0f,
                    m22 = 1f,
                    m23 = 0f,

                    m30 = 0f,
                    m31 = 0f,
                    m32 = 0f,
                    m33 = 1f
                };
            }
        }

        public static Matrix4 operator *(Matrix4 lhs, Matrix4 rhs)
        {
            return new Matrix4
            {
                m00 = (lhs.m00 * rhs.m00) + (lhs.m01 * rhs.m10) + (lhs.m02 * rhs.m20) + (lhs.m03 * rhs.m30),
                m01 = (lhs.m00 * rhs.m01) + (lhs.m01 * rhs.m11) + (lhs.m02 * rhs.m21) + (lhs.m03 * rhs.m31),
                m02 = (lhs.m00 * rhs.m02) + (lhs.m01 * rhs.m12) + (lhs.m02 * rhs.m22) + (lhs.m03 * rhs.m32),
                m03 = (lhs.m00 * rhs.m03) + (lhs.m01 * rhs.m13) + (lhs.m02 * rhs.m23) + (lhs.m03 * rhs.m33),
                m10 = (lhs.m10 * rhs.m00) + (lhs.m11 * rhs.m10) + (lhs.m12 * rhs.m20) + (lhs.m13 * rhs.m30),
                m11 = (lhs.m10 * rhs.m01) + (lhs.m11 * rhs.m11) + (lhs.m12 * rhs.m21) + (lhs.m13 * rhs.m31),
                m12 = (lhs.m10 * rhs.m02) + (lhs.m11 * rhs.m12) + (lhs.m12 * rhs.m22) + (lhs.m13 * rhs.m32),
                m13 = (lhs.m10 * rhs.m03) + (lhs.m11 * rhs.m13) + (lhs.m12 * rhs.m23) + (lhs.m13 * rhs.m33),
                m20 = (lhs.m20 * rhs.m00) + (lhs.m21 * rhs.m10) + (lhs.m22 * rhs.m20) + (lhs.m23 * rhs.m30),
                m21 = (lhs.m20 * rhs.m01) + (lhs.m21 * rhs.m11) + (lhs.m22 * rhs.m21) + (lhs.m23 * rhs.m31),
                m22 = (lhs.m20 * rhs.m02) + (lhs.m21 * rhs.m12) + (lhs.m22 * rhs.m22) + (lhs.m23 * rhs.m32),
                m23 = (lhs.m20 * rhs.m03) + (lhs.m21 * rhs.m13) + (lhs.m22 * rhs.m23) + (lhs.m23 * rhs.m33),
                m30 = (lhs.m30 * rhs.m00) + (lhs.m31 * rhs.m10) + (lhs.m32 * rhs.m20) + (lhs.m33 * rhs.m30),
                m31 = (lhs.m30 * rhs.m01) + (lhs.m31 * rhs.m11) + (lhs.m32 * rhs.m21) + (lhs.m33 * rhs.m31),
                m32 = (lhs.m30 * rhs.m02) + (lhs.m31 * rhs.m12) + (lhs.m32 * rhs.m22) + (lhs.m33 * rhs.m32),
                m33 = (lhs.m30 * rhs.m03) + (lhs.m31 * rhs.m13) + (lhs.m32 * rhs.m23) + (lhs.m33 * rhs.m33)
            };
        }

        public static Vector4f operator *(Matrix4 lhs, Vector4f rhs)
        {
            Vector4f result = new Vector4f();
            result.x = (lhs.m00 * rhs.x) + (lhs.m01 * rhs.y) + (lhs.m02 * rhs.z) + (lhs.m03 * rhs.w);
            result.y = (lhs.m10 * rhs.x) + (lhs.m11 * rhs.y) + (lhs.m12 * rhs.z) + (lhs.m13 * rhs.w);
            result.z = (lhs.m20 * rhs.x) + (lhs.m21 * rhs.y) + (lhs.m22 * rhs.z) + (lhs.m23 * rhs.w);
            result.w = (lhs.m30 * rhs.x) + (lhs.m31 * rhs.y) + (lhs.m32 * rhs.z) + (lhs.m33 * rhs.w);
            return result;
        }

        public Vector4f GetColumn(int index)
        {
            return new Vector4f(
                this[0, index],
                this[1, index],
                this[2, index],
                this[3, index]);
        }

        public Vector4f GetRow(int index)
        {
            return new Vector4f(
                this[index, 0], 
                this[index, 1],
                this[index, 2],
                this[index, 3]);
        }

        public void SetColumn(int index, Vector4f columnVector)
        {
            this[0, index] = columnVector.x;
            this[1, index] = columnVector.y;
            this[2, index] = columnVector.z;
            this[3, index] = columnVector.w;
        }

        public void SetRow(int index, Vector4f columnVector)
        {
            this[index, 0] = columnVector.x;
            this[index, 1] = columnVector.y;
            this[index, 2] = columnVector.z;
            this[index, 3] = columnVector.w;
        }

        public static Matrix4 Scale(Vector3f value)
        {
            return new Matrix4
            {
                m00 = value.x,
                m01 = 0f,
                m02 = 0f,
                m03 = 0f,

                m10 = 0f,
                m11 = value.y,
                m12 = 0f,
                m13 = 0f,

                m20 = 0f,
                m21 = 0f,
                m22 = value.z,
                m23 = 0f,

                m30 = 0f,
                m31 = 0f,
                m32 = 0f,
                m33 = 1f
            };
        }

        public static Matrix4 Translate(Vector3f value)
        {
            return new Matrix4
            {
                m00 = 1f,
                m01 = 0f,
                m02 = 0f,
                m03 = value.x,

                m10 = 0f,
                m11 = 1f,
                m12 = 0f,
                m13 = value.y,

                m20 = 0f,
                m21 = 0f,
                m22 = 1f,
                m23 = value.z,

                m30 = 0f,
                m31 = 0f,
                m32 = 0f,
                m33 = 1f
            };
        }

        public static Matrix4 Rotate(float angle, Vector3f v)
        {
            var c = Mathf.Cos(angle);
            var s = Mathf.Sin(angle);
            var axis = v.Normalized;

            return new Matrix4
            {
                m00 = c + (1f - c) * axis.x * axis.x,
                m01 = (1f - c) * axis.x * axis.y + s * axis.z,
                m02 = (1f - c) * axis.x * axis.z - s * axis.y,
                m03 = 0f,

                m10 = (1f - c) * axis.y * axis.x - s * axis.z,
                m11 = c + (1f - c) * axis.y * axis.y,
                m12 = (1f - c) * axis.y * axis.z + s * axis.x,
                m13 = 0f,

                m20 = (1f - c) * axis.z * axis.x + s * axis.y,
                m21 = (1f - c) * axis.z * axis.y - s * axis.x,
                m22 = c + (1f - c) * axis.z * axis.z,
                m23 = 0f,

                m30 = 0f,
                m31 = 0f,
                m32 = 0f,
                m33 = 1f
            };
        }

        public static Matrix4 Ortho(float left, float right, float bottom, float top)
        {
            return new Matrix4
            {
                m00 = 2f / (right - left),
                m01 = 0f,
                m02 = 0f,
                m03 = 0f,

                m10 = 0f,
                m11 = 2f / (top - bottom),
                m12 = 0f,
                m13 = 0f,

                m20 = 0f,
                m21 = 0f,
                m22 = -1f,
                m23 = 0f,

                m30 = -(right + left) / (right - left),
                m31 = -(top + bottom) / (top - bottom),
                m32 = 0f,
                m33 = 1f
            };
        }

        public static Matrix4 Ortho(float left, float right, float bottom, float top, float near, float far)
        {
            return new Matrix4
            {
                m00 = 2f / (right - left),
                m01 = 0f,
                m02 = 0f,
                m03 = 0f,

                m10 = 0f,
                m11 = 2f / (top - bottom),
                m12 = 0f,
                m13 = 0f,

                m20 = 0f,
                m21 = 0f,
                m22 = -2f / (far - near),
                m23 = 0f,

                m30 = -(right + left) / (right - left),
                m31 = -(top + bottom) / (top - bottom),
                m32 = -(far + near) / (far - near),
                m33 = 1f
            };
        }

        public static Matrix4 Projection(float fovY, float aspectRatio, float near, float far)
        {
            var tanHalfFovY = Mathf.Tan(fovY / 2f);

            return new Matrix4
            {
                m00 = 1f / (aspectRatio * tanHalfFovY),
                m01 = 0f,
                m02 = 0f,
                m03 = 0f,

                m10 = 0f,
                m11 = 1f / tanHalfFovY,
                m12 = 0f,
                m13 = 0f,

                m20 = 0f,
                m21 = 0f,
                m22 = -(far + near) / (far - near),
                m23 = 1f,

                m30 = 0f,
                m31 = 0f,
                m32 = -(2f * far * near) / (far - near),
                m33 = 1f
            };
        }

        public static Matrix4 ProjectionFov(float fov, float width, float height, float near, float far)
        {
            var h = Mathf.Cos(0.5f * fov) / Mathf.Sin(0.5f * fov);
            var w = h * height / width;

            return new Matrix4
            {
                m00 = w,
                m01 = 0f,
                m02 = 0f,
                m03 = 0f,

                m10 = 0f,
                m11 = h,
                m12 = 0f,
                m13 = 0f,

                m20 = 0f,
                m21 = 0f,
                m22 = -(far + near) / (far - near),
                m23 = -1f,

                m30 = 0f,
                m31 = 0f,
                m32 = -(2f * far * near) / (far - near),
                m33 = 1f
            };
        }

        public override bool Equals(object obj)
        {
            if (!(obj is Matrix4))
            {
                return false;
            }

            var matrix = (Matrix4)obj;
            return m00 == matrix.m00 &&
                   m10 == matrix.m10 &&
                   m20 == matrix.m20 &&
                   m30 == matrix.m30 &&
                   m01 == matrix.m01 &&
                   m11 == matrix.m11 &&
                   m21 == matrix.m21 &&
                   m31 == matrix.m31 &&
                   m02 == matrix.m02 &&
                   m12 == matrix.m12 &&
                   m22 == matrix.m22 &&
                   m32 == matrix.m32 &&
                   m03 == matrix.m03 &&
                   m13 == matrix.m13 &&
                   m23 == matrix.m23 &&
                   m33 == matrix.m33;
        }

        public override int GetHashCode()
        {
            var hashCode = 1830880184;
            hashCode = hashCode * -1521134295 + m00.GetHashCode();
            hashCode = hashCode * -1521134295 + m10.GetHashCode();
            hashCode = hashCode * -1521134295 + m20.GetHashCode();
            hashCode = hashCode * -1521134295 + m30.GetHashCode();
            hashCode = hashCode * -1521134295 + m01.GetHashCode();
            hashCode = hashCode * -1521134295 + m11.GetHashCode();
            hashCode = hashCode * -1521134295 + m21.GetHashCode();
            hashCode = hashCode * -1521134295 + m31.GetHashCode();
            hashCode = hashCode * -1521134295 + m02.GetHashCode();
            hashCode = hashCode * -1521134295 + m12.GetHashCode();
            hashCode = hashCode * -1521134295 + m22.GetHashCode();
            hashCode = hashCode * -1521134295 + m32.GetHashCode();
            hashCode = hashCode * -1521134295 + m03.GetHashCode();
            hashCode = hashCode * -1521134295 + m13.GetHashCode();
            hashCode = hashCode * -1521134295 + m23.GetHashCode();
            hashCode = hashCode * -1521134295 + m33.GetHashCode();
            return hashCode;
        }
    }
}
