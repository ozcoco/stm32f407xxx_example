//
// Created by ozcom on 2025/4/10.
//

#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

#include "main.h"
#include "spi.h"
#include "delay/delay.h"

/**
 * @brief 定义是否启用不同型号的LCD
 *
 * 每个宏的值为 0 表示不启用该型号的LCD，为 1 表示启用。
 */
// 不启用 GC9A01 型号的 LCD
#define US_LCD_GC9A01_ON 0
// 启用 ST7789V2 型号的 LCD
#define US_LCD_ST7789V2_ON 1
// 不启用 ST7735S 型号的 LCD
#define US_LCD_ST7735S_ON 0

/**
 * @brief 定义与 LCD 通信使用的 SPI 句柄
 *
 * 此句柄用于指定与 LCD 进行数据传输的 SPI 接口。
 */
#define US_DISPLAY_SPI_HANDLE hspi1

/**
 * @brief 定义数据/命令控制引脚（DC）相关信息
 *
 * 包括该引脚的 GPIO 端口和引脚号。
 */
// 数据/命令控制引脚的 GPIO 端口
#define US_DISPLAY_DC_GPIO_PORT DISPLAY_DC_GPIO_Port
// 数据/命令控制引脚的引脚号
#define US_DISPLAY_DC_PIN DISPLAY_DC_Pin

/**
 * @brief 定义片选引脚（CS）相关信息
 *
 * 包括该引脚的 GPIO 端口和引脚号。
 */
// 片选引脚的 GPIO 端口
#define US_DISPLAY_CS_GPIO_PORT DISPLAY_CS_GPIO_Port
// 片选引脚的引脚号
#define US_DISPLAY_CS_PIN DISPLAY_CS_Pin

/**
 * @brief 定义复位引脚（RST）相关信息
 *
 * 包括该引脚的 GPIO 端口和引脚号。
 */
// 复位引脚的 GPIO 端口
#define US_DISPLAY_RST_GPIO_PORT DISPLAY_RST_GPIO_Port
// 复位引脚的引脚号
#define US_DISPLAY_RST_PIN DISPLAY_RST_Pin

/**
 * @brief 设置数据/命令控制引脚为数据模式
 *
 * 通过将 DC 引脚置高来指示接下来传输的是数据。
 */
#define US_LCD_DC_DATA() HAL_GPIO_WritePin(US_DISPLAY_DC_GPIO_PORT, US_DISPLAY_DC_PIN, GPIO_PIN_SET)

/**
 * @brief 设置数据/命令控制引脚为命令模式
 *
 * 通过将 DC 引脚置低来指示接下来传输的是命令。
 */
#define US_LCD_DC_CMD() HAL_GPIO_WritePin(US_DISPLAY_DC_GPIO_PORT, US_DISPLAY_DC_PIN, GPIO_PIN_RESET)

/**
 * @brief 选中片选引脚
 *
 * 通过将 CS 引脚置低来选中 LCD 设备。
 */
#define US_LCD_CS_SELECT() HAL_GPIO_WritePin(US_DISPLAY_CS_GPIO_PORT, US_DISPLAY_CS_PIN, GPIO_PIN_RESET)

/**
 * @brief 取消选中片选引脚
 *
 * 通过将 CS 引脚置高来取消选中 LCD 设备。
 */
#define US_LCD_CS_UNSELECT() HAL_GPIO_WritePin(US_DISPLAY_CS_GPIO_PORT, US_DISPLAY_CS_PIN, GPIO_PIN_SET)

/**
 * @brief 设置复位引脚为高电平
 *
 * 通过将 RST 引脚置高来使 LCD 设备退出复位状态。
 */
#define US_LCD_RST_SET() HAL_GPIO_WritePin(US_DISPLAY_RST_GPIO_PORT, US_DISPLAY_RST_PIN, GPIO_PIN_SET)

/**
 * @brief 设置复位引脚为低电平
 *
 * 通过将 RST 引脚置低来使 LCD 设备进入复位状态。
 */
#define US_LCD_RST_Clear() HAL_GPIO_WritePin(US_DISPLAY_RST_GPIO_PORT, US_DISPLAY_RST_PIN, GPIO_PIN_RESET)

/**
 * @brief 通过 SPI 使用 DMA 传输数据到 LCD
 *
 * @param pdata 指向要发送的数据的指针
 * @param len 要发送的数据的长度
 *
 * 此宏会启动 DMA 传输，并等待传输完成。
 */
#define US_LCD_WRITE_DATA(pdata,len) do{ \
                                        HAL_SPI_Transmit_DMA(&US_DISPLAY_SPI_HANDLE, pdata, len); \
                                        while (US_DISPLAY_SPI_HANDLE.State != HAL_DMA_STATE_READY); \
                                        }while(0)

/**
 * @brief 通过 SPI 发送单字节命令到 LCD
 *
 * @param data 要发送的命令字节
 *
 * 此宏会调用 US_LCD_WRITE_DATA 宏来发送一个字节的命令。
 */
#define US_LCD_WRITE_CMD(data) US_LCD_WRITE_DATA(&data,1)

/**
 * @brief 通过 SPI 发送单字节数据到 LCD
 *
 * @param data 要发送的数据字节
 *
 * 此宏会调用 US_LCD_WRITE_DATA 宏来发送一个字节的数据。
 */
#define US_LCD_WRITE_DATA_BYTE(data) US_LCD_WRITE_DATA(&data,1)

/**
 * @brief 实现 LCD 延迟毫秒的功能
 *
 * @param ms 要延迟的毫秒数
 *
 * 此宏会调用 US_DELAY_MS 函数来实现指定毫秒数的延迟。
 */
#define US_LCD_DELAY_MS(ms) US_DELAY_MS(ms)

/**
 * @brief 实现 LCD 延迟微秒的功能
 *
 * @param us 要延迟的微秒数
 *
 * 此宏会调用 US_DELAY_US 函数来实现指定微秒数的延迟。
 */
#define US_LCD_DELAY_US(us) US_DELAY_US(us)


#endif //LCD_CONFIG_H
