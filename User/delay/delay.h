//
// Created by ozcom on 2024/1/8.
//

#ifndef FMC_TFT_LCD_DELAY_H
#define FMC_TFT_LCD_DELAY_H

#include "main.h"

#define US_DELAY_US(us) do{ \
                            uint32_t temp; \
                            SysTick->LOAD = HAL_RCC_GetHCLKFreq()/1000000/8*us; \
                            SysTick->VAL = 0X00; \
                            SysTick->CTRL = 0X01; \
                            do { \
                                temp = SysTick->CTRL; \
                            } \
                            while ((temp & 0x01) && (!(temp & (1 << 16)))); \
                            SysTick->CTRL = 0x00; \
                            SysTick->VAL = 0X00; \
                        }while(0)

// #define US_DELAY_MS(ms) do{ \
//                             uint32_t temp; \
//                                 SysTick->LOAD = HAL_RCC_GetHCLKFreq()/1000/8*ms; \
//                             SysTick->VAL = 0X00; \
//                             SysTick->CTRL = 0X01; \
//                             do { \
//                                 temp = SysTick->CTRL; \
//                             } \
//                             while ((temp & 0x01) && (!(temp & (1 << 16)))); \
//                             SysTick->CTRL = 0x00; \
//                             SysTick->VAL = 0X00; \
//                         }while(0)

#define US_DELAY_MS(ms) HAL_Delay(ms)

void delay_us(uint32_t us);

void delay_ms(uint16_t ms);

#endif //FMC_TFT_LCD_DELAY_H
