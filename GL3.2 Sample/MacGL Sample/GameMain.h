//
//  GameMain.h
//
//  Created by Satoshi Numata on 12/04/21.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

#include <vector>

#include "GLXCollection.h"


struct StarInfo {
    vec3    pos;
};


class GameMain {
    
    GLXProgram  *mProgram;
    GLXProgram  *mProgram2;
    
    GLXShape    *mShape;
    GLXShape    *mShape2;
    GLXShape    *mShapePlane;

    float   mRotation;
    
    std::vector<StarInfo>   mStars;
    
    GLXTexture  *mTex0;
    GLXTexture  *mTex1;

    GLXFramebuffer  *mFramebuffer;

public:
    GameMain(const vec2& screenSize);
    ~GameMain();
    
private:
    void    loadShaders();

public:
    void    updateModel();
    void    drawView(const vec2& screenSize);
    
private:
    void    draw1(const vec2& screenSize);
    void    draw2(const vec2& screenSize);
    
};


#endif  //#ifndef __GAMEMAIN_H__

