//
// Created by ozcom on 2025/4/2.
//

#ifdef USE_USER_FLASH

#include "stm32_flash.h"
#include "stm32f4xx_hal.h"

static uint32_t get_flash_selector(const uint32_t addr)
{
    if (addr < STM32_FLASH_SECTOR_1_ADDR) return FLASH_SECTOR_0; // Bank 0
    if (addr < STM32_FLASH_SECTOR_2_ADDR) return FLASH_SECTOR_1; // Bank 1
    if (addr < STM32_FLASH_SECTOR_3_ADDR) return FLASH_SECTOR_2; // Bank 2
    if (addr < STM32_FLASH_SECTOR_4_ADDR) return FLASH_SECTOR_3; // Bank 3
    if (addr < STM32_FLASH_SECTOR_5_ADDR) return FLASH_SECTOR_4; // Bank 4
    if (addr < STM32_FLASH_SECTOR_6_ADDR) return FLASH_SECTOR_5; // Bank 5
    if (addr < STM32_FLASH_SECTOR_7_ADDR) return FLASH_SECTOR_6; // Bank 6
    if (addr < STM32_FLASH_SECTOR_8_ADDR) return FLASH_SECTOR_7; // Bank 7
    if (addr < STM32_FLASH_SECTOR_9_ADDR) return FLASH_SECTOR_8; // Bank 8
    if (addr < STM32_FLASH_SECTOR_10_ADDR) return FLASH_SECTOR_9; // Bank 9
    if (addr < STM32_FLASH_SECTOR_11_ADDR) return FLASH_SECTOR_10; // Bank 10
    return FLASH_SECTOR_11;
}

uint8_t STM32_FLASH_WRITE(const uint32_t addr, const void* data, const uint32_t size)
{
    FLASH_EraseInitTypeDef erase_init;
    uint32_t sector_error = 0;
    const uint8_t* data_ptr = data;
    // 检查地址是否合法
    if (addr < STM32_FLASH_SECTOR_0_ADDR || addr >= STM32_FLASH_SECTOR_11_ADDR + 128 * 1024) return 1;
    // 解锁FLASH
    if (HAL_FLASH_Unlock() != HAL_OK)return 2;
    if (FLASH_WaitForLastOperation(STM32_FLASH_TIMEOUT))return 3;
    // 擦除FLASH
    const uint32_t word = *(__IO uint32_t*)addr;
    if (word != 0xFFFFFFFF)
    {
        erase_init.TypeErase = FLASH_TYPEERASE_SECTORS;
        erase_init.Banks = FLASH_BANK_1;
        erase_init.Sector = get_flash_selector(addr);
        erase_init.NbSectors = 1;
        erase_init.VoltageRange = FLASH_VOLTAGE_RANGE_3;
        if (HAL_FLASHEx_Erase(&erase_init, &sector_error) != HAL_OK)return 4;
    }
    if (FLASH_WaitForLastOperation(STM32_FLASH_TIMEOUT))return 3;
    // 写入FLASH
    for (uint32_t i = 0; i < size; i++)
    {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr + i, data_ptr[i]) != HAL_OK) return 5;
    }
    // 锁定FLASH
    if (HAL_FLASH_Lock() != HAL_OK) return 6;
    return 0;
}

#endif
