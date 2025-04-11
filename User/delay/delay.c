//
// Created by ozcom on 2024/1/8.
//
#include "delay.h"

void delay_us(const uint32_t us)
{
    uint32_t temp;
    SysTick->LOAD = HAL_RCC_GetHCLKFreq()/1000000/8*us;
    SysTick->VAL = 0X00;
    SysTick->CTRL = 0X01;
    do {
        temp = SysTick->CTRL;
    }
    while ((temp & 0x01) && (!(temp & (1 << 16))));
    SysTick->CTRL = 0x00;
    SysTick->VAL = 0X00;
}

void delay_ms(const uint16_t ms)
{
    uint32_t temp;
    SysTick->LOAD = HAL_RCC_GetHCLKFreq()/1000/8*ms;
    SysTick->VAL = 0X00;
    SysTick->CTRL = 0X01;
    do {
        temp = SysTick->CTRL;
    }
    while ((temp & 0x01) && (!(temp & (1 << 16))));
    SysTick->CTRL = 0x00;
    SysTick->VAL = 0X00;
}
