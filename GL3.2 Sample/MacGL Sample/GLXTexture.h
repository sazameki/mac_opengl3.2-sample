//
//  GLXTexture.h
//
//  Created by Satoshi Numata on 12/04/22.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GLX_TEXTURE_H__
#define __GLX_TEXTURE_H__

#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <GLKit/GLKit.h>
#else
#import "GLKTextureLoader.h"
#endif

#include <string>
#include <stdexcept>


class GLXTexture {
    
    GLKTextureInfo  *mTexInfo;
    
public:
    GLXTexture(const std::string& filename, bool isCubeMap = false) throw(std::runtime_error);
    virtual ~GLXTexture();
    
protected:
    GLXTexture();
    
public:
    virtual void    activate(int texIndex, GLint uniformIndex) throw(std::runtime_error);
    
};


#endif  //#ifndef __GLX_TEXTURE_H__

