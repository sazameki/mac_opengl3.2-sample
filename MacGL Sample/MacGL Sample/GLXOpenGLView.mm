//
//  GLXOpenGLView.m
//
//  Created by Satoshi Numata on 12/04/20.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GLXOpenGLView.h"
#import "GLXAppDelegate.h"
#import "GLXSetting.h"


@implementation GLXOpenGLView

- (id)initWithFrame:(NSRect)frame
{
    // 注意：NSOpenGLPFAWindow を指定すると、OpenGL 3.2のCore Profileは使えないらしい。
    NSOpenGLPixelFormatAttribute attrs[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize, (NSOpenGLPixelFormatAttribute)24,
        NSOpenGLPFAAlphaSize, (NSOpenGLPixelFormatAttribute)8,
        NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16,
        NSOpenGLPFAAccelerated,
        NSOpenGLPFADoubleBuffer,
        (NSOpenGLPixelFormatAttribute)0
    };
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
    if (!pixelFormat) {
        NSLog(@"Failed to create a pixel format object.");
        return nil;
    }

    return [super initWithFrame:frame pixelFormat:pixelFormat];
}

- (void)prepareOpenGL
{
    mCGLContext = (CGLContextObj)self.openGLContext.CGLContextObj;

    CGLLockContext(mCGLContext);
    CGLSetCurrentContext(mCGLContext);
    
    mGameMain = new GameMain();
    
    CGLUnlockContext(mCGLContext);

    [NSThread detachNewThreadSelector:@selector(updateProc:)
                             toTarget:self
                           withObject:nil];
}

- (void)drawRect:(NSRect)dirtyRect
{
    CGLLockContext(mCGLContext);
    CGLSetCurrentContext(mCGLContext);
    
    static const float baseRatio = (float)GLX_SCREEN_WIDTH/GLX_SCREEN_HEIGHT;
    
    int width = (int)self.frame.size.width;
    int height = (int)self.frame.size.height;
    
    int x = 0, y = 0;
    if ((float)width / height <= baseRatio) {
        int theHeight = (int)(width / baseRatio);
        y = (height - theHeight) / 2;
        height = theHeight;
    } else {
        int theWidth = (int)(height * baseRatio);
        x = (width - theWidth) / 2;
        width = theWidth;
    }
    
    glViewport(x, y, width, height);
    
    mGameMain->drawView();

    CGLFlushDrawable(mCGLContext);
    CGLUnlockContext(mCGLContext);
}

- (void)updateProc:(id)dummy
{
    @autoreleasepool {
        while (gIsAppRunning) {
            CGLLockContext(mCGLContext);
            CGLSetCurrentContext(mCGLContext);

            mGameMain->drawView();
            mGameMain->updateModel();

            CGLFlushDrawable(mCGLContext);
            CGLUnlockContext(mCGLContext);

            [NSThread sleepForTimeInterval:1.0/60];
        }
        
        [self performSelectorOnMainThread:@selector(finishApplication) withObject:nil waitUntilDone:NO];
    }
}

- (void)finishApplication
{
    delete mGameMain;
    mGameMain = 0;
    
    // AppDelegateのapplicationShouldTerminate:で遅延させていたアプリケーション終了をここで完了させます。
    [NSApp replyToApplicationShouldTerminate:YES];
}

@end


