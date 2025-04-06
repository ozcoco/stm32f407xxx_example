//
// Created by ozcom on 2025/4/7.
//

#ifndef GC9A01_H
#define GC9A01_H

#include "stdint.h"

#ifdef USE_USER_LCD

void GC9A01_Init(void);

void GC9A01_DrawPoint(uint16_t x, uint16_t y, uint16_t color);

#else

inline void GC9A01_Init(void){}

inline void GC9A01_DrawPoint(uint16_t x, uint16_t y, uint16_t color){}

#endif

#endif //GC9A01_H
