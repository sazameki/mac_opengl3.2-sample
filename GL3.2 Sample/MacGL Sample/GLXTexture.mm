//
//  GLXTexture.mm
//
//  Created by Satoshi Numata on 12/04/22.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GLXTexture.h"
#include <stdexcept>
#include <sstream>


GLXTexture::GLXTexture(const std::string& filename_, bool isCubeMap) throw(std::runtime_error)
: mTexInfo(nil)
{
    NSString *filename = [[NSString alloc] initWithCString:filename_.c_str() encoding:NSUTF8StringEncoding];
    NSURL *fileURL = [[NSBundle mainBundle] URLForResource:[filename stringByDeletingPathExtension]
                                             withExtension:[filename pathExtension]];
    if (!fileURL) {
        std::ostringstream oss;
        oss << "GLXTexture: Cannot find file \"" << filename_ << "\"";
        throw std::runtime_error(oss.str());
    }
    
    NSError *error = nil;
    if (isCubeMap) {
        mTexInfo = [GLKTextureLoader cubeMapWithContentsOfURL:fileURL options:nil error:&error];
    } else {
        mTexInfo = [GLKTextureLoader textureWithContentsOfURL:fileURL options:nil error:&error];
    }
    if (!mTexInfo) {
        std::ostringstream oss;
        oss << "GLXTexture: Invalid image file \"" << filename_ << "\"";
        if (error) {
            NSString *desc = [error localizedDescription];
            if (desc) {
                oss << " (" << [desc cStringUsingEncoding:NSUTF8StringEncoding] << ")";
            }
        }
        throw std::runtime_error(oss.str());
    }
}

GLXTexture::GLXTexture()
: mTexInfo(nil)
{
    // Do nothing
}

GLXTexture::~GLXTexture()
{
    if (mTexInfo) {
        mTexInfo = nil;
    }
}

void GLXTexture::activate(int texIndex, GLint uniformIndex) throw(std::runtime_error)
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
    glBindTexture(mTexInfo.target, mTexInfo.name);
    glUniform1i(uniformIndex, texIndex);
}

