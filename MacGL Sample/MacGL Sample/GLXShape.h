//
//  GLXShape.h
//
//  Created by Satoshi Numata on 12/04/11.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//


#ifndef __GLX_SHAPE_H__
#define __GLX_SHAPE_H__

#include <TargetConditionals.h>

#ifdef TARGET_IOS_IPHONE
#import <GLKit/GLKit.h>
#else
#import <OpenGL/gl3.h>
#endif  //#ifdef TARGET_IOS_IPHONE

#include <vector>
#include "GLXMath.h"


struct GLXVertex {
    vec3    pos;
    vec3    normal;
    vec2    texUV;
};


class GLXShape {
    
public:
    static void SetAttributePosition(GLuint index);
    static void SetAttributeNormal(GLuint index);
    static void SetAttributeTextureUV(GLuint index);
    
private:
    std::vector<GLXVertex>  mVertexData;
    int                     mVertexCount;
    
    GLuint  mVertexArray;
    GLuint  mVertexBuffer;

protected:
    GLXShape();
    
public:
    virtual ~GLXShape();
    
public:
    void    draw();
    
protected:
    void    addPolygon(const vec3& p1, const vec3& p2, const vec3& p3,
                       const vec2& uv1, const vec2& uv2, const vec2& uv3);
    void    makeVBO();
    
};


class GLXShapePlane : public GLXShape {
    
public:
    GLXShapePlane();

};


class GLXShapeCube : public GLXShape {
    
public:
    GLXShapeCube(float size);
    
};


class GLXShapeCylinder : public GLXShape {
    
public:
    GLXShapeCylinder(int divCount, float radius, float height);
    
};


class GLXShapeCone : public GLXShape {
    
public:
    GLXShapeCone(int divCount, float radius, float height);
    
};

class GLXShapeSphere : public GLXShape {
    
public:
    GLXShapeSphere(int divX, int divY, float radius);
    
};

class GLXShapeTorus : public GLXShape {
    
public:
    GLXShapeTorus(int divCount, float radius1, float radius2);
    
};

class GLXShapeKlein : public GLXShape {
    
public:
    GLXShapeKlein(int divCount, float radius1, float radius2);
    
};

class GLXShapeDrop : public GLXShape {

public:
    GLXShapeDrop(int divCount, float radius, float height);
    
};


#endif  //#ifndef __GLX_SHAPE_H__

