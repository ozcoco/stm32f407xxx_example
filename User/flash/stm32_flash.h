//
// Created by ozcom on 2025/4/2.
//

#ifndef FLASH_H
#define FLASH_H

#include "stdint.h"

#define STM32_FLASH_TIMEOUT 5000

#define STM32_FLASH_SECTOR_0_ADDR     ((uint32_t)0x08000000) //16 Kbytes
#define STM32_FLASH_SECTOR_1_ADDR     ((uint32_t)0x08004000) //16 Kbytes
#define STM32_FLASH_SECTOR_2_ADDR     ((uint32_t)0x08008000) //16 Kbytes
#define STM32_FLASH_SECTOR_3_ADDR     ((uint32_t)0x0800C000) //16 Kbytes
#define STM32_FLASH_SECTOR_4_ADDR     ((uint32_t)0x08010000) //64 Kbytes
#define STM32_FLASH_SECTOR_5_ADDR     ((uint32_t)0x08020000) //128 Kbytes
#define STM32_FLASH_SECTOR_6_ADDR     ((uint32_t)0x08040000) //128 Kbytes
#define STM32_FLASH_SECTOR_7_ADDR     ((uint32_t)0x08060000) //128 Kbytes
#define STM32_FLASH_SECTOR_8_ADDR     ((uint32_t)0x08080000) //128 Kbytes
#define STM32_FLASH_SECTOR_9_ADDR     ((uint32_t)0x080A0000) //128 Kbytes
#define STM32_FLASH_SECTOR_10_ADDR    ((uint32_t)0x080C0000) //128 Kbytes
#define STM32_FLASH_SECTOR_11_ADDR    ((uint32_t)0x080E0000) //128 Kbytes

#ifdef USE_USER_FLASH

uint8_t STM32_FLASH_WRITE(const uint32_t addr, const void *data, const uint32_t size);

#else

inline uint8_t STM32_FLASH_WRITE(const uint32_t addr, const void *data, const uint32_t size){}

#endif

#endif //FLASH_H
