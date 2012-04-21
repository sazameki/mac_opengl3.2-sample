//
//  GameMain.cpp
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


GameMain::GameMain()
{
    // Load shaders
    loadShaders();
    
    // Set using the defeault alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Set using the depth buffer
    glEnable(GL_DEPTH_TEST);
    
    // Make shapes
    GLXShape::SetAttributePosition(ATTRIB_VERTEX);
    GLXShape::SetAttributeNormal(ATTRIB_NORMAL);
    GLXShape::SetAttributeTextureUV(ATTRIB_TEXTURE_UV);

    mShape = new GLXShapeSphere(20, 20, 0.05);
    mShape2 = new GLXShapeSphere(100, 100, 5.0);
    
    mTex0 = new GLXTexture("nasa_saturn.png");
    mTex1 = new GLXTexture("nasa_mimas.png");

    // Setup models
    mRotation = 0.0f;
    
    float angle = 0.0;
    float radius = 6.8;
    const int starCount = 10000;
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
}

GameMain::~GameMain()
{
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
}

void GameMain::loadShaders()
{
    GLXVertexShader vs("Shader.vsh");
    vs.addAttributeIndex(ATTRIB_VERTEX, "position");
    vs.addAttributeIndex(ATTRIB_NORMAL, "normal");
    vs.addAttributeIndex(ATTRIB_TEXTURE_UV, "texUV");

    GLXFragmentShader fs("Shader.fsh");
    
    mProgram = new GLXProgram(vs, fs);
    
    uniforms[UNIFORM_MODELVIEWPROJECTION_MATRIX] = mProgram->locateUniform("modelViewProjectionMatrix");
    uniforms[UNIFORM_MODEL_MATRIX] = mProgram->locateUniform("modelMatrix");
    uniforms[UNIFORM_LIGHT_VECTOR] = mProgram->locateUniform("lightVec");
    uniforms[UNIFORM_TEXTURE_0] = mProgram->locateUniform("texture0");

    // Shaders are no more needed after they were linked into a program.
}

void GameMain::updateModel()
{
    mRotation += 0.01f;
}

void GameMain::drawView(const vec2& screenSize)
{
    float aspect = fabsf(screenSize.x / screenSize.y);

    mat4 projMat = mat4::MakePerspective(M_PI/2, aspect, 0.1f, 100.0f);
    vec3 eye(cosf(mRotation) * 10.0, 3.0, sinf(mRotation) * 10.0);
    mat4 viewMat = mat4::MakeLookAt(eye,
                                    vec3(0.0, 0.0, 0.0),
                                    vec3(0.0, 1.0, 0.0));
    
    mat4 vpMat = projMat * viewMat;
    
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    mProgram->use();
    
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

