//
// Created by ozcom on 2025/3/30.
//
#pragma once

#ifndef LED_H
#define LED_H

#include "main.h"

#ifdef USE_USER_LED

// 控制 LED0 的状态
#define LED0(state) do { HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, state); } while (0)
// 控制 LED1 的状态
#define LED1(state) do { HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, state); } while (0)

#else

// 控制 LED0 的状态
#define LED0(state) do {} while (0)
// 控制 LED1 的状态
#define LED1(state) do {} while (0)

#endif

#endif
