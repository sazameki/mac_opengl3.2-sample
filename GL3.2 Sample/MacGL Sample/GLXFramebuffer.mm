//
//  GLXFramebuffer.mm
//
//  Created by Satoshi Numata on 12/04/08.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GLXFramebuffer.h"

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import "GLXViewController.h"
#endif

#include <sstream>


GLXRenderTarget::GLXRenderTarget(const vec2& size, GLint internalFormat, GLenum format, GLenum type)
    : mSize(size)
{
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &mName);
    
    if (mName == GL_INVALID_OPERATION) {
        NSLog(@"[Error] GLMRenderTarget: Failed to creaete a texture as a rendering target (INVALID_OPERATION).");
        return;
    } else if (mName == GL_INVALID_VALUE) {
        NSLog(@"[Error] GLMRenderTarget: Failed to creaete a texture as a rendering target (INVALID_VALUE).");
        return;
    } else if (mName == GL_INVALID_ENUM) {
        NSLog(@"[Error] GLMRenderTarget: Failed to creaete a texture as a rendering target (INVALID_ENUM).");
        return;
    }
    
    glBindTexture(GL_TEXTURE_2D, mName);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,                 // MIPMAPレベル
                 internalFormat,    // テクスチャで使うコンポーネント数
                 (GLsizei)mSize.x, (GLsizei)mSize.y,   // テクスチャのサイズ
                 0,                 // ボーダー（0:境界線なし、1:境界線あり）
                 format,            // ビットマップの色の並び順
                 type,              // 各コンポーネントのサイズ
                 0);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLXRenderTarget::~GLXRenderTarget()
{
    if (mName != GL_INVALID_VALUE) {
        glDeleteTextures(1, &mName);
    }
}

void GLXRenderTarget::activate(int texIndex, GLint uniformIndex) throw(std::runtime_error)
{
    GLenum texture;
    switch (texIndex) {
        case 0:
            texture = GL_TEXTURE0;
            break;
        case 1:
            texture = GL_TEXTURE1;
            break;
        case 2:
            texture = GL_TEXTURE2;
            break;
        case 3:
            texture = GL_TEXTURE3;
            break;
        case 4:
            texture = GL_TEXTURE4;
            break;
        case 5:
            texture = GL_TEXTURE5;
            break;
        case 6:
            texture = GL_TEXTURE6;
            break;
        case 7:
            texture = GL_TEXTURE7;
            break;
        default:
            std::ostringstream oss;
            oss << "GLXTexture: Invalid texture index: " << texIndex;
            throw std::runtime_error(oss.str());
            break;
    }
    
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, mName);
    glUniform1i(uniformIndex, texIndex);
}

GLuint GLXRenderTarget::getName() const
{
    return mName;
}


GLXFramebuffer::GLXFramebuffer(const vec2& size)
    : mSize(size), mColorTarget(0), mDepthTarget(0), mStencilTarget(0)
{
    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
}

GLXFramebuffer::~GLXFramebuffer()
{
    if (mColorTarget) {
        delete mColorTarget;
        mColorTarget = 0;
    }
    if (mDepthTarget) {
        delete mDepthTarget;
        mDepthTarget = 0;
    }
    if (mStencilTarget) {
        delete mStencilTarget;
        mStencilTarget = 0;
    }
    glDeleteFramebuffers(1, &mFramebuffer);
}

void GLXFramebuffer::attachTarget(GLXRenderTarget *target, GLenum attachment)
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, target->getName(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLXFramebuffer::addColorTarget(GLint internalFormat, GLenum format, GLenum type)
{
    mColorTarget = new GLXRenderTarget(mSize, internalFormat, format, type);
    attachTarget(mColorTarget, GL_COLOR_ATTACHMENT0);
}

void GLXFramebuffer::addDepthTarget(GLint internalFormat, GLenum format, GLenum type)
{
    mDepthTarget = new GLXRenderTarget(mSize, internalFormat, format, type);
    attachTarget(mDepthTarget, GL_DEPTH_ATTACHMENT);
}

void GLXFramebuffer::addStencilTarget(GLint internalFormat, GLenum format, GLenum type)
{
    mStencilTarget = new GLXRenderTarget(mSize, internalFormat, format, type);
    attachTarget(mStencilTarget, GL_STENCIL_ATTACHMENT);
}

void GLXFramebuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
}

void GLXFramebuffer::unbind()
{
#if TARGET_OS_IPHONE
    [_gGLKView bindDrawable];
#else
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
}

GLXRenderTarget *GLXFramebuffer::getColorTarget() const
{
    return mColorTarget;
}

GLXRenderTarget *GLXFramebuffer::getDepthTarget() const
{
    return mDepthTarget;
}

GLXRenderTarget *GLXFramebuffer::getStencilTarget() const
{
    return mStencilTarget;
}

