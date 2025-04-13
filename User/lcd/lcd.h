//
// Created by ozcom on 2025/4/7.
//

#ifndef LCD_H
#define LCD_H

#ifdef USE_USER_LCD

#include <stdint.h>

/**
 * @brief 初始化LCD设备。
 *
 * 此函数用于对LCD设备进行初始化操作，包括设置LCD的工作模式、初始化引脚等，
 * 确保LCD设备可以正常工作，为后续的显示操作做准备。
 */
void lcd_init(void);

/**
 * @brief 在LCD上显示内容。
 *
 * 此函数用于在已初始化的LCD设备上显示指定的内容。
 * 它会根据LCD的驱动和设置，将相应的数据发送到LCD，以实现内容的显示。
 */
void lcd_display(void);

/**
 * @brief 用指定颜色填充整个 ST7789V2 LCD 显示屏。
 *
 * @param color 填充颜色，使用 RGB565 格式。
 */
void LCD_Fill_Color(uint16_t color);

/**
 * @brief 在指定位置绘制一个像素点。
 *
 * @param x 像素点的 x 坐标。
 * @param y 像素点的 y 坐标。
 * @param color 像素点的颜色，使用 RGB565 格式。
 */
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);

/**
 * @brief 在指定区域填充指定颜色。
 *
 * @param xSta 区域的起始 x 坐标。
 * @param ySta 区域的起始 y 坐标。
 * @param xEnd 区域的结束 x 坐标。
 * @param yEnd 区域的结束 y 坐标。
 * @param color 填充颜色，使用 RGB565 格式。
 */
void LCD_Fill(uint16_t xSta, uint16_t ySta, uint16_t xEnd, uint16_t yEnd, uint16_t color);

/**
 * @brief 在指定位置绘制一个 4x4 像素的点。
 *
 * @param x 点的 x 坐标。
 * @param y 点的 y 坐标。
 * @param color 点的颜色，使用 RGB565 格式。
 */
void LCD_DrawPixel_4px(uint16_t x, uint16_t y, uint16_t color);

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
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

/**
 * @brief 绘制一个矩形。
 *
 * @param x1 矩形左上角的 x 坐标。
 * @param y1 矩形左上角的 y 坐标。
 * @param x2 矩形右下角的 x 坐标。
 * @param y2 矩形右下角的 y 坐标。
 * @param color 矩形的颜色，使用 RGB565 格式。
 */
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

/**
 * @brief 绘制一个圆形。
 *
 * @param x0 圆心的 x 坐标。
 * @param y0 圆心的 y 坐标。
 * @param r 圆的半径。
 * @param color 圆的颜色，使用 RGB565 格式。
 */
void LCD_DrawCircle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);

/**
 * @brief 在指定位置绘制一幅图像。
 *
 * @param x 图像左上角的 x 坐标。
 * @param y 图像左上角的 y 坐标。
 * @param w 图像的宽度。
 * @param h 图像的高度。
 * @param data 图像数据，使用 RGB565 格式。
 */
void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);

/**
 * @brief 反转显示屏的颜色。
 *
 * @param invert 反转标志，非零值表示反转，零值表示不反转。
 */
void LCD_InvertColors(uint8_t invert);

/* Text functions. */
// 文本绘制函数

/**
 * @brief 在指定位置写入一个字符。
 *
 * @param x 字符的起始 x 坐标。
 * @param y 字符的起始 y 坐标。
 * @param ch 要写入的字符。
 * @param color 字符的颜色，使用 RGB565 格式。
 * @param bgcolor 字符的背景颜色，使用 RGB565 格式。
 */
void LCD_WriteChar(uint16_t x, uint16_t y, char ch, uint16_t color, uint16_t bgcolor);

/**
 * @brief 在指定位置写入一个字符串。
 *
 * @param x 字符串的起始 x 坐标。
 * @param y 字符串的起始 y 坐标。
 * @param str 要写入的字符串。
 * @param color 字符串的颜色，使用 RGB565 格式。
 * @param bgcolor 字符串的背景颜色，使用 RGB565 格式。
 */
void LCD_WriteString(uint16_t x, uint16_t y, const char* str, uint16_t color, uint16_t bgcolor);

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
void LCD_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);

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
void LCD_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, uint16_t color);

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
void LCD_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3,
                               uint16_t color);

/**
 * @brief 绘制一个填充的圆形。
 *
 * @param x0 圆心的 x 坐标。
 * @param y0 圆心的 y 坐标。
 * @param r 圆的半径。
 * @param color 圆的填充颜色，使用 RGB565 格式。
 */
void LCD_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

/**
 * @brief 设置 ST7789V2 LCD 显示屏的撕裂效应。
 *
 * @param tear 撕裂效应标志，非零值表示启用，零值表示禁用。
 */
void LCD_TearEffect(uint8_t tear);


#else

inline void lcd_init(void){}

inline void lcd_display(void){}

#endif

#endif
