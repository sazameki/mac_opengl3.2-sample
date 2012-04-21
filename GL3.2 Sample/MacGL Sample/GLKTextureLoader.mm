//
//  GLKTextureLoader.mm
//
//  Created by Satoshi Numata on 12/04/22.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GLKTextureLoader.h"

#include <stdexcept>
#include "GLXMath.h"


enum Texture2DScaleMode {
    Texture2DScaleModeLinear,
    Texture2DScaleModeNearest,
};


@interface GLKTextureInfo()

- (id)initWithTarget:(GLenum)target name:(GLuint)name width:(GLuint)width height:(GLuint)height;

@end


@implementation GLKTextureInfo

@synthesize name;
@synthesize target;
@synthesize width;
@synthesize height;

- (id)copyWithZone:(NSZone *)zone
{
    GLKTextureInfo *ret = [[GLKTextureInfo alloc] init];
    
    ret->target = target;
    ret->name = name;
    ret->width = width;
    ret->height = height;
    
    return ret;
}

- (id)initWithTarget:(GLenum)target_ name:(GLuint)name_ width:(GLuint)width_ height:(GLuint)height_
{
    self = [super init];
    if (self) {
        target = target_;
        name = name_;
        width = width_;
        height = height_;
    }
    return self;
}

@end


@implementation GLKTextureLoader

GLuint __Texture2DLoad(NSURL *imageURL, Texture2DScaleMode scaleMode, vec2* imageSize)
{
    GLuint ret = GL_INVALID_VALUE;
    
    // 画像の読み込み
    CGImageSourceRef imageSourceRef = CGImageSourceCreateWithURL((__bridge CFURLRef)imageURL, NULL);
    CGImageRef imageRef = CGImageSourceCreateImageAtIndex(imageSourceRef, 0, NULL);
    if (imageRef == NULL) {
        return ret;
	}    
    
    // 画像サイズの取得と調整
    imageSize->x = (float)CGImageGetWidth(imageRef);
    imageSize->y = (float)CGImageGetHeight(imageRef);
    
    // ビットマップ（RGBAの並び）への変換
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    NSMutableData* data = [NSMutableData dataWithLength:(4 * (int)(imageSize->x) * (int)(imageSize->y))];
    CGContextRef bitmapContextRef = CGBitmapContextCreate([data mutableBytes],
                                                          (size_t)(imageSize->x),
                                                          (size_t)(imageSize->y),
                                                          8,                        // Bits per component
                                                          (size_t)(imageSize->x) * 4, // Bytes per Row
                                                          colorSpaceRef,
                                                          kCGImageAlphaPremultipliedLast);
    CGContextDrawImage(bitmapContextRef,
                       CGRectMake(0, 0, (int)imageSize->x, (int)imageSize->y),
                       imageRef);
    
    // アルファ値に対する調整（これがないと半透明部分が黒くなってしまう）
    unsigned char* p = (unsigned char*)[data mutableBytes];
    for (int i = 0; i < imageSize->x * imageSize->y; i++) {
        float alpha = (float)*(p + 3) / 0xff;
        if (alpha > 0.0f && alpha < 1.0f) {
            *p = (unsigned char)((float)*p / alpha);
            p++;
            *p = (unsigned char)((float)*p / alpha);
            p++;
            *p = (unsigned char)((float)*p / alpha);
            p += 2;
        } else {
            p += 4;
        }
    }
    
    // テクスチャの名前を作る
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &ret);
    glBindTexture(GL_TEXTURE_2D, ret);
    
    // ビットマップを割り当てる
    glPixelStorei(GL_UNPACK_ROW_LENGTH, (GLint)(imageSize->x));     // テクスチャ画像の横幅
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);                          // テクスチャ画像はバイト単位で並んでいる
    
    if (scaleMode == Texture2DScaleModeLinear) {
        // 拡大・縮小時の線形補間の指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        // 拡大・縮小時のニアレストネイバー補間の指定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);      
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    // クランプ処理の指定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    // 各行のピクセルデータの境界の種類
    // 1: バイト単位
    // 2: 偶数バイト単位
    // 4: WORD（2バイト）単位
    // 8: DWORD（4バイト）単位
    glTexImage2D(GL_TEXTURE_2D,
                 0,                             // MIPMAPのレベル
                 GL_RGBA,                       // テクスチャで使うカラーコンポーネント数
                 (GLsizei)(imageSize->x),      // テクスチャ画像の横幅
                 (GLsizei)(imageSize->y),     // テクスチャ画像の高さ
                 0,                             // ボーダー（0:境界線なし、1:境界線あり）
                 GL_RGBA,                       // ビットマップの色の並び順
                 GL_UNSIGNED_BYTE,
                 [data bytes]);
    
    ///// クリーンアップ
    CGContextRelease(bitmapContextRef);
    CGColorSpaceRelease(colorSpaceRef);
    CGImageRelease(imageRef);
    CFRelease(imageSourceRef);
    
    return ret;
}

+ (GLKTextureInfo *)textureWithContentsOfURL:(NSURL *)url
                                     options:(NSDictionary *)options
                                       error:(NSError **)outError
{
    vec2 imageSize;
    GLuint target = GL_TEXTURE_2D;
    GLuint name = __Texture2DLoad(url, Texture2DScaleModeLinear, &imageSize);
    return [[GLKTextureInfo alloc] initWithTarget:target name:name width:(GLuint)imageSize.x height:(GLuint)imageSize.y];
}

+ (GLKTextureInfo*)cubeMapWithContentsOfURL:(NSURL *)url
                                    options:(NSDictionary *)options
                                      error:(NSError **)outError
{
    throw std::runtime_error("-[GLKTextureInfo cubeMapWithContentsOfURL:options:error:] is not implemented yet.");
    return nil;
}

@end

