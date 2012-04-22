//
//  GLXProgram.mm
//
//  Created by Satoshi Numata on 12/04/07.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GLXProgram.h"


#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#else
#import <Foundation/Foundation.h>
#import <OpenGL/OpenGL.h>
#endif

#include "GLXLog.h"
#include <sstream>


bool CompileShader(GLuint *shader, NSString *filepath, GLenum type)
{
    GLint status;
    
    const GLchar *source = (GLchar *)[[NSString stringWithContentsOfFile:filepath encoding:NSUTF8StringEncoding error:nil] UTF8String];
    if (!source) {
        if (type == GL_VERTEX_SHADER) {
            NSLog(@"[Error] GLMShader: Cannot load source file for vertex shader: \"%@\"", filepath);
        } else {
            NSLog(@"[Error] GLMShader: Cannot load source file for fragment shader: \"%@\"", filepath);
        }
        return NO;
    }
    
    *shader = glCreateShader(type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);
    
#if defined(DEBUG)
    GLint logLength;
    glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetShaderInfoLog(*shader, logLength, &logLength, log);
        NSLog(@"Shader compile log:\n%s", log);
        free(log);
    }
#endif
    
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        glDeleteShader(*shader);
        return false;
    }
    
    return true;
}


GLXShader::GLXShader(const std::string& filename)
: mFilename(filename)
{
    // Do nothing
}

void GLXShader::compile(const std::string& filename_) throw(std::runtime_error)
{
    GLenum type = (dynamic_cast<GLXVertexShader*>(this)? GL_VERTEX_SHADER: GL_FRAGMENT_SHADER);
    
    NSString *filename = [[NSString alloc] initWithCString:filename_.c_str() encoding:NSUTF8StringEncoding];    
    NSString *filepath = [[NSBundle mainBundle] pathForResource:[filename stringByDeletingPathExtension]
                                                         ofType:[filename pathExtension]];
    
    if (!filepath) {
        std::ostringstream oss;
        if (type == GL_VERTEX_SHADER) {
            oss << "GLXVertexShader: ";
        } else {
            oss << "GLXFragmentShader: ";
        }
        oss << "Cannot find source file \"" << filename_ << "\"";
        throw std::runtime_error(oss.str());
    }
    
    if (!CompileShader(&mShader, filepath, type)) {
        std::ostringstream oss;
        if (type == GL_VERTEX_SHADER) {
            oss << "GLXVertexShader: ";
        } else {
            oss << "GLXFragmentShader: ";
        }
        oss << "Failed to compile \"" << filename_ << "\"";
        throw std::runtime_error(oss.str());
    }
}

GLXShader::~GLXShader()
{
    if (mShader) {
        glDeleteShader(mShader);
        mShader = 0;
    }
}

GLuint GLXShader::getShader() const
{
    return mShader;
}

std::string GLXShader::getFilename() const
{
    return mFilename;
}


GLXVertexShader::GLXVertexShader(const std::string& filename) throw(std::runtime_error)
: GLXShader(filename)
{
    compile(filename);
}

void GLXVertexShader::addAttributeIndex(GLuint index, const std::string& name)
{
    mAttributes[index] = name;
}

void GLXVertexShader::locateAttributes(GLuint program)
{
    std::map<int, std::string>::iterator it = mAttributes.begin();
    while (it != mAttributes.end()) {
        int index = it->first;
        const std::string& name = it->second;
        glBindAttribLocation(program, index, name.c_str());
        it++;
    }
}


GLXFragmentShader::GLXFragmentShader(const std::string& filename) throw(std::runtime_error)
: GLXShader(filename)
{
    compile(filename);
}


GLXProgram::GLXProgram(GLXVertexShader& vs, GLXFragmentShader& fs) throw(std::runtime_error)
{
    mProgram = glCreateProgram();
    if (!link(vs, fs)) {
        throw std::runtime_error("GLXProgram: Failed to link shaders.");
    }
}

GLXProgram::~GLXProgram()
{
    if (mProgram) {
        glDeleteProgram(mProgram);
        mProgram = 0;
    }
}

bool GLXProgram::link(GLXVertexShader& vs, GLXFragmentShader& fs)
{
    ///// シェーダのアタッチ
    glAttachShader(mProgram, vs.getShader());
    glAttachShader(mProgram, fs.getShader());
    
    // attribute 変数の位置取得はリンク前に行う
    vs.locateAttributes(mProgram);
    
    ///// プログラムのリンク
    glLinkProgram(mProgram);
    
#if defined(DEBUG)
    GLint logLength;
    glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(mProgram, logLength, &logLength, log);
        GLXLog("Program link log (%s, %s):\n%s", vs.getFilename().c_str(), fs.getFilename().c_str(), log);
        free(log);
    }
#endif
    
    GLint status;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &status);
    if (status == 0) {
        return false;
    }
    
    ///// シェーダのデタッチ
    glDetachShader(mProgram, vs.getShader());
    glDetachShader(mProgram, fs.getShader());
    
    return true;
}

bool GLXProgram::validate()
{
    GLint logLength, status;
    
    glValidateProgram(mProgram);
    glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = (GLchar *)malloc(logLength);
        glGetProgramInfoLog(mProgram, logLength, &logLength, log);
        GLXLog("Program validate log:\n%s", log);
        free(log);
    }
    
    glGetProgramiv(mProgram, GL_VALIDATE_STATUS, &status);
    if (status == 0) {
        return false;
    }
    
    return true;
}

void GLXProgram::use()
{
    glUseProgram(mProgram);
}

int GLXProgram::locateUniform(const std::string& name)
{
    return glGetUniformLocation(mProgram, name.c_str());
}

