//
//  GLKTextureLoader.h
//
//  Created by Satoshi Numata on 12/04/22.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GLK_TEXTURE_LOADER_H__
#define __GLK_TEXTURE_LOADER_H__

#import <Foundation/Foundation.h>
#import <OpenGL/gl3.h>


@interface GLKTextureInfo : NSObject <NSCopying>
{
@private
    GLuint                      name;
    GLenum                      target;
    GLuint                      width;
    GLuint                      height;
}

@property (readonly) GLuint                     name;
@property (readonly) GLenum                     target;
@property (readonly) GLuint                     width;
@property (readonly) GLuint                     height;

@end


@interface GLKTextureLoader : NSObject

+ (GLKTextureInfo *)textureWithContentsOfURL:(NSURL *)url                           /* The URL from which to read. */
                                     options:(NSDictionary *)options                /* Options that control how the image is loaded. */
                                       error:(NSError **)outError;                  /* Error description. */

+ (GLKTextureInfo*)cubeMapWithContentsOfURL:(NSURL *)url                            /* File path of image. */
                                    options:(NSDictionary *)options                 /* Options that control how the image is loaded. */
                                      error:(NSError **)outError;                   /* Error description. */

@end


#endif  //#ifndef __GLK_TEXTURE_LOADER_H__

