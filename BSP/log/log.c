//
// Created by ozcom on 2023/8/10.
//
#include <stdbool.h>
#include "log.h"
#include "app_main.h"

void log_rx_enable(void)
{
    HAL_UARTEx_ReceiveToIdle_DMA(&LOG_INTERFACE, LogRxBuf, LOG_RX_MAX_SIZE);
    __HAL_DMA_DISABLE_IT(&LOG_INTERFACE_DMA_CHANNEL, DMA_IT_HT);
}

void log_i(const char* fmt, ...)
{
    while (LOG_INTERFACE.gState != HAL_UART_STATE_READY);
    va_list ap;
    va_start(ap, fmt);
    char buf[LOG_TX_MAX_SIZE] = {0};
    snprintf(buf, LOG_TX_MAX_SIZE, "[I/%s] ", __FILE_NAME__);
    vsnprintf(buf + strlen(buf), LOG_TX_MAX_SIZE - strlen(buf), fmt, ap);
    va_end(ap);
    HAL_UART_Transmit_DMA(&LOG_INTERFACE, (uint8_t*)buf, strlen(buf));
}

void log_d(const char* fmt, ...)
{
    while (LOG_INTERFACE.gState != HAL_UART_STATE_READY);
    va_list ap;
    va_start(ap, fmt);
    char buf[LOG_TX_MAX_SIZE] = {0};
    snprintf(buf, LOG_TX_MAX_SIZE, "[%s line:%d D/%s] ", __FILE_NAME__, __LINE__, __FUNCTION__);
    vsnprintf(buf + strlen(buf), LOG_TX_MAX_SIZE - strlen(buf), fmt, ap);
    va_end(ap);
    HAL_UART_Transmit_DMA(&LOG_INTERFACE, (uint8_t*)buf, strlen(buf));
}

void log_e(const char* fmt, ...)
{
    while (LOG_INTERFACE.gState != HAL_UART_STATE_READY);
    va_list ap;
    va_start(ap, fmt);
    char buf[LOG_TX_MAX_SIZE] = {0};
    snprintf(buf, LOG_TX_MAX_SIZE, "[%s line:%d E/%s] ", __FILE_NAME__, __LINE__, __FUNCTION__);
    vsnprintf(buf + strlen(buf), LOG_TX_MAX_SIZE - strlen(buf), fmt, ap);
    va_end(ap);
    HAL_UART_Transmit_DMA(&LOG_INTERFACE, (uint8_t*)buf, strlen(buf));
}

/** log rx **/
uint8_t LogRxBuf[LOG_RX_BUF_SIZE];

void log_rx_callback(uint16_t size)
{
    if (size <= LOG_RX_BUF_SIZE)
    {
        app_main.on_uart_rx(1, LogRxBuf, size);
    }
    else
    {
        LOGE("Log Rx buffer overflow\n");
    }
    memset(LogRxBuf, 0U, LOG_RX_BUF_SIZE);
    LOG_RX_ENABLE();
}
