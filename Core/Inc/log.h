//
// Created by ozcom on 2023/8/10.
//

#ifndef LOG_H
#define LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include "usart.h"
#include <stdbool.h>
#include <stdarg.h>
#include <malloc.h>

#define LOG_INTERFACE huart1
#define LOG_INTERFACE_DMA_CHANNEL hdma_usart1_rx

#define MYL_LOG_TX_MAX_SIZE 128U
#define MY_LOG_RX_BUF_SIZE 128U

#define MY_LOG_RX_MAX_SIZE (MY_LOG_RX_BUF_SIZE*2U)
extern uint8_t MyLogRxBuf[MY_LOG_RX_BUF_SIZE];

#define MY_LOG_RX_ENABLE() do{ \
                            HAL_UARTEx_ReceiveToIdle_DMA(&LOG_INTERFACE, MyLogRxBuf, MY_LOG_RX_MAX_SIZE); \
                            __HAL_DMA_DISABLE_IT(&LOG_INTERFACE_DMA_CHANNEL, DMA_IT_HT); \
                           }while(0U)

void my_log_rx_enable(void);

#define LOGI(...) do{ \
                    while (LOG_INTERFACE.gState!=HAL_UART_STATE_READY); \
                    char buf[MYL_LOG_TX_MAX_SIZE] = {0};          \
                    sprintf(buf, __VA_ARGS__);      \
                    HAL_UART_Transmit_DMA(&LOG_INTERFACE, (uint8_t *) buf, strlen(buf)); \
                    }while(0U)

void log_i(const char* fmt, ...);

#define LOGD(...) do{ \
                    while (LOG_INTERFACE.gState!=HAL_UART_STATE_READY); \
                    char buf[MYL_LOG_TX_MAX_SIZE] = {0};                  \
                    sprintf(buf, "[%s line:%d D/%s] ", __FILE_NAME__, __LINE__, __FUNCTION__);        \
                    sprintf(buf + strlen(buf), __VA_ARGS__);      \
                    HAL_UART_Transmit_DMA(&LOG_INTERFACE, (uint8_t *) buf, strlen(buf)); \
                    }while(0U)

void log_d(const char* fmt, ...);

#define LOGE(...) do{ \
                    while (LOG_INTERFACE.gState!=HAL_UART_STATE_READY); \
                    char buf[MYL_LOG_TX_MAX_SIZE] = {0};                  \
                    sprintf(buf, "[%s line:%d E/%s] ", __FILE_NAME__, __LINE__, __FUNCTION__);        \
                    sprintf(buf + strlen(buf), __VA_ARGS__);      \
                    HAL_UART_Transmit_DMA(&LOG_INTERFACE, (uint8_t *) buf, strlen(buf)); \
                    }while(0U)

void log_e(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif //LOG_H
