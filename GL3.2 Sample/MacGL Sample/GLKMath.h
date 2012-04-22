//
//  GLKMath.h
//
//  Created by Satoshi Numata on 12/04/20.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GLXMATRIX4_H__
#define __GLXMATRIX4_H__

#include <cmath>

typedef union
{
    struct { float x, y; };
    struct { float s, t; };
    float v[2];
} GLKVector2;


static inline GLKVector2 GLKVector2Add(const GLKVector2& vectorLeft, const GLKVector2& vectorRight)
{
    GLKVector2 v = {
        vectorLeft.v[0] + vectorRight.v[0],
        vectorLeft.v[1] + vectorRight.v[1] };
    return v;
}

static inline GLKVector2 GLKVector2Subtract(const GLKVector2& vectorLeft, const GLKVector2& vectorRight)
{
    GLKVector2 v = {
        vectorLeft.v[0] - vectorRight.v[0],
        vectorLeft.v[1] - vectorRight.v[1] };
    return v;
}

static __inline__ GLKVector2 GLKVector2Multiply(const GLKVector2& vectorLeft, const GLKVector2& vectorRight)
{
    GLKVector2 v = { vectorLeft.v[0] * vectorRight.v[0],
        vectorLeft.v[1] * vectorRight.v[1] };
    return v;
}

static __inline__ GLKVector2 GLKVector2Divide(const GLKVector2& vectorLeft, const GLKVector2& vectorRight)
{
    GLKVector2 v = { vectorLeft.v[0] / vectorRight.v[0],
        vectorLeft.v[1] / vectorRight.v[1] };
    return v;
}

static inline GLKVector2 GLKVector2AddScalar(const GLKVector2& vector, float value)
{
    GLKVector2 v = { vector.v[0] + value, vector.v[1] + value };
    return v;
}

static inline GLKVector2 GLKVector2SubtractScalar(const GLKVector2& vector, float value)
{
    GLKVector2 v = { vector.v[0] - value, vector.v[1] - value };
    return v;
}

static inline GLKVector2 GLKVector2MultiplyScalar(const GLKVector2& vector, float value)
{
    GLKVector2 v = { vector.v[0] * value, vector.v[1] * value };
    return v;
}

static inline GLKVector2 GLKVector2DivideScalar(const GLKVector2& vector, float value)
{
    GLKVector2 v = { vector.v[0] / value, vector.v[1] / value };
    return v;
}

static inline float GLKVector2DotProduct(const GLKVector2& vectorLeft, const GLKVector2& vectorRight)
{
    return vectorLeft.v[0] * vectorRight.v[0] + vectorLeft.v[1] * vectorRight.v[1];
}

static inline float GLKVector2Length(const GLKVector2& vector)
{
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1]);
}

static inline bool GLKVector2AllEqualToVector2(const GLKVector2& vectorLeft, const GLKVector2& vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1])
        compare = true;
    return compare;
}


typedef union {
    struct { float x, y, z; };
    struct { float r, g, b; };
    struct { float s, t, p; };
    float v[3];
} GLKVector3;

static inline GLKVector3 GLKVector3Add(const GLKVector3& vectorLeft, const GLKVector3& vectorRight)
{
    GLKVector3 v = {
        vectorLeft.v[0] + vectorRight.v[0],
        vectorLeft.v[1] + vectorRight.v[1],
        vectorLeft.v[2] + vectorRight.v[2] };
    return v;
}

static inline GLKVector3 GLKVector3Subtract(const GLKVector3& vectorLeft, const GLKVector3& vectorRight)
{
    GLKVector3 v = { vectorLeft.v[0] - vectorRight.v[0],
        vectorLeft.v[1] - vectorRight.v[1],
        vectorLeft.v[2] - vectorRight.v[2] };
    return v;
}

static inline GLKVector3 GLKVector3Multiply(const GLKVector3& vectorLeft, const GLKVector3& vectorRight)
{
    GLKVector3 v = { vectorLeft.v[0] * vectorRight.v[0],
        vectorLeft.v[1] * vectorRight.v[1],
        vectorLeft.v[2] * vectorRight.v[2] };
    return v;
}

static inline GLKVector3 GLKVector3Divide(const GLKVector3& vectorLeft, const GLKVector3& vectorRight)
{
    GLKVector3 v = { vectorLeft.v[0] / vectorRight.v[0],
        vectorLeft.v[1] / vectorRight.v[1],
        vectorLeft.v[2] / vectorRight.v[2] };
    return v;
}

static inline GLKVector3 GLKVector3AddScalar(const GLKVector3& vector, float value)
{
    GLKVector3 v = { vector.v[0] + value,
        vector.v[1] + value,
        vector.v[2] + value };
    return v;
}

static inline GLKVector3 GLKVector3SubtractScalar(const GLKVector3& vector, float value)
{
    GLKVector3 v = { vector.v[0] - value,
        vector.v[1] - value,
        vector.v[2] - value };
    return v;    
}

static inline GLKVector3 GLKVector3MultiplyScalar(const GLKVector3& vector, float value)
{
    GLKVector3 v = { vector.v[0] * value,
        vector.v[1] * value,
        vector.v[2] * value };
    return v;   
}

static inline GLKVector3 GLKVector3DivideScalar(const GLKVector3& vector, float value)
{
    GLKVector3 v = { vector.v[0] / value,
        vector.v[1] / value,
        vector.v[2] / value };
    return v;
}

static inline GLKVector3 GLKVector3CrossProduct(const GLKVector3& vectorLeft, const GLKVector3& vectorRight)
{
    GLKVector3 v = {
        vectorLeft.v[1] * vectorRight.v[2] - vectorLeft.v[2] * vectorRight.v[1],
        vectorLeft.v[2] * vectorRight.v[0] - vectorLeft.v[0] * vectorRight.v[2],
        vectorLeft.v[0] * vectorRight.v[1] - vectorLeft.v[1] * vectorRight.v[0] };
    return v;
}

static inline float GLKVector3DotProduct(const GLKVector3& vectorLeft, const GLKVector3& vectorRight)
{
    return vectorLeft.v[0] * vectorRight.v[0] +
           vectorLeft.v[1] * vectorRight.v[1] +
           vectorLeft.v[2] * vectorRight.v[2];
}

static inline bool GLKVector3AllEqualToVector3(const GLKVector3& vectorLeft, const GLKVector3& vectorRight)
{
    bool compare = false;
    if (vectorLeft.v[0] == vectorRight.v[0] &&
        vectorLeft.v[1] == vectorRight.v[1] &&
        vectorLeft.v[2] == vectorRight.v[2])
        compare = true;
    return compare;
}

static inline GLKVector3 GLKVector3Negate(const GLKVector3& vector)
{
    GLKVector3 v = { -vector.v[0], -vector.v[1], -vector.v[2] };
    return v;
}

static inline float GLKVector3Length(const GLKVector3& vector)
{
    return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1] + vector.v[2] * vector.v[2]);
}

static inline GLKVector3 GLKVector3Normalize(const GLKVector3& vector)
{
    float scale = 1.0f / GLKVector3Length(vector);
    GLKVector3 v = {
        vector.v[0] * scale,
        vector.v[1] * scale,
        vector.v[2] * scale };
    return v;
}


typedef union {
    struct {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
    float m[9];
} GLKMatrix3;

typedef union {
    struct {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
    float m[16];
} GLKMatrix4;


static inline GLKMatrix3 GLKMatrix4GetMatrix3(const GLKMatrix4& matrix)
{
    GLKMatrix3 m = { matrix.m[0], matrix.m[1], matrix.m[2],
        matrix.m[4], matrix.m[5], matrix.m[6],
        matrix.m[8], matrix.m[9], matrix.m[10] };
    return m;
}

static inline float GLKMatrix3Det(const GLKMatrix3& matrix)
{
 	float v1 = matrix.m00 * (matrix.m11 * matrix.m22 - matrix.m21 * matrix.m12); 
 	float v2 = matrix.m01 * (matrix.m20 * matrix.m12 - matrix.m10 * matrix.m22);
 	float v3 = matrix.m02 * (matrix.m10 * matrix.m21 - matrix.m20 * matrix.m11); 
	return v1 + v2 + v3;
}

static inline GLKMatrix3 GLKMatrix3Invert(const GLKMatrix3& matrix, bool *isInvertible)
{
    if (isInvertible) {
        *isInvertible = true;
    }
    
    float determ = 1.0 / GLKMatrix3Det(matrix);

    GLKMatrix3 m;
	m.m00 = determ * (matrix.m11*matrix.m22 - matrix.m12*matrix.m21);
	m.m01 = determ * (matrix.m12*matrix.m20 - matrix.m10*matrix.m22);
	m.m02 = determ * (matrix.m10*matrix.m21 - matrix.m11*matrix.m20);
	m.m10 = determ * (matrix.m21*matrix.m02 - matrix.m01*matrix.m22);
	m.m11 = determ * (matrix.m00*matrix.m22 - matrix.m02*matrix.m20);
	m.m12 = determ * (matrix.m01*matrix.m20 - matrix.m00*matrix.m21);
	m.m20 = determ * (matrix.m01*matrix.m12 - matrix.m02*matrix.m11);
	m.m21 = determ * (matrix.m02*matrix.m10 - matrix.m00*matrix.m12);
	m.m22 = determ * (matrix.m00*matrix.m11 - matrix.m10*matrix.m01);
    return m;
}


//extern const mat4 mat4Identity;

static inline GLKMatrix4 GLKMatrix4MakePerspective(
    float fovyRadians, float aspect, float nearZ, float farZ)
{
    float cotan = 1.0f / tanf(fovyRadians / 2.0f);
    
    GLKMatrix4 m = {
        cotan / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, cotan, 0.0f, 0.0f,
        0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
        0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f
    };
    
    return m;
}

static inline GLKMatrix4 GLKMatrix4MakeLookAt(float eyeX, float eyeY, float eyeZ,
                                  float centerX, float centerY, float centerZ,
                                  float upX, float upY, float upZ)
{
    GLKVector3 ev = { eyeX, eyeY, eyeZ };
    GLKVector3 cv = { centerX, centerY, centerZ };
    GLKVector3 uv = { upX, upY, upZ };
    GLKVector3 n = GLKVector3Normalize(GLKVector3Add(ev, GLKVector3Negate(cv)));
    GLKVector3 u = GLKVector3Normalize(GLKVector3CrossProduct(uv, n));
    GLKVector3 v = GLKVector3CrossProduct(n, u);
    
    GLKMatrix4 m = {
        u.v[0], v.v[0], n.v[0], 0.0f,
        u.v[1], v.v[1], n.v[1], 0.0f,
        u.v[2], v.v[2], n.v[2], 0.0f,
        GLKVector3DotProduct(GLKVector3Negate(u), ev),
        GLKVector3DotProduct(GLKVector3Negate(v), ev),
        GLKVector3DotProduct(GLKVector3Negate(n), ev),
        1.0f };
    
    return m;
}

static inline GLKMatrix4 GLKMatrix4MakeOrtho(float left, float right,
                                             float bottom, float top,
                                             float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    GLKMatrix4 m = { 2.0f / rsl, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / tsb, 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / fsn, 0.0f,
        -ral / rsl, -tab / tsb, -fan / fsn, 1.0f };
    
    return m;
}

static inline GLKMatrix4 GLKMatrix4Multiply(const GLKMatrix4& matrixLeft, const GLKMatrix4& matrixRight)
{
    GLKMatrix4 m;
    
    m.m[0]  = matrixLeft.m[0] * matrixRight.m[0]  + matrixLeft.m[4] * matrixRight.m[1]  + matrixLeft.m[8] * matrixRight.m[2]   + matrixLeft.m[12] * matrixRight.m[3];
	m.m[4]  = matrixLeft.m[0] * matrixRight.m[4]  + matrixLeft.m[4] * matrixRight.m[5]  + matrixLeft.m[8] * matrixRight.m[6]   + matrixLeft.m[12] * matrixRight.m[7];
	m.m[8]  = matrixLeft.m[0] * matrixRight.m[8]  + matrixLeft.m[4] * matrixRight.m[9]  + matrixLeft.m[8] * matrixRight.m[10]  + matrixLeft.m[12] * matrixRight.m[11];
	m.m[12] = matrixLeft.m[0] * matrixRight.m[12] + matrixLeft.m[4] * matrixRight.m[13] + matrixLeft.m[8] * matrixRight.m[14]  + matrixLeft.m[12] * matrixRight.m[15];
    
	m.m[1]  = matrixLeft.m[1] * matrixRight.m[0]  + matrixLeft.m[5] * matrixRight.m[1]  + matrixLeft.m[9] * matrixRight.m[2]   + matrixLeft.m[13] * matrixRight.m[3];
	m.m[5]  = matrixLeft.m[1] * matrixRight.m[4]  + matrixLeft.m[5] * matrixRight.m[5]  + matrixLeft.m[9] * matrixRight.m[6]   + matrixLeft.m[13] * matrixRight.m[7];
	m.m[9]  = matrixLeft.m[1] * matrixRight.m[8]  + matrixLeft.m[5] * matrixRight.m[9]  + matrixLeft.m[9] * matrixRight.m[10]  + matrixLeft.m[13] * matrixRight.m[11];
	m.m[13] = matrixLeft.m[1] * matrixRight.m[12] + matrixLeft.m[5] * matrixRight.m[13] + matrixLeft.m[9] * matrixRight.m[14]  + matrixLeft.m[13] * matrixRight.m[15];
    
	m.m[2]  = matrixLeft.m[2] * matrixRight.m[0]  + matrixLeft.m[6] * matrixRight.m[1]  + matrixLeft.m[10] * matrixRight.m[2]  + matrixLeft.m[14] * matrixRight.m[3];
	m.m[6]  = matrixLeft.m[2] * matrixRight.m[4]  + matrixLeft.m[6] * matrixRight.m[5]  + matrixLeft.m[10] * matrixRight.m[6]  + matrixLeft.m[14] * matrixRight.m[7];
	m.m[10] = matrixLeft.m[2] * matrixRight.m[8]  + matrixLeft.m[6] * matrixRight.m[9]  + matrixLeft.m[10] * matrixRight.m[10] + matrixLeft.m[14] * matrixRight.m[11];
	m.m[14] = matrixLeft.m[2] * matrixRight.m[12] + matrixLeft.m[6] * matrixRight.m[13] + matrixLeft.m[10] * matrixRight.m[14] + matrixLeft.m[14] * matrixRight.m[15];
    
	m.m[3]  = matrixLeft.m[3] * matrixRight.m[0]  + matrixLeft.m[7] * matrixRight.m[1]  + matrixLeft.m[11] * matrixRight.m[2]  + matrixLeft.m[15] * matrixRight.m[3];
	m.m[7]  = matrixLeft.m[3] * matrixRight.m[4]  + matrixLeft.m[7] * matrixRight.m[5]  + matrixLeft.m[11] * matrixRight.m[6]  + matrixLeft.m[15] * matrixRight.m[7];
	m.m[11] = matrixLeft.m[3] * matrixRight.m[8]  + matrixLeft.m[7] * matrixRight.m[9]  + matrixLeft.m[11] * matrixRight.m[10] + matrixLeft.m[15] * matrixRight.m[11];
	m.m[15] = matrixLeft.m[3] * matrixRight.m[12] + matrixLeft.m[7] * matrixRight.m[13] + matrixLeft.m[11] * matrixRight.m[14] + matrixLeft.m[15] * matrixRight.m[15];
    
    return m;
}

static inline GLKMatrix4 GLKMatrix4MakeRotation(float radians, float x, float y, float z)
{
    GLKVector3 vec = { x, y, z };
    GLKVector3 v = GLKVector3Normalize(vec);
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    GLKMatrix4 m = {
        cos + cosp * v.v[0] * v.v[0],
        cosp * v.v[0] * v.v[1] + v.v[2] * sin,
        cosp * v.v[0] * v.v[2] - v.v[1] * sin,
        0.0f,
        cosp * v.v[0] * v.v[1] - v.v[2] * sin,
        cos + cosp * v.v[1] * v.v[1],
        cosp * v.v[1] * v.v[2] + v.v[0] * sin,
        0.0f,
        cosp * v.v[0] * v.v[2] + v.v[1] * sin,
        cosp * v.v[1] * v.v[2] - v.v[0] * sin,
        cos + cosp * v.v[2] * v.v[2],
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f };
    
    return m;
}

static GLKMatrix4 GLKMatrix4Identity = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
};

static inline GLKMatrix4 GLKMatrix4MakeTranslation(float tx, float ty, float tz)
{
    GLKMatrix4 m = GLKMatrix4Identity;
    m.m[12] = tx;
    m.m[13] = ty;
    m.m[14] = tz;
    return m;
}

static inline GLKMatrix4 GLKMatrix4MakeScale(float sx, float sy, float sz)
{
    GLKMatrix4 m = GLKMatrix4Identity;
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    return m;
}

static inline GLKMatrix4 GLKMatrix4Rotate(const GLKMatrix4& matrix, float radians, float x, float y, float z)
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(radians, x, y, z);
    return GLKMatrix4Multiply(matrix, rm);
}

static inline GLKMatrix4 GLKMatrix4Scale(const GLKMatrix4& matrix, float sx, float sy, float sz)
{
    GLKMatrix4 m = { matrix.m[0] * sx, matrix.m[1] * sx, matrix.m[2] * sx, matrix.m[3] * sx,
        matrix.m[4] * sy, matrix.m[5] * sy, matrix.m[6] * sy, matrix.m[7] * sy,
        matrix.m[8] * sz, matrix.m[9] * sz, matrix.m[10] * sz, matrix.m[11] * sz,
        matrix.m[12], matrix.m[13], matrix.m[14], matrix.m[15] };
    return m;
}

static inline GLKMatrix4 GLKMatrix4Translate(const GLKMatrix4& matrix, float tx, float ty, float tz)
{
    GLKMatrix4 m = { matrix.m[0], matrix.m[1], matrix.m[2], matrix.m[3],
        matrix.m[4], matrix.m[5], matrix.m[6], matrix.m[7],
        matrix.m[8], matrix.m[9], matrix.m[10], matrix.m[11],
        matrix.m[0] * tx + matrix.m[4] * ty + matrix.m[8] * tz + matrix.m[12],
        matrix.m[1] * tx + matrix.m[5] * ty + matrix.m[9] * tz + matrix.m[13],
        matrix.m[2] * tx + matrix.m[6] * ty + matrix.m[10] * tz + matrix.m[14],
        matrix.m[15] };
    return m;
}

#endif  //#ifndef __GLXMATRIX4_H__

