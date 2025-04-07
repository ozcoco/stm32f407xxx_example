//
// Created by ozcom on 2025/4/7.
//

#include "i2c.h"
#ifdef USE_USER_MPU_6050

#include "i2c_utils.h"
#include "log/log.h"

#define US_I2C_TIMEOUT 1000

uint8_t US_I2C_MEM_READ(uint8_t slave_addr, uint8_t reg_addr, uint8_t* data, uint16_t len)
{
    HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Mem_Read(&US_I2C_HANDLE, slave_addr
                              , reg_addr,I2C_MEMADD_SIZE_8BIT, data, len,US_I2C_TIMEOUT);

    if (status != HAL_OK)
    {
        /* 检查通讯状态 */
        /* 总线出错处理 */
        LOGE("i2c read error, status: %d, reg_addr: %d \n", status, reg_addr);
        return status;
    }
    while (HAL_I2C_GetState(&US_I2C_HANDLE) != HAL_I2C_STATE_READY);
    /* 检查SENSOR是否就绪进行下一次读写操作 */
    while (HAL_I2C_IsDeviceReady(&US_I2C_HANDLE, slave_addr,
                                 US_I2C_TIMEOUT, US_I2C_TIMEOUT) == HAL_TIMEOUT);
    /* 等待传输结束 */
    while (HAL_I2C_GetState(&US_I2C_HANDLE) != HAL_I2C_STATE_READY);
    return 0;
}

uint8_t US_I2C_MEM_WRITE(uint8_t slave_addr, uint8_t reg_addr, uint8_t* data, uint16_t len)
{
    HAL_StatusTypeDef status = HAL_OK;
    status = HAL_I2C_Mem_Write(&US_I2C_HANDLE, slave_addr, reg_addr,
                               I2C_MEMADD_SIZE_8BIT, data, len,US_I2C_TIMEOUT);
    if (status != HAL_OK)
    {
        /* 检查通讯状态 */
        /* 总线出错处理 */
        LOGE("i2c read error, status: %d, reg_addr: %d \n", status, reg_addr);
        return status;
    }
    while (HAL_I2C_GetState(&US_I2C_HANDLE) != HAL_I2C_STATE_READY);
    /* 检查SENSOR是否就绪进行下一次读写操作 */
    while (HAL_I2C_IsDeviceReady(&US_I2C_HANDLE, slave_addr,
                                 US_I2C_TIMEOUT, US_I2C_TIMEOUT) == HAL_TIMEOUT);
    /* 等待传输结束 */
    while (HAL_I2C_GetState(&US_I2C_HANDLE) != HAL_I2C_STATE_READY);
    return 0;
}

#endif
