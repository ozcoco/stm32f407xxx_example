//
// Created by ozcom on 2025/3/31.
//

#include "i2c.h"
#include "usart.h"

/** 串口连接，接收回调 **/

extern void log_rx_callback(uint16_t size);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t size)
{
    if (huart == &huart1)
    {
        log_rx_callback(size);
    }
}

/** 串口连接，接收回调 **/


/** I2C中断 **/

extern void i2c_rx_callback(const uint8_t uart_num);
extern void i2c_tx_callback(const uint8_t uart_num);
extern void i2c_err_callback(const uint8_t uart_num);
extern void i2c_abort_callback(const uint8_t uart_num);

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef* hi2c)
{
    if (hi2c == &hi2c1)
    {
        i2c_rx_callback(1);
    }
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef* hi2c)
{
    if (hi2c == &hi2c1)
    {
        i2c_tx_callback(1);
    }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef* hi2c)
{
    if (hi2c == &hi2c1)
    {
        i2c_err_callback(1);
    }
}

void HAL_I2C_AbortCpltCallback(I2C_HandleTypeDef* hi2c)
{
    if (hi2c == &hi2c1)
    {
        i2c_abort_callback(1);
    }
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c == &hi2c1)
    {
        i2c_tx_callback(1);
    }
}
void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c == &hi2c1)
    {
        i2c_rx_callback(1);
    }
}

/** I2C中断 **/
