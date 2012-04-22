//
//  GLXFramebuffer.h
//
//  Created by Satoshi Numata on 12/04/08.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GLX_FRAMEBUFFER_H__
#define __GLX_FRAMEBUFFER_H__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <GLKit/GLKit.h>
#else
#import <OpenGL/gl3.h>
#endif

#include "GLXMath.h"
#include "GLXTexture.h"


class GLXRenderTarget : public GLXTexture {
    GLuint  mName;
    vec2    mSize;
    
public:
    /*
         internalFormat:
         GL_ALPHA, GL_RGB, GL_RGBA, GL_RGBA4, GL_RGB5_A1,
         GL_LUMINANCE, GL_LUMINANCE_ALPHA,
         GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT16,
         (GL_RGB565, GL_STENCIL_INDEX, GL_STENCIL_INDEX8)
         
         format:
         GL_ALPHA, GL_RGB, GL_RGBA, GL_BGRA, GL_LUMINANCE, GL_LUMINANCE_ALPHA
         
         type:
         GL_UNSIGNED_BYTE, GL_BYTE, GL_UNSIGNED_SHORT, GL_SHORT, GL_UNSIGNED_INT, GL_INT, GL_FLOAT,
         GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, GL_UNSIGNED_SHORT_4_4_4_4_REV,
         GL_UNSIGNED_SHORT_5_5_5_1, GL_UNSIGNED_SHORT_1_5_5_5_REV 
     */
    GLXRenderTarget(const vec2& size, GLint internalFormat, GLenum format, GLenum type);
    virtual ~GLXRenderTarget();

public:
    virtual void    activate(int texIndex, GLint uniformIndex) throw(std::runtime_error);
    
public:
    GLuint  getName() const;
    
};


class GLXFramebuffer {
    
    vec2    mSize;
    GLuint  mFramebuffer;
    
    GLXRenderTarget     *mColorTarget;
    GLXRenderTarget     *mDepthTarget;
    GLXRenderTarget     *mStencilTarget;
    
public:
    GLXFramebuffer(const vec2& size);
    ~GLXFramebuffer();
    
public:
    void    addColorTarget(GLint internalFormat, GLenum format, GLenum type);
    void    addDepthTarget(GLint internalFormat, GLenum format, GLenum type);
    void    addStencilTarget(GLint internalFormat, GLenum format, GLenum type);
    
private:
    void    attachTarget(GLXRenderTarget *target, GLenum attachment);
    
public:
    void    bind();
    void    unbind();
    
public:
    GLXRenderTarget     *getColorTarget() const;
    GLXRenderTarget     *getDepthTarget() const;
    GLXRenderTarget     *getStencilTarget() const;
    
};

#endif  //#ifndef __GLX_FRAMEBUFFER_H__

