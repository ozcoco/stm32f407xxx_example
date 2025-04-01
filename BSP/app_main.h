//
// Created by ozcom on 2025/3/31.
//

#ifndef APP_MAIN_H
#define APP_MAIN_H

#include <stdint.h>

typedef struct
{
    void* user;
    void (*on_init)(void);
    void (*on_begin)(void);
    void (*on_start)(void);
    uint8_t (*on_loop)(void);
    void (*on_end)(void);
    void (*on_uart_rx)(const uint8_t uart_num,const uint8_t* data, uint16_t size);
} app_main_t;

extern app_main_t app_main;

#endif //APP_MAIN_H
