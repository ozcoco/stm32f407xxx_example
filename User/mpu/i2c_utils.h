//
// Created by ozcom on 2025/4/7.
//

#ifndef I2C_UTILS_H
#define I2C_UTILS_H

#include "main.h"

#ifdef USE_USER_MPU_6050

#define US_I2C_HANDLE hi2c1

uint8_t US_I2C_MEM_READ(uint8_t slave_addr, uint8_t reg_addr, uint8_t* data, uint16_t len);

uint8_t US_I2C_MEM_WRITE(uint8_t slave_addr, uint8_t reg_addr, uint8_t* data, uint16_t len);

#else

inline uint8_t US_I2C_MEM_READ(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len){return 0;}

inline uint8_t US_I2C_MEM_WRITE(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len){return 0;}

#endif

#endif //I2C_UTILS_H
