//
//  GLXLog.h
//
//  Created by Satoshi Numata on 10/01/10.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GLX_DEBUG_H__
#define __GLX_DEBUG_H__

#if defined(DEBUG)
#define GLXLog(...)     _GLXLogImpl(__VA_ARGS__)
#else
#define GLXLog(...)
#endif

/*!
    @function GLXLog
    @abstract 指定された書式で、デバッグ文字列を出力します。書式は printf() 関数と同じ書式を使用します。
    Debug ビルドでのみ有効になります。Release ビルドでは、何も行いません。
 */
void    _GLXLogImpl(const char* format, ...);

#endif  //#ifndef __GLX_DEBUG_H__

