//
// Created by ozcom on 2025/4/3.
//

#ifndef MPU_6050_H
#define MPU_6050_H
#include <stdint.h>

#ifdef USE_USER_MPU_6050

uint8_t mpu_6050_init(void);

#else

inline uint8_t mpu_6050_init(void){ return 0; }

#endif

#endif //MPU_6050_H
