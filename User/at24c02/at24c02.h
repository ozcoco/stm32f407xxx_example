//
// Created by ozcom on 2025/4/8.
//

#ifndef AT24C02_H
#define AT24C02_H

#include "main.h"

#ifdef USE_USER_AT24C02

// 事件
#define US_AT24C02_EVENT_NONE 0b00000000U
#define US_AT24C02_EVENT_RX_COMPLETE 0b00000001U
#define US_AT24C02_EVENT_TX_COMPLETE 0b00000010U
#define US_AT24C02_EVENT_ERROR 0b00000100U

// DMA通道
extern DMA_HandleTypeDef hdma_i2c1_rx;
extern DMA_HandleTypeDef hdma_i2c1_tx;

void at24c02_init(void);

void at24c02_print(void);

void on_at24c02_event(const uint8_t event);

#else

inline void at24c02_init(void){}

inline void at24c02_print(void){}

inline void on_at24c02_event(uint8_t event){}

#endif

#endif //AT24C02_H
