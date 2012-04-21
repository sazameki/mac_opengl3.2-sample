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
    
    GLXShape    *mShape;
    GLXShape    *mShape2;
    
    float   mRotation;
    
    std::vector<StarInfo>   mStars;

public:
    GameMain();
    ~GameMain();
    
public:
    void    updateModel();
    void    drawView();
    
protected:
    void    loadShaders();
    
};


#endif  //#ifndef __GAMEMAIN_H__

