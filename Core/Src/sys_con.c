//
// Created by ozcom on 2025/3/31.
//

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
