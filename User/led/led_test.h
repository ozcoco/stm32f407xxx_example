//
// Created by ozcom on 2025/3/31.
//

#ifndef LED_TEST_H
#define LED_TEST_H

#include "stdint.h"

#define CMD_LED_0_ON 0x11
#define CMD_LED_0_OFF 0x10
#define CMD_LED_1_ON 0x21
#define CMD_LED_1_OFF 0x20

void led_init(void);

void on_led_cmd(int32_t data);

#endif //LED_TEST_H
