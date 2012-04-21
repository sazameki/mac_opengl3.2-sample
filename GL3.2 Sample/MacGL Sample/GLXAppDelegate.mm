//
//  GLXAppDelegate.m
//
//  Created by Satoshi Numata on 12/04/21.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import "GLXAppDelegate.h"
#import "GLXSetting.h"


BOOL gIsAppRunning = YES;


@implementation GLXAppDelegate

@synthesize window = _window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Adjust window size
    [_window setContentSize:NSMakeSize(GLX_SCREEN_WIDTH, GLX_SCREEN_HEIGHT)];
    
    // Allow full screen mode
    [_window setCollectionBehavior:NSWindowCollectionBehaviorFullScreenPrimary];

    // Show the window
    [_window makeKeyAndOrderFront:self];
}

// Allow window resizing only in the full screen mode
- (NSSize)window:(NSWindow *)window willUseFullScreenContentSize:(NSSize)proposedSize
{
    return proposedSize;
}

// Terminate the app after the window is closed
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
    return YES;
}

// Terminate the app after cleaning up
// App termination will be performed with calling -[NSApp replyToApplicationShouldTerminate:] in -[GLXOpenGLView finishApplication].
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    gIsAppRunning = NO;
    return NSTerminateLater;
}

@end

