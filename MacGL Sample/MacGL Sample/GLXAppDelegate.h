//
//  GLXAppDelegate.h
//
//  Created by Satoshi Numata on 12/04/21.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#import <Cocoa/Cocoa.h>


extern BOOL gIsAppRunning;


@interface GLXAppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;

@end
