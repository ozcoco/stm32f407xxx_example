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

void at24c02_init(void)
{
    uint8_t data = 0x55;
    const uint8_t addr = 0x00;
    at24c02_write(addr, &data, sizeof(data));
    delay_ms(100);
    uint8_t readData = 0;
    at24c02_read(addr, &readData, sizeof(readData));
    LOGI("at24c02_init: readData=0x%02X", readData);
}

#endif
