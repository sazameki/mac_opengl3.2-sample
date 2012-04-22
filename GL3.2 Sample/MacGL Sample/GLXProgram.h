//
//  GLXProgram.h
//
//  Created by Satoshi Numata on 12/04/07.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//


#ifndef __GLX_PROGRAM_H__
#define __GLX_PROGRAM_H__


#include <TargetConditionals.h>

#if TARGET_OS_IPHONE
#import <OpenGLES/ES2/gl.h>
#else
#import <OpenGL/gl3.h>
#endif

#include <string>
#include <stdexcept>
#include <map>


class GLXProgram;


class GLXShader {
    
    std::string     mFilename;
    GLuint          mShader;
    
protected:
    GLXShader(const std::string& filename);
    void    compile(const std::string& filename) throw(std::runtime_error);
    
public:
    virtual ~GLXShader();
    
public:
    GLuint      getShader() const;
    std::string getFilename() const;
    
};


class GLXVertexShader : public GLXShader {
    
    friend class GLXProgram;
    
    std::map<int, std::string>  mAttributes;
    
public:
    GLXVertexShader(const std::string& filename) throw(std::runtime_error);
    
public:
    void    addAttributeIndex(GLuint index, const std::string& name);
    
private:
    void    locateAttributes(GLuint program);
    
};


class GLXFragmentShader : public GLXShader {
    
public:
    GLXFragmentShader(const std::string& filename) throw(std::runtime_error);
    
};


class GLXProgram {
    
    GLuint  mProgram;
    
public:
    GLXProgram(GLXVertexShader& vs, GLXFragmentShader& fs) throw(std::runtime_error);
    ~GLXProgram();
    
public:
    bool    validate();
    void    use();
    int     locateUniform(const std::string& name);
    
private:
    bool    link(GLXVertexShader& vs, GLXFragmentShader& fs);
    
};


#endif  //#ifndef __GLX_PROGRAM_H__

