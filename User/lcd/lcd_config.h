//
// Created by ozcom on 2025/4/10.
//

#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

#include "main.h"
#include "spi.h"
#include "delay/delay.h"

#define US_LCD_GC9A01_ON 0
#define US_LCD_ST7789V2_ON 1
#define US_LCD_ST7735S_ON 0
#define US_LCD_ST7735S_ON 0

#define US_DISPLAY_SPI_HANDLE hspi1
// dc
#define US_DISPLAY_DC_GPIO_PORT DISPLAY_DC_GPIO_Port
#define US_DISPLAY_DC_PIN DISPLAY_DC_Pin
// cs
#define US_DISPLAY_CS_GPIO_PORT DISPLAY_CS_GPIO_Port
#define US_DISPLAY_CS_PIN DISPLAY_CS_Pin
// rst
#define US_DISPLAY_RST_GPIO_PORT DISPLAY_RST_GPIO_Port
#define US_DISPLAY_RST_PIN DISPLAY_RST_Pin

#define US_LCD_DC_DATA() HAL_GPIO_WritePin(US_DISPLAY_DC_GPIO_PORT, US_DISPLAY_DC_PIN, GPIO_PIN_SET)
#define US_LCD_DC_CMD() HAL_GPIO_WritePin(US_DISPLAY_DC_GPIO_PORT, US_DISPLAY_DC_PIN, GPIO_PIN_RESET)

#define US_LCD_CS_SELECT() HAL_GPIO_WritePin(US_DISPLAY_CS_GPIO_PORT, US_DISPLAY_CS_PIN, GPIO_PIN_RESET)
#define US_LCD_CS_UNSELECT() HAL_GPIO_WritePin(US_DISPLAY_CS_GPIO_PORT, US_DISPLAY_CS_PIN, GPIO_PIN_SET)

#define US_LCD_RST_SET() HAL_GPIO_WritePin(US_DISPLAY_RST_GPIO_PORT, US_DISPLAY_RST_PIN, GPIO_PIN_SET)
#define US_LCD_RST_Clear() HAL_GPIO_WritePin(US_DISPLAY_RST_GPIO_PORT, US_DISPLAY_RST_PIN, GPIO_PIN_RESET)

#define US_LCD_WRITE_DATA(pdata,len) do{ \
                                        HAL_SPI_Transmit_DMA(&US_DISPLAY_SPI_HANDLE, pdata, len); \
                                        while (US_DISPLAY_SPI_HANDLE.State != HAL_DMA_STATE_READY); \
                                        }while(0)

#define US_LCD_WRITE_CMD(data) US_LCD_WRITE_DATA(&data,1)

#define US_LCD_WRITE_DATA_BYTE(data) US_LCD_WRITE_DATA(&data,1)

#define US_LCD_DELAY_MS(ms) US_DELAY_MS(ms)
#define US_LCD_DELAY_US(us) US_DELAY_US(us)

#endif //LCD_CONFIG_H
