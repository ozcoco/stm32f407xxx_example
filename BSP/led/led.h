//
// Created by ozcom on 2025/3/30.
//
#pragma once

#ifdef USE_BSP_LED

#ifndef LED_H
#define LED_H

#include "main.h"

// 控制 LED0 的状态
#define LED0(state) do { HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, state); } while (0)

// 控制 LED1 的状态
#define LED1(state) do { HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state); } while (0)

// // 控制 LED0 的状态
// inline void LED0(const uint8_t state)
// {
//     HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, state);
// }
//
// // 控制 LED1 的状态
// inline void LED1(const uint8_t state)
// {
//     HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state);
// }

#endif //LED_H
#endif //USE_BSP_LED
