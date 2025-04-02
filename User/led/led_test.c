//
// Created by ozcom on 2025/3/31.
//

#include "led_test.h"
#include "string.h"
#include "led.h"
#include "log/log.h"
#include "flash/stm32_flash.h"

#define CMD_LED_0_ON 0x11
#define CMD_LED_0_OFF 0x10
#define CMD_LED_1_ON 0x21
#define CMD_LED_1_OFF 0x20

#define LED_STATE_SAVE_FLASH_ADDR (STM32_FLASH_SECTOR_3_ADDR+4)

typedef struct
{
    uint8_t led0_state;
    uint8_t led1_state;
} led_state_t;

// 定义LED状态结构体变量
static led_state_t led_state;

void led_init(void)
{
    // 读取LED状态
    led_state = *(__IO led_state_t*)LED_STATE_SAVE_FLASH_ADDR;
    LOGI("led0_state: led0_state=%d, led1_state=%d\n", led_state.led0_state, led_state.led1_state);
    // 如果LED0状态为0，则点亮LED0
    LED0(led_state.led0_state);
    // 如果LED1状态为0，则点亮LED1
    LED1(led_state.led1_state);
}

void on_led_cmd(const int32_t cmd)
{
    bool is_changed = true;
    switch (cmd)
    {
    case CMD_LED_0_ON:
        LED0(0);
        led_state.led0_state = 0;
        break; // 点亮LED0
    case CMD_LED_0_OFF:
        LED0(1);
        led_state.led0_state = 1;
        break; // 熄灭LED0
    case CMD_LED_1_ON:
        LED1(0);
        led_state.led1_state = 0;
        break; // 点亮LED1
    case CMD_LED_1_OFF:
        LED1(1);
        led_state.led1_state = 1;
        break; // 熄灭LED1
    default:
        is_changed = false;
        break;
    }
    //是否保存LED状态
    if (is_changed)
    {
        // 保存LED状态
        STM32_FLASH_WRITE(LED_STATE_SAVE_FLASH_ADDR, &led_state, sizeof(led_state_t));
    }
}
