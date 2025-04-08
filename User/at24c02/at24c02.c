//
// Created by ozcom on 2025/4/8.
//

#ifdef USE_USER_AT24C02

#include "at24c02.h"
#include "i2c.h"
#include "log/log.h"
#include "delay/delay.h"

#define US_AT24C02_ADDR 0xA0

static void at24c02_read(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, len,
                                                      HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        LOGE("at24c02 read error, status=%d", status);
    }
}

static void at24c02_write(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, len,
                                                       HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        LOGE("at24c02 write error, status=%d", status);
    }
}

static void at24c02_read_it(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    const HAL_StatusTypeDef status =
        HAL_I2C_Mem_Read_IT(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data, len);
    if (status != HAL_OK)
    {
        LOGE("at24c02 it read error, status=%d", status);
    }
}

static void at24c02_write_it(const uint16_t addr, uint8_t* data, const uint16_t len)
{
    const HAL_StatusTypeDef status = HAL_I2C_Mem_Write_IT(&hi2c1, US_AT24C02_ADDR, addr, I2C_MEMADD_SIZE_8BIT, data,
                                                          len);
    if (status != HAL_OK)
    {
        LOGE("at24c02 it write error, status=%d", status);
    }
}

static uint8_t readData2 = 0;

void at24c02_init(void)
{
    uint8_t data = 0x55;
    uint8_t addr = 0x00;
    at24c02_write(addr, &data, sizeof(data));
    delay_ms(100);
    uint8_t readData = 0;
    at24c02_read(addr, &readData, sizeof(readData));
    delay_ms(100);
    LOGI("at24c02_init: readData=0x%02X \n", readData);
    data += 2;
    addr += 1;
    at24c02_write_it(addr, &data, sizeof(data));
    delay_ms(100);
}

static uint8_t data = 0x55;
static volatile uint8_t addr = 0x00;

void at24c02_print(void)
{
}


void on_at24c02_event(const uint8_t event)
{
    LOGI("on_at24c02_event event=%d \n", event);
    switch (event)
    {
    case US_AT24C02_EVENT_RX_COMPLETE:
        {
            LOGI("on_at24c02_event: RX complete readData2=0x%02X \n", readData2);
            data += 2;
            addr += 1;
            at24c02_write_it(addr, &data, sizeof(data));
        }
        break;
    case US_AT24C02_EVENT_TX_COMPLETE:
        {
            at24c02_read_it(addr, &readData2, sizeof(readData2));
        }
        break;
    case US_AT24C02_EVENT_ERROR:
        break;
    default:
        break;
    }
}


#endif
