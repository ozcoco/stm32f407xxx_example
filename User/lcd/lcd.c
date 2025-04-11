//
// Created by ozcom on 2025/4/7.
//

#ifdef USE_USER_LCD

#include "lcd.h"
#include "lcd_config.h"

#if US_LCD_GC9A01_ON == 1
#include "GC9A01.h"

static void GC9A01_Display(void);

#endif

#if US_LCD_ST7789V2_ON == 1
#include "ST7789V2.h"

static void ST7789V2_Display(void);

#endif


void lcd_init(void)
{
#if US_LCD_GC9A01_ON
    GC9A01_Init();
#endif

#if US_LCD_ST7789V2_ON
    ST7789V2_Init();
#endif
    // 显示
    lcd_display();
}

void lcd_display(void)
{
#if US_LCD_GC9A01_ON
    GC9A01_Display();
#endif

#if US_LCD_ST7789V2_ON
    ST7789V2_Display();
#endif
}


#if US_LCD_GC9A01_ON == 1

static void GC9A01_Display(void)
{
    // todo
}

#endif

#if US_LCD_ST7789V2_ON == 1

static void ST7789V2_Display(void)
{
	ST7789_Fill_Color(WHITE);
	// US_LCD_DELAY_MS(1000);
	ST7789_WriteString(10, 20, "Speed Test", Font_11x18, RED, WHITE);
	// US_LCD_DELAY_MS(1000);
	ST7789_Fill_Color(CYAN);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(RED);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(BLUE);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(GREEN);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(YELLOW);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(BROWN);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(DARKBLUE);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(MAGENTA);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(LIGHTGREEN);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(LGRAY);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(LBBLUE);
    // US_LCD_DELAY_MS(500);
	ST7789_Fill_Color(WHITE);
	// US_LCD_DELAY_MS(500);

	ST7789_WriteString(10, 10, "Font test.", Font_16x26, GBLUE, WHITE);
	ST7789_WriteString(10, 50, "Hello Steve!", Font_7x10, RED, WHITE);
	ST7789_WriteString(10, 75, "Hello Steve!", Font_11x18, YELLOW, WHITE);
	ST7789_WriteString(10, 100, "Hello Steve!", Font_16x26, MAGENTA, WHITE);
	// US_LCD_DELAY_MS(100);

	ST7789_Fill_Color(RED);
	ST7789_WriteString(10, 10, "Rect./Line.", Font_11x18, YELLOW, BLACK);
	ST7789_DrawRectangle(30, 30, 100, 100, WHITE);
	// US_LCD_DELAY_MS(100);

	ST7789_Fill_Color(RED);
	ST7789_WriteString(10, 10, "Filled Rect.", Font_11x18, YELLOW, BLACK);
	ST7789_DrawFilledRectangle(30, 30, 50, 50, WHITE);
	// US_LCD_DELAY_MS(100);

	ST7789_Fill_Color(RED);
	ST7789_WriteString(10, 10, "Circle.", Font_11x18, YELLOW, BLACK);
	ST7789_DrawCircle(60, 60, 25, WHITE);
	// US_LCD_DELAY_MS(100);

	ST7789_Fill_Color(RED);
	ST7789_WriteString(10, 10, "Filled Cir.", Font_11x18, YELLOW, BLACK);
	ST7789_DrawFilledCircle(60, 60, 25, WHITE);
	// US_LCD_DELAY_MS(100);

	ST7789_Fill_Color(RED);
	ST7789_WriteString(10, 10, "Triangle", Font_11x18, YELLOW, BLACK);
	ST7789_DrawTriangle(30, 30, 30, 70, 60, 40, WHITE);
	// US_LCD_DELAY_MS(100);

	ST7789_Fill_Color(RED);
	ST7789_WriteString(10, 10, "Filled Tri", Font_11x18, YELLOW, BLACK);
	ST7789_DrawFilledTriangle(30, 30, 30, 70, 60, 40, WHITE);
	// US_LCD_DELAY_MS(100);

	//	If FLASH cannot storage anymore datas, please delete codes below.
	ST7789_Fill_Color(WHITE);
	ST7789_DrawImage(0, 0, 128, 128, (uint16_t *)saber);
	// US_LCD_DELAY_MS(3000);
}

#endif

#endif
