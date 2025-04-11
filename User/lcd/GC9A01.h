//
// Created by ozcom on 2025/4/7.
//

#ifndef GC9A01_H
#define GC9A01_H

#include "lcd_config.h"
#include "stdint.h"

#if defined(USE_USER_LCD) && US_LCD_GC9A01_ON == 1

void GC9A01_Init(void);

void GC9A01_DrawPoint(uint16_t x, uint16_t y, uint16_t color);

#else

inline void GC9A01_Init(void)
{
}

inline void GC9A01_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
}

#endif

#endif //GC9A01_H
