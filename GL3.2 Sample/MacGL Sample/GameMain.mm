//
//  GameMain.mm
//
//  Created by Satoshi Numata on 12/04/21.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GameMain.h"


enum
{
    ATTRIB_VERTEX,
    ATTRIB_NORMAL,
    ATTRIB_TEXTURE_UV,
    NUM_ATTRIBUTES
};

enum
{
    UNIFORM_MODELVIEWPROJECTION_MATRIX,
    UNIFORM_MODEL_MATRIX,
    UNIFORM_LIGHT_VECTOR,
    UNIFORM_TEXTURE_0,
    NUM_UNIFORMS
};
GLint uniforms[NUM_UNIFORMS];

enum
{
    UNIFORM2_MODELVIEWPROJECTION_MATRIX,
    UNIFORM2_TEXTURE_0,
    UNIFORM2_TIME,
    NUM_UNIFORMS2
};
GLint uniforms2[NUM_UNIFORMS2];


GameMain::GameMain(const vec2& screenSize)
{
    // Load shaders
    loadShaders();
    
    // Set using the defeault alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Make shapes
    GLXShape::SetAttributePosition(ATTRIB_VERTEX);
    GLXShape::SetAttributeNormal(ATTRIB_NORMAL);
    GLXShape::SetAttributeTextureUV(ATTRIB_TEXTURE_UV);
    
    mShape = new GLXShapeSphere(20, 20, 0.05);
    mShape2 = new GLXShapeSphere(100, 100, 5.0);
    mShapePlane = new GLXShapePlane();
    
    mTex0 = new GLXTexture("nasa_saturn.png");
    mTex1 = new GLXTexture("nasa_mimas.png");
    
    // Setup models
    mRotation = 0.0f;
    
    float angle = 0.0;
    float radius = 6.8;
    const int starCount = 1000;
    for (int i = 0; i < starCount; i++) {
        angle += 0.01;
        radius += 2.0 / starCount;
        
        float xr = ((float)(rand() % 10000) / 10000 - 0.5) * 1.0;
        float yr = ((float)(rand() % 10000) / 10000 - 0.5) * radius * 2 / 12;
        float zr = ((float)(rand() % 10000) / 10000 - 0.5) * 1.0;
        
        StarInfo starInfo;
        starInfo.pos.x = cosf(angle) * radius + xr;
        starInfo.pos.y = 0.6 + yr;
        starInfo.pos.z = sinf(angle) * radius + zr;
        mStars.push_back(starInfo);
    }
    
    ///// Prepare texture rendering
    mFramebuffer = new GLXFramebuffer(screenSize);
    mFramebuffer->addColorTarget(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
    mFramebuffer->addDepthTarget(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT);
}

GameMain::~GameMain()
{
    delete mFramebuffer;
    mFramebuffer = 0;
    
    delete mShape;
    mShape = 0;
    
    delete mShape2;
    mShape2 = 0;
    
    delete mTex0;
    mTex0 = 0;
    
    delete mTex1;
    mTex1 = 0;
    
    delete mProgram;
    mProgram = 0;
    
    delete mProgram2;
    mProgram2 = 0;
}

void GameMain::loadShaders()
{
    GLXVertexShader vs("Shader.vsh");
    vs.addAttributeIndex(ATTRIB_VERTEX, "position");
    vs.addAttributeIndex(ATTRIB_NORMAL, "normal");
    vs.addAttributeIndex(ATTRIB_TEXTURE_UV, "texUV");
    
    GLXFragmentShader fs("Shader.fsh");
    
    // Shader 1
    mProgram = new GLXProgram(vs, fs);
    uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX] = mProgram->locateUniform("modelViewProjectionMatrix");
    uniforms[UNIFORM_MODEL_MATRIX] = mProgram->locateUniform("modelMatrix");
    uniforms[UNIFORM_LIGHT_VECTOR] = mProgram->locateUniform("lightVec");
    uniforms[UNIFORM_TEXTURE_0] = mProgram->locateUniform("texture0");
    
    // Shader 2
    GLXFragmentShader fs2("Shader2.fsh");
    mProgram2 = new GLXProgram(vs, fs2);
    uniforms2[UNIFORM2_MODELVIEWPROJECTION_MATRIX] = mProgram2->locateUniform("modelViewProjectionMatrix");
    uniforms2[UNIFORM2_TEXTURE_0] = mProgram2->locateUniform("texture0");
    uniforms2[UNIFORM2_TIME] = mProgram2->locateUniform("time");
    
    // Shaders are no more needed after they were linked into a program.
}

void GameMain::updateModel()
{
    mRotation += 0.01f;
}

void GameMain::draw1(const vec2& screenSize)
{
    float aspect = fabsf(screenSize.x / screenSize.y);
    
    mat4 projMat = mat4::MakePerspective(M_PI/2, aspect, 0.1f, 100.0f);
    vec3 eye(cosf(mRotation) * 10.0, 3.0, sinf(mRotation) * 10.0);
    mat4 viewMat = mat4::MakeLookAt(eye,
                                    vec3(0.0, 0.0, 0.0),
                                    vec3(0.0, 1.0, 0.0));
    
    mat4 vpMat = projMat * viewMat;
    
    mFramebuffer->bind();
    mProgram->use();
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    
    glUniform3fv(uniforms[UNIFORM_LIGHT_VECTOR], 1, (vec3(0.0, 0.0, 0.0)-eye).v);
    
    {
        mTex0->activate(0, uniforms[UNIFORM_TEXTURE_0]);
        mat4 modelMat = mat4::Identity;
        modelMat = modelMat.scale(vec3(1.0, 0.98, 1.0));
        mat4 mvpMat = vpMat * modelMat;
        glUniformMatrix4fv(uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, mvpMat.m);
        glUniformMatrix4fv(uniforms[UNIFORM_MODEL_MATRIX], 1, 0, modelMat.m);
        mShape2->draw();
    }
    
    mTex1->activate(0, uniforms[UNIFORM_TEXTURE_0]);
    for (int i = 0; i < mStars.size(); i++) {
        const StarInfo& starInfo = mStars[i];
        mat4 modelMat = mat4::Identity;
        modelMat = modelMat.translate(starInfo.pos);
        mat4 mvpMat = vpMat * modelMat;
        glUniformMatrix4fv(uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX], 1, 0, mvpMat.m);
        glUniformMatrix4fv(uniforms[UNIFORM_MODEL_MATRIX], 1, 0, modelMat.m);
        mShape->draw();
    }
}

void GameMain::draw2(const vec2& screenSize)
{
    static float time = 0.0f;
    time += 2.0f;
    
    mFramebuffer->unbind();
    mProgram2->use();
    
    glDisable(GL_DEPTH_TEST);
    
    //glClearColor(0.0, 0.0, 0.0, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);
    
    mat4 projMat = mat4::MakeOrtho(0.0, screenSize.x, screenSize.y, 0.0, 0.001, 100.0);
    mat4 viewMat = mat4::MakeLookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    mat4 modelMat = mat4::MakeScale(vec3(screenSize.x, screenSize.y, 0));
    
    mat4 mvpMat = projMat * viewMat * modelMat;
    
    glUniformMatrix4fv(uniforms2[UNIFORM2_MODELVIEWPROJECTION_MATRIX], 1, 0, mvpMat.m);
    mFramebuffer->getColorTarget()->activate(0, uniforms2[UNIFORM2_TEXTURE_0]);
    glUniform1f(uniforms2[UNIFORM2_TIME], time);
    
    mShapePlane->draw();
}

void GameMain::drawView(const vec2& screenSize)
{
    // 1st stage
    draw1(screenSize);
    
    // 2nd stage
    draw2(screenSize);
}

