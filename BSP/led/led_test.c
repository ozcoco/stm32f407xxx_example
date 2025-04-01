//
// Created by ozcom on 2025/3/31.
//

#include "led_test.h"
#include "string.h"
#include "led.h"
#include "log/log.h"

#define CMD_LED_0_ON 0x11
#define CMD_LED_0_OFF 0x10
#define CMD_LED_1_ON 0x21
#define CMD_LED_1_OFF 0x20

void on_led_cmd(const int32_t cmd)
{
    switch (cmd)
    {
    case CMD_LED_0_ON:
        LED0(0);
        break; // 点亮LED0
    case CMD_LED_0_OFF:
        LED0(1);
        break; // 熄灭LED0
    case CMD_LED_1_ON:
        LED1(0);
        break; // 点亮LED1
    case CMD_LED_1_OFF:
        LED1(1);
        break; // 熄灭LED1
    default:
        break;
    }
}
