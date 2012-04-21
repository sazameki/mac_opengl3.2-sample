//
//  GLXMath.h
//
//  Created by Satoshi Numata on 12/04/11.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//


#ifndef __GLX_MATH_H__
#define __GLX_MATH_H__

#import "GLKMath.h"


struct vec2 {
    union {
        GLKVector2  glkVector2;
        struct { float x, y; };
        struct { float s, t; };
        float       v[2];
    };
    
public:
    vec2();
    vec2(const float x, const float y);
    vec2(const GLKVector2& vec);
    vec2(const vec2& vec);
    
public:
    float   dot(const vec2& v);
    float   length() const;

public:
    bool    operator==(const vec2& v) const;

    vec2&   operator=(const vec2& v);
    
    vec2    operator+(const vec2& v) const;
    vec2    operator-(const vec2& v) const;
    vec2    operator*(const vec2& v) const;
    vec2    operator/(const vec2& v) const;

    vec2    operator+(const float value) const;
    vec2    operator-(const float value) const;
    vec2    operator*(const float value) const;
    vec2    operator/(const float value) const;

    vec2&   operator+=(const vec2& v);
    vec2&   operator-=(const vec2& v);
    vec2&   operator*=(const vec2& v);
    vec2&   operator/=(const vec2& v);

    vec2&   operator+=(const float value);
    vec2&   operator-=(const float value);
    vec2&   operator*=(const float value);
    vec2&   operator/=(const float value);

};


struct vec3 {
    union {
        GLKVector3  glkVector3;
        struct { float x, y, z; };
        struct { float r, g, b; };
        struct { float s, t, p; };
        float       v[3];
    };
    
public:
    vec3();
    vec3(const float x, const float y, const float z);
    vec3(const GLKVector3& vec);
    vec3(const vec3& vec);
    
public:
    vec3    normalize() const;
    vec3    cross(const vec3& v) const;
    float   dot(const vec3& v) const;
    float   length() const;

public:
    bool    operator==(const vec3& v) const;

    vec3&   operator=(const vec3& v);

    vec3    operator+(const vec3& v) const;
    vec3    operator-(const vec3& v) const;
    vec3    operator*(const vec3& v) const;
    vec3    operator/(const vec3& v) const;

    vec3    operator+(const float value) const;
    vec3    operator-(const float value) const;
    vec3    operator*(const float value) const;
    vec3    operator/(const float value) const;

    vec3&   operator+=(const vec3& v);
    vec3&   operator-=(const vec3& v);
    vec3&   operator*=(const vec3& v);
    vec3&   operator/=(const vec3& v);
    
    vec3&   operator+=(const float value);
    vec3&   operator-=(const float value);
    vec3&   operator*=(const float value);
    vec3&   operator/=(const float value);

};


struct mat4;


struct mat3 {
    union {
        GLKMatrix3 glkMatrix3;
        struct {
            float m00, m01, m02;
            float m10, m11, m12;
            float m20, m21, m22;
        };
        float m[9];
    };

public:
    mat3(float value);
    mat3(const mat4& matrix);
    mat3(const GLKMatrix3& matrix);

public:
    mat3    invert() const;
    
};


struct mat4 {
    union {
        GLKMatrix4  glkMatrix4;
        struct
        {
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        };
        float m[16];
    };
    
    static const mat4 Identity;
    
public:
    mat4(float value);
    mat4(const GLKMatrix4& matrix);
    
public:
    static mat4 MakePerspective(float fovyRadians, float aspect, float nearZ, float farZ);
    static mat4 MakeLookAt(const vec3& eye, const vec3& target, const vec3& up);
    
public:
    mat4    rotate(float rotationInRadian, const vec3& axis) const;
    mat4    scale(const vec3& vec) const;
    mat4    translate(const vec3& vec) const;
    
    mat4    operator*(const mat4& m) const;
    
};

#endif  //#ifndef __GLX_MATH_H__

