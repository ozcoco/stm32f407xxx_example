//
// Created by ozcom on 2025/4/3.
//

#ifndef MPU_6050_H
#define MPU_6050_H

#ifdef USE_USER_MPU_6050

void mpu_6050_init(void);

void mpu_6050_print(void);

#else

inline void mpu_6050_init(void){}

inline void mpu_6050_print(void){}

#endif

#endif //MPU_6050_H
