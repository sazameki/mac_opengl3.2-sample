//
//  GLXOpenGLView.h
//
//  Created by Satoshi Numata on 12/04/20.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>
#include "GameMain.h"


@interface GLXOpenGLView : NSOpenGLView {
    CGLContextObj   mCGLContext;
    GameMain        *mGameMain;
}

@end


