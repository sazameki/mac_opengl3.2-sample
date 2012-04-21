//
//  GLXLog.cpp
//
//  Created by Satoshi Numata on 10/01/10.
//  Copyright (c) 2012 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#include "GLXLog.h"
#include <cstdarg>
#include <cstdio>
#include <sys/time.h>


void _GLXLogImpl(const char* format, ...)
{
    static char buffer[1024];
    va_list marker;
    va_start(marker, format);
    vsprintf(buffer, format, marker);
    va_end(marker);
    
    timeval tp;
    gettimeofday(&tp, NULL);
    
    time_t theTime = time(NULL);
    tm* date = localtime(&theTime);
    
    static char dateBuffer[16];
    strftime(dateBuffer, 15, "%H:%M:%S", date);
    
    printf("[%s.%02d] %s\n", dateBuffer, tp.tv_usec / 10000, buffer);
}

