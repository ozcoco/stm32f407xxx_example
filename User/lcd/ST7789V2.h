//
// Created by ozcom on 2025/4/10.
//

#ifndef ST7789V2_H
#define ST7789V2_H

#include "lcd_config.h"
#include "stdint.h"
#include "font.h"

/* Choose a type you are using */
// 选择使用的LCD屏幕类型
//#define USING_135X240
// #define USING_240X240
#define USING_240X280
//#define USING_170X320

/* Choose a display rotation you want to use: (0-3) */
// 选择显示屏的旋转角度，取值范围为 0 - 3
// #define ST7789_ROTATION 0
//#define ST7789_ROTATION 1
#define ST7789_ROTATION 2				//  use Normally on 240x240
//#define ST7789_ROTATION 3

#ifdef USING_135X240
// 如果选择了 135x240 分辨率的屏幕
#if ST7789_ROTATION == 0
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 53
        #define Y_SHIFT 40
        // 当旋转角度为 0 时，定义屏幕的宽度、高度以及 X 和 Y 方向的偏移量
#endif

#if ST7789_ROTATION == 1
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 52
        // 当旋转角度为 1 时，定义屏幕的宽度、高度以及 X 和 Y 方向的偏移量
#endif

#if ST7789_ROTATION == 2
        #define ST7789_WIDTH 135
        #define ST7789_HEIGHT 240
        #define X_SHIFT 52
        #define Y_SHIFT 40
        // 当旋转角度为 2 时，定义屏幕的宽度、高度以及 X 和 Y 方向的偏移量
#endif

#if ST7789_ROTATION == 3
        #define ST7789_WIDTH 240
        #define ST7789_HEIGHT 135
        #define X_SHIFT 40
        #define Y_SHIFT 53
        // 当旋转角度为 3 时，定义屏幕的宽度、高度以及 X 和 Y 方向的偏移量
#endif

#endif

#ifdef USING_240X240
// 如果选择了 240x240 分辨率的屏幕
    #define ST7789_WIDTH 240
    #define ST7789_HEIGHT 240
    // 定义屏幕的宽度和高度

#if ST7789_ROTATION == 0
			#define X_SHIFT 0
			#define Y_SHIFT 80
			// 当旋转角度为 0 时，定义 X 和 Y 方向的偏移量
#elif ST7789_ROTATION == 1
			#define X_SHIFT 80
			#define Y_SHIFT 0
			// 当旋转角度为 1 时，定义 X 和 Y 方向的偏移量
#elif ST7789_ROTATION == 2
			#define X_SHIFT 0
			#define Y_SHIFT 0
			// 当旋转角度为 2 时，定义 X 和 Y 方向的偏移量
#elif ST7789_ROTATION == 3
			#define X_SHIFT 0
			#define Y_SHIFT 0
			// 当旋转角度为 3 时，定义 X 和 Y 方向的偏移量
#endif

#endif

#ifdef USING_240X280
// 如果选择了 240x280 分辨率的屏幕
#define ST7789_WIDTH 240
#define ST7789_HEIGHT 280
// 定义屏幕的宽度和高度

#if ST7789_ROTATION == 0
            #define X_SHIFT 0
            #define Y_SHIFT 80
            // 当旋转角度为 0 时，定义 X 和 Y 方向的偏移量
#elif ST7789_ROTATION == 1
            #define X_SHIFT 80
            #define Y_SHIFT 0
            // 当旋转角度为 1 时，定义 X 和 Y 方向的偏移量
#elif ST7789_ROTATION == 2
#define X_SHIFT 0
#define Y_SHIFT 20
// 当旋转角度为 2 时，定义 X 和 Y 方向的偏移量
#elif ST7789_ROTATION == 3
            #define X_SHIFT 0
            #define Y_SHIFT 0
            // 当旋转角度为 3 时，定义 X 和 Y 方向的偏移量
#endif

#endif

#ifdef USING_170X320
// 如果选择了 170x320 分辨率的屏幕
#if ST7789_ROTATION == 0
        #define ST7789_WIDTH 170
        #define ST7789_HEIGHT 320
        #define X_SHIFT 35
        #define Y_SHIFT 0
        // 当旋转角度为 0 时，定义屏幕的宽度、高度以及 X 和 Y 方向的偏移量
#endif

#if ST7789_ROTATION == 1
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 170
        #define X_SHIFT 0
        #define Y_SHIFT 35
        // 当旋转角度为 1 时，定义屏幕的宽度、高度以及 X 和 Y 方向的偏移量
#endif

#if ST7789_ROTATION == 2
        #define ST7789_WIDTH 170
        #define ST7789_HEIGHT 320
        #define X_SHIFT 35
        #define Y_SHIFT 0
        // 当旋转角度为 2 时，定义屏幕的宽度、高度以及 X 和 Y 方向的偏移量
#endif

#if ST7789_ROTATION == 3
        #define ST7789_WIDTH 320
        #define ST7789_HEIGHT 170
        #define X_SHIFT 0
        #define Y_SHIFT 35
        // 当旋转角度为 3 时，定义屏幕的宽度、高度以及 X 和 Y 方向的偏移量
#endif

#endif

/* Control Registers and constant codes */
// 控制寄存器和常量代码定义
#define ST7789_NOP     0x00
#define ST7789_SWRESET 0x01
#define ST7789_RDDID   0x04
#define ST7789_RDDST   0x09

#define ST7789_SLPIN   0x10
#define ST7789_SLPOUT  0x11
#define ST7789_PTLON   0x12
#define ST7789_NORON   0x13

#define ST7789_INVOFF  0x20
#define ST7789_INVON   0x21
#define ST7789_DISPOFF 0x28
#define ST7789_DISPON  0x29
#define ST7789_CASET   0x2A
#define ST7789_RASET   0x2B
#define ST7789_RAMWR   0x2C
#define ST7789_RAMRD   0x2E

#define ST7789_PTLAR   0x30
#define ST7789_COLMOD  0x3A
#define ST7789_MADCTL  0x36

/**
 * Memory Data Access Control Register (0x36H)
 * MAP:     D7  D6  D5  D4  D3  D2  D1  D0
 * param:   MY  MX  MV  ML  RGB MH  -   -
 * 内存数据访问控制寄存器 (0x36H)
 * 位映射:     D7  D6  D5  D4  D3  D2  D1  D0
 * 参数含义:   MY  MX  MV  ML  RGB MH  -   -
 */

/* Page Address Order ('0': Top to Bottom, '1': the opposite) */
#define ST7789_MADCTL_MY  0x80
// 页地址顺序 ('0': 从上到下, '1': 相反)

/* Column Address Order ('0': Left to Right, '1': the opposite) */
#define ST7789_MADCTL_MX  0x40
// 列地址顺序 ('0': 从左到右, '1': 相反)

/* Page/Column Order ('0' = Normal Mode, '1' = Reverse Mode) */
#define ST7789_MADCTL_MV  0x20
// 页/列顺序 ('0' = 正常模式, '1' = 反转模式)

/* Line Address Order ('0' = LCD Refresh Top to Bottom, '1' = the opposite) */
#define ST7789_MADCTL_ML  0x10
// 行地址顺序 ('0' = LCD 从上到下刷新, '1' = 相反)

/* RGB/BGR Order ('0' = RGB, '1' = BGR) */
#define ST7789_MADCTL_RGB 0x00
// RGB/BGR 顺序 ('0' = RGB, '1' = BGR)

#define ST7789_RDID1   0xDA
#define ST7789_RDID2   0xDB
#define ST7789_RDID3   0xDC
#define ST7789_RDID4   0xDD

/* Advanced options */
// 高级选项
#define ST7789_COLOR_MODE_16bit 0x55    //  RGB565 (16bit)
#define ST7789_COLOR_MODE_18bit 0x66    //  RGB666 (18bit)
// 定义 16 位和 18 位颜色模式

#if defined(USE_USER_LCD) && US_LCD_ST7789V2_ON == 1

/**
 * @brief 初始化 ST7789V2 LCD 显示屏。
 *
 * 此函数用于初始化 ST7789V2 LCD 显示屏，包括设置初始参数、发送初始化命令等。
 */
void ST7789V2_Init(void);

/**
 * @brief 设置 ST7789V2 LCD 显示屏的旋转角度。
 *
 * @param m 旋转角度，取值范围为 0 - 3。
 */
void ST7789_SetRotation(uint8_t m);

/**
 * @brief 用指定颜色填充整个 ST7789V2 LCD 显示屏。
 *
 * @param color 填充颜色，使用 RGB565 格式。
 */
void ST7789_Fill_Color(uint16_t color);

/**
 * @brief 在指定位置绘制一个像素点。
 *
 * @param x 像素点的 x 坐标。
 * @param y 像素点的 y 坐标。
 * @param color 像素点的颜色，使用 RGB565 格式。
 */
void ST7789_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

/**
 * @brief 在指定区域填充指定颜色。
 *
 * @param xSta 区域的起始 x 坐标。
 * @param ySta 区域的起始 y 坐标。
 * @param xEnd 区域的结束 x 坐标。
 * @param yEnd 区域的结束 y 坐标。
 * @param color 填充颜色，使用 RGB565 格式。
 */
void ST7789_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd, uint16_t color);

/**
 * @brief 在指定位置绘制一个 4x4 像素的点。
 *
 * @param x 点的 x 坐标。
 * @param y 点的 y 坐标。
 * @param color 点的颜色，使用 RGB565 格式。
 */
void ST7789_DrawPixel_4px(uint16_t x, uint16_t y, uint16_t color);

/* Graphical functions. */
// 图形绘制函数

/**
 * @brief 在指定两点之间绘制一条直线。
 *
 * @param x1 起点的 x 坐标。
 * @param y1 起点的 y 坐标。
 * @param x2 终点的 x 坐标。
 * @param y2 终点的 y 坐标。
 * @param color 直线的颜色，使用 RGB565 格式。
 */
void ST7789_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

/**
 * @brief 绘制一个矩形。
 *
 * @param x1 矩形左上角的 x 坐标。
 * @param y1 矩形左上角的 y 坐标。
 * @param x2 矩形右下角的 x 坐标。
 * @param y2 矩形右下角的 y 坐标。
 * @param color 矩形的颜色，使用 RGB565 格式。
 */
void ST7789_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

/**
 * @brief 绘制一个圆形。
 *
 * @param x0 圆心的 x 坐标。
 * @param y0 圆心的 y 坐标。
 * @param r 圆的半径。
 * @param color 圆的颜色，使用 RGB565 格式。
 */
void ST7789_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);

/**
 * @brief 在指定位置绘制一幅图像。
 *
 * @param x 图像左上角的 x 坐标。
 * @param y 图像左上角的 y 坐标。
 * @param w 图像的宽度。
 * @param h 图像的高度。
 * @param data 图像数据，使用 RGB565 格式。
 */
void ST7789_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);

/**
 * @brief 反转显示屏的颜色。
 *
 * @param invert 反转标志，非零值表示反转，零值表示不反转。
 */
void ST7789_InvertColors(uint8_t invert);

/* Text functions. */
// 文本绘制函数

/**
 * @brief 在指定位置写入一个字符。
 *
 * @param x 字符的起始 x 坐标。
 * @param y 字符的起始 y 坐标。
 * @param ch 要写入的字符。
 * @param font 字符的字体定义。
 * @param color 字符的颜色，使用 RGB565 格式。
 * @param bgcolor 字符的背景颜色，使用 RGB565 格式。
 */
void ST7789_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);

/**
 * @brief 在指定位置写入一个字符串。
 *
 * @param x 字符串的起始 x 坐标。
 * @param y 字符串的起始 y 坐标。
 * @param str 要写入的字符串。
 * @param font 字符串的字体定义。
 * @param color 字符串的颜色，使用 RGB565 格式。
 * @param bgcolor 字符串的背景颜色，使用 RGB565 格式。
 */
void ST7789_WriteString(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor);

/* Extented Graphical functions. */
// 扩展图形绘制函数

/**
 * @brief 绘制一个填充的矩形。
 *
 * @param x 矩形左上角的 x 坐标。
 * @param y 矩形左上角的 y 坐标。
 * @param w 矩形的宽度。
 * @param h 矩形的高度。
 * @param color 矩形的填充颜色，使用 RGB565 格式。
 */
void ST7789_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

/**
 * @brief 绘制一个三角形。
 *
 * @param x1 第一个顶点的 x 坐标。
 * @param y1 第一个顶点的 y 坐标。
 * @param x2 第二个顶点的 x 坐标。
 * @param y2 第二个顶点的 y 坐标。
 * @param x3 第三个顶点的 x 坐标。
 * @param y3 第三个顶点的 y 坐标。
 * @param color 三角形的颜色，使用 RGB565 格式。
 */
void ST7789_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);

/**
 * @brief 绘制一个填充的三角形。
 *
 * @param x1 第一个顶点的 x 坐标。
 * @param y1 第一个顶点的 y 坐标。
 * @param x2 第二个顶点的 x 坐标。
 * @param y2 第二个顶点的 y 坐标。
 * @param x3 第三个顶点的 x 坐标。
 * @param y3 第三个顶点的 y 坐标。
 * @param color 三角形的填充颜色，使用 RGB565 格式。
 */
void ST7789_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3,
                               uint16_t color);

/**
 * @brief 绘制一个填充的圆形。
 *
 * @param x0 圆心的 x 坐标。
 * @param y0 圆心的 y 坐标。
 * @param r 圆的半径。
 * @param color 圆的填充颜色，使用 RGB565 格式。
 */
void ST7789_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/* Command functions */
// 命令函数

/**
 * @brief 设置 ST7789V2 LCD 显示屏的撕裂效应。
 *
 * @param tear 撕裂效应标志，非零值表示启用，零值表示禁用。
 */
void ST7789_TearEffect(uint8_t tear);


#else

inline void ST7789V2_Init(void)
{
}

inline void ST7789V2_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
}

#endif

#endif //ST7789V2_H
