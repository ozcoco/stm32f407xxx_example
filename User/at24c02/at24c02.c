//
// Created by ozcom on 2025/4/8.
//

#include <sys/types.h>
#ifdef USE_USER_AT24C02

#include "at24c02.h"
#include "i2c.h"
#include "log/log.h"
#include "delay/delay.h"

#define US_EXAMPLE_I2C_POLLING_ON 1
#define US_EXAMPLE_I2C_IT_ON 1
#define US_EXAMPLE_I2C_DMA_ON 0

#define US_AT24C02_ADDR 0xA0

//
// Polling和中断方式读取和写入AT24C02
//
#if (US_EXAMPLE_I2C_IT_ON == 1 && US_EXAMPLE_I2C_POLLING_ON == 1)

static void us_at24c02_read(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    if (HAL_I2C_IsDeviceReady(&hi2c1, US_AT24C02_ADDR, 1, 1000) != HAL_OK)
    {
        LOGE("at24c02_read: device not ready, DevAddr=%d", addr);
        return;
    }
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, len,
                                                      HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        LOGE("at24c02 read error, status=%d", status);
    }
}

static void us_at24c02_write(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    if (HAL_I2C_IsDeviceReady(&hi2c1, US_AT24C02_ADDR, 1, 1000) != HAL_OK)
    {
        LOGE("at24c02_write: device not ready, DevAddr=%d", addr);
        return;
    }
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, len,
                                                       HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        LOGE("at24c02 write error, status=%d", status);
    }
}

static void us_at24c02_read_it(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    if (HAL_I2C_IsDeviceReady(&hi2c1, US_AT24C02_ADDR, 1, 1000) != HAL_OK)
    {
        LOGE("at24c02_read_it: device not ready, DevAddr=%d", addr);
        return;
    }
    const HAL_StatusTypeDef status =
        HAL_I2C_Mem_Read_IT(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, len);
    if (status != HAL_OK)
    {
        LOGE("at24c02 it read error, status=%d", status);
    }
}

static void us_at24c02_write_it(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    if (HAL_I2C_IsDeviceReady(&hi2c1, US_AT24C02_ADDR, 1, 1000) != HAL_OK)
    {
        LOGE("at24c02_write_it: device not ready, DevAddr=%d", addr);
        return;
    }
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Write_IT(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data,
                                                          len);
    if (status != HAL_OK)
    {
        LOGE("at24c02 it write error, status=%d", status);
    }
}


static uint8_t readData2 = 0;
static uint8_t data = 0x55;
static volatile uint8_t addr = 0x00;

#endif


//
// DMA方式读取和写入AT24C02
//
#if US_EXAMPLE_I2C_DMA_ON == 1

static void us_at24c02_read_dma(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    if (HAL_I2C_IsDeviceReady(&hi2c1, US_AT24C02_ADDR, 1, 1000) != HAL_OK)
    {
        LOGE("at24c02_write_dma: device not ready, DevAddr=%d", addr);
        return;
    }
    const HAL_StatusTypeDef status =
        HAL_I2C_Mem_Read_DMA(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, len);
    if (status != HAL_OK)
    {
        LOGE("at24c02 dma read error, status=%d", status);
    }
}

static void us_at24c02_write_dma(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    if (HAL_I2C_IsDeviceReady(&hi2c1, US_AT24C02_ADDR, 1, 1000) != HAL_OK)
    {
        LOGE("at24c02_write_dma: device not ready, DevAddr=%d", addr);
        return;
    }
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Write_DMA(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data,
                                                           len);
    if (status != HAL_OK)
    {
        LOGE("at24c02 dma write error, status=%d", status);
    }
}

typedef struct
{
    __IO uint8_t w_data[1];
    __IO uint8_t r_data[1];
    __IO uint16_t addr;
    __IO uint8_t event;
} us_at24c02_t;

static us_at24c02_t at24c02 = {
    .w_data = {0},
    .r_data = {0},
    .addr = 0x00,
    .event = US_AT24C02_EVENT_NONE,
};

#endif

void at24c02_init(void)
{
#if (US_EXAMPLE_I2C_IT_ON == 1 && US_EXAMPLE_I2C_POLLING_ON == 1)
    {
        uint8_t data = 0x55;
        uint8_t addr = 0x00;
        us_at24c02_write(addr, &data, sizeof(data));
        delay_ms(100);
        uint8_t readData = 0;
        us_at24c02_read(addr, &readData, sizeof(readData));
        delay_ms(100);
        LOGI("at24c02_init: readData=0x%02X \n", readData);
        data += 2;
        addr += 1;
        us_at24c02_write_it(addr, &data, sizeof(data));
        delay_ms(100);
    }
#endif

#if US_EXAMPLE_I2C_DMA_ON == 1
    {
        // dma 写入数据
        us_at24c02_write_dma(at24c02.addr, at24c02.w_data, sizeof(at24c02.w_data));
        // delay_ms(100);
    }
#endif
}

void at24c02_print(void)
{
    LOGI("at24c02_print \n");
#if US_EXAMPLE_I2C_DMA_ON == 1
    {
        LOGI("\n at24c02_print event=%d \n", at24c02.event);
        switch (at24c02.event)
        {
        case US_AT24C02_EVENT_RX_COMPLETE:
            {
                LOGI("at24c02_print: w_data=%d \n", at24c02.r_data[0]);
                at24c02.addr += 1;
                at24c02.w_data[0] += 1;
                // dma 写入数据
                us_at24c02_write_dma(at24c02.addr, at24c02.w_data, sizeof(at24c02.w_data));
            }
            break;
        case US_AT24C02_EVENT_TX_COMPLETE:
            {
                // dma 读取数据
                us_at24c02_read_dma(at24c02.addr, at24c02.r_data, sizeof(at24c02.r_data));
            }
            break;
        case US_AT24C02_EVENT_ERROR:
            {
            }
            break;
        default:
            {
            }
        }
    }
#endif
}

void on_at24c02_event(const uint8_t event)
{
    LOGI("\n on_at24c02_event event=%d \n", event);
#if US_EXAMPLE_I2C_DMA_ON == 1
    at24c02.event = event;
#endif
    switch (event)
    {
    case US_AT24C02_EVENT_RX_COMPLETE:
        {
#if (US_EXAMPLE_I2C_IT_ON == 1 && US_EXAMPLE_I2C_POLLING_ON == 1)
            {
                LOGI("on_at24c02_event: RX complete readData2=0x%02X \n", readData2);
                data += 2;
                addr += 1;
                us_at24c02_write_it(addr, &data, sizeof(data));
            }
#endif

#if US_EXAMPLE_I2C_DMA_ON == 1
            {
                // LOGI("on_at24c02_event: RX complete at24c02.r_data=0x%d \n", at24c02.r_data[0]);
                // dma 写数据
                // at24c02.addr += 1;
                // at24c02.w_data[0] += 1;
                // us_at24c02_write_dma(at24c02.addr, at24c02.w_data, sizeof(at24c02.w_data));
                // // dma 读取数据
                // us_at24c02_read_dma(at24c02.addr, at24c02.r_data, sizeof(at24c02.r_data));
            }
#endif
        }
        break;
    case US_AT24C02_EVENT_TX_COMPLETE:
        {
#if (US_EXAMPLE_I2C_IT_ON == 1 && US_EXAMPLE_I2C_POLLING_ON == 1)
            {
                us_at24c02_read_it(addr, &readData2, sizeof(readData2));
            }
#endif

#if US_EXAMPLE_I2C_DMA_ON == 1
            {
                // dma 读取数据
                // us_at24c02_read_dma(at24c02.addr, at24c02.r_data, sizeof(at24c02.r_data));
            }
#endif
        }
        break;
    case US_AT24C02_EVENT_ERROR:
        break;
    default:
        break;
    }
}


#endif
