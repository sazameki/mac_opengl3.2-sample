//
//  GLXMath.cpp
//
//  Created by Satoshi Numata on 12/04/11.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GLXMath.h"


vec2::vec2()
    : x(0.0), y(0.0)
{
    // Do nothing
}

vec2::vec2(const float _x, const float _y)
    : x(_x), y(_y)
{
    // Do nothing
}

vec2::vec2(const GLKVector2& vec)
    : glkVector2(vec)
{
    // Do nothing
}

vec2::vec2(const vec2& vec)
    : glkVector2(vec.glkVector2)
{
    // Do nothing
}

float vec2::dot(const vec2& v)
{
    return GLKVector2DotProduct(this->glkVector2, v.glkVector2);
}

float vec2::length() const
{
    return GLKVector2Length(this->glkVector2);
}

bool vec2::operator==(const vec2& v) const
{
    return GLKVector2AllEqualToVector2(this->glkVector2, v.glkVector2);
}

vec2& vec2::operator=(const vec2& v)
{
    glkVector2 = v.glkVector2;
    return *this;
}

vec2 vec2::operator+(const vec2& v) const
{
    return GLKVector2Add(this->glkVector2, v.glkVector2);
}

vec2 vec2::operator-(const vec2& v) const
{
    return GLKVector2Subtract(this->glkVector2, v.glkVector2);
}

vec2 vec2::operator*(const vec2& v) const
{
    return GLKVector2Multiply(this->glkVector2, v.glkVector2);
}

vec2 vec2::operator/(const vec2& v) const
{
    return GLKVector2Divide(this->glkVector2, v.glkVector2);
}

vec2 vec2::operator+(const float value) const
{
    return GLKVector2AddScalar(this->glkVector2, value);
}

vec2 vec2::operator-(const float value) const
{
    return GLKVector2SubtractScalar(this->glkVector2, value);
}

vec2 vec2::operator*(const float value) const
{
    return GLKVector2MultiplyScalar(this->glkVector2, value);
}

vec2 vec2::operator/(const float value) const
{
    return GLKVector2DivideScalar(this->glkVector2, value);
}

vec2& vec2::operator+=(const vec2& v)
{
    this->glkVector2 = GLKVector2Add(this->glkVector2, v.glkVector2);
    return *this;
}

vec2& vec2::operator-=(const vec2& v)
{
    this->glkVector2 = GLKVector2Subtract(this->glkVector2, v.glkVector2);
    return *this;
}

vec2& vec2::operator*=(const vec2& v)
{
    this->glkVector2 = GLKVector2Multiply(this->glkVector2, v.glkVector2);
    return *this;
}

vec2& vec2::operator/=(const vec2& v)
{
    this->glkVector2 = GLKVector2Divide(this->glkVector2, v.glkVector2);
    return *this;
}

vec2& vec2::operator+=(const float value)
{
    this->glkVector2 = GLKVector2AddScalar(this->glkVector2, value);
    return *this;
}

vec2& vec2::operator-=(const float value)
{
    this->glkVector2 = GLKVector2SubtractScalar(this->glkVector2, value);
    return *this;
}

vec2& vec2::operator*=(const float value)
{
    this->glkVector2 = GLKVector2MultiplyScalar(this->glkVector2, value);
    return *this;
}

vec2& vec2::operator/=(const float value)
{
    this->glkVector2 = GLKVector2DivideScalar(this->glkVector2, value);
    return *this;
}


vec3::vec3()
    : x(0.0), y(0.0), z(0.0)
{
    // Do nothing
}

vec3::vec3(const float _x, const float _y, const float _z)
    : x(_x), y(_y), z(_z)
{
    // Do nothing
}

vec3::vec3(const GLKVector3& vec)
    : glkVector3(vec)
{
    // Do nothing
}

vec3::vec3(const vec3& vec)
    : x(vec.x), y(vec.y), z(vec.z)
{
    // Do nothing
}

vec3 vec3::normalize() const
{
    return GLKVector3Normalize(this->glkVector3);
}

vec3 vec3::cross(const vec3& v) const
{
    return GLKVector3CrossProduct(this->glkVector3, v.glkVector3);
}

float vec3::dot(const vec3& v) const
{
    return GLKVector3DotProduct(this->glkVector3, v.glkVector3);
}

float vec3::length() const
{
    return GLKVector3Length(this->glkVector3);
}

bool vec3::operator==(const vec3& v) const
{
    return GLKVector3AllEqualToVector3(this->glkVector3, v.glkVector3);
}

vec3& vec3::operator=(const vec3& v)
{
    glkVector3 = v.glkVector3;
    return *this;
}

vec3 vec3::operator+(const vec3& v) const
{
    return GLKVector3Add(this->glkVector3, v.glkVector3);
}

vec3 vec3::operator-(const vec3& v) const
{
    return GLKVector3Subtract(this->glkVector3, v.glkVector3);
}

vec3 vec3::operator*(const vec3& v) const
{
    return GLKVector3Multiply(this->glkVector3, v.glkVector3);
}

vec3 vec3::operator/(const vec3& v) const
{
    return GLKVector3Divide(this->glkVector3, v.glkVector3);
}

vec3 vec3::operator+(const float value) const
{
    return GLKVector3AddScalar(this->glkVector3, value);
}

vec3 vec3::operator-(const float value) const
{
    return GLKVector3SubtractScalar(this->glkVector3, value);
}

vec3 vec3::operator*(const float value) const
{
    return GLKVector3MultiplyScalar(this->glkVector3, value);
}

vec3 vec3::operator/(const float value) const
{
    return GLKVector3DivideScalar(this->glkVector3, value);
}

vec3& vec3::operator+=(const vec3& v)
{
    this->glkVector3 = GLKVector3Add(this->glkVector3, v.glkVector3);
    return *this;
}

vec3& vec3::operator-=(const vec3& v)
{
    this->glkVector3 = GLKVector3Subtract(this->glkVector3, v.glkVector3);
    return *this;
}

vec3& vec3::operator*=(const vec3& v)
{
    this->glkVector3 = GLKVector3Multiply(this->glkVector3, v.glkVector3);
    return *this;
}

vec3& vec3::operator/=(const vec3& v)
{
    this->glkVector3 = GLKVector3Divide(this->glkVector3, v.glkVector3);
    return *this;
}

vec3& vec3::operator+=(const float value)
{
    this->glkVector3 = GLKVector3AddScalar(this->glkVector3, value);
    return *this;
}

vec3& vec3::operator-=(const float value)
{
    this->glkVector3 = GLKVector3SubtractScalar(this->glkVector3, value);
    return *this;
}

vec3& vec3::operator*=(const float value)
{
    this->glkVector3 = GLKVector3MultiplyScalar(this->glkVector3, value);
    return *this;
}

vec3& vec3::operator/=(const float value)
{
    this->glkVector3 = GLKVector3DivideScalar(this->glkVector3, value);
    return *this;
}


mat3::mat3(float value)
{
    m00 = m11 = m22 = value;
    m01 = m02 = 0.0f;
    m10 = m12 = 0.0f;
    m20 = m21 = 0.0f;
}

mat3::mat3(const mat4& matrix)
{
    m00 = matrix.m00;
    m01 = matrix.m01;
    m02 = matrix.m02;
    m10 = matrix.m10;
    m11 = matrix.m11;
    m12 = matrix.m12;
    m20 = matrix.m20;
    m21 = matrix.m21;
    m22 = matrix.m22;
}

mat3::mat3(const GLKMatrix3& matrix)
    : glkMatrix3(matrix)
{
    // Do nothing
}

mat3 mat3::invert() const
{
    return GLKMatrix3Invert(glkMatrix3);
}


mat4::mat4(float value)
{
    m00 = m11 = m22 = m33 = value;
    m01 = m02 = m03 = 0.0f;
    m10 = m12 = m13 = 0.0f;
    m20 = m21 = m23 = 0.0f;
    m30 = m31 = m32 = 0.0f;
}

mat4::mat4(const GLKMatrix4& matrix)
    : glkMatrix4(matrix)
{
    // Do nothing
}

mat4 mat4::MakePerspective(float fovyRadians, float aspect, float nearZ, float farZ)
{
    return GLKMatrix4MakePerspective(fovyRadians, aspect, nearZ, farZ);
}

mat4 mat4::MakeLookAt(const vec3& eye, const vec3& target, const vec3& up)
{
    return GLKMatrix4MakeLookAt(eye.x, eye.y, eye.z, target.x, target.y, target.z, up.x, up.y, up.z);
}

mat4 mat4::rotate(float rotationInRadian, const vec3& axis) const
{
    return GLKMatrix4Rotate(glkMatrix4, rotationInRadian, axis.x, axis.y, axis.z);
}

mat4 mat4::scale(const vec3& vec) const
{
    return GLKMatrix4Scale(glkMatrix4, vec.x, vec.y, vec.z);
}

mat4 mat4::translate(const vec3& vec) const
{
    return GLKMatrix4Translate(glkMatrix4, vec.x, vec.y, vec.z);
}

mat4 mat4::operator*(const mat4& m) const
{
    return GLKMatrix4Multiply(glkMatrix4, m.glkMatrix4);
}


const mat4 mat4::Identity = mat4(1.0f);

