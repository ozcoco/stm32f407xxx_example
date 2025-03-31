//
// Created by ozcom on 2025/3/31.
//

#ifndef APP_MAIN_H
#define APP_MAIN_H

typedef struct{
    void* user;
    void (*on_init)(void);
    void (*on_begin)(void);
    void (*on_start)(void);
    unsigned char (*on_loop)(void);
    void (*on_end)(void);
} app_main_t;

extern app_main_t app_main;

#endif //APP_MAIN_H
