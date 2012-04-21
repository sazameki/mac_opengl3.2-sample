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
#include <map>


class GLXProgram;


class GLXShader {

    GLuint  mShader;
    
protected:
    void    compile(const std::string& filename);
    
public:
    virtual ~GLXShader();
    
public:
    GLuint  getShader() const;
    
};


class GLXVertexShader : public GLXShader {
    
    friend class GLXProgram;
    
    std::map<int, std::string>  mAttributes;

public:
    GLXVertexShader(const std::string& filename);
    
public:
    void    addAttributeIndex(GLuint index, const std::string& name);
    
private:
    void    locateAttributes(GLuint program);
    
};


class GLXFragmentShader : public GLXShader {

public:
    GLXFragmentShader(const std::string& filename);

};


class GLXProgram {

    GLuint  mProgram;

public:
    GLXProgram(GLXVertexShader& vs, GLXFragmentShader& fs);
    ~GLXProgram();
    
public:
    bool    validate();
    void    use();
    int     locateUniform(const std::string& name);
    
private:
    bool    link(GLXVertexShader& vs, GLXFragmentShader& fs);
    
};


#endif  //#ifndef __GLX_PROGRAM_H__

