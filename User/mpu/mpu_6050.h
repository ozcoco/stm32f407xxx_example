//
// Created by ozcom on 2025/4/3.
//

#ifndef MPU_6050_H
#define MPU_6050_H

#ifdef USE_USER_MPU_6050

#include "stdint.h"
#include "driver_mpu6050_interface.h"
#include "log/log.h"
#include "delay/delay.h"
#include "lcd/lcd.h"
#include "lcd/lcd_config.h"

/**
 * @brief mpu6050 basic example default definition
 */
#define MPU6050_BASIC_DEFAULT_CLOCK_SOURCE                   MPU6050_CLOCK_SOURCE_PLL_X_GYRO           /**< gyro pll x */
#define MPU6050_BASIC_DEFAULT_RATE                           50                                        /**< 50Hz */
#define MPU6050_BASIC_DEFAULT_LOW_PASS_FILTER                MPU6050_LOW_PASS_FILTER_3                 /**< low pass filter 3 */
#define MPU6050_BASIC_DEFAULT_CYCLE_WAKE_UP                  MPU6050_BOOL_FALSE                        /**< disable cycle wake up */
#define MPU6050_BASIC_DEFAULT_WAKE_UP_FREQUENCY              MPU6050_WAKE_UP_FREQUENCY_1P25_HZ         /**< 1.25Hz */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_PIN_LEVEL            MPU6050_PIN_LEVEL_LOW                     /**< low level */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_PIN_TYPE             MPU6050_PIN_TYPE_PUSH_PULL                /**< push pull */
#define MPU6050_BASIC_DEFAULT_ACCELEROMETER_RANGE            MPU6050_ACCELEROMETER_RANGE_2G            /**< 2g */
#define MPU6050_BASIC_DEFAULT_GYROSCOPE_RANGE                MPU6050_GYROSCOPE_RANGE_2000DPS           /**< 2000dps */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_MOTION               MPU6050_BOOL_FALSE                        /**< disable motion */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_FIFO_OVERFLOW        MPU6050_BOOL_FALSE                        /**< disable fifo overflow */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_DMP                  MPU6050_BOOL_FALSE                        /**< disable dmp */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_I2C_MAST             MPU6050_BOOL_FALSE                        /**< disable i2c master */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_DATA_READY           MPU6050_BOOL_FALSE                        /**< disable data ready */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_LATCH                MPU6050_BOOL_TRUE                         /**< enable latch */
#define MPU6050_BASIC_DEFAULT_INTERRUPT_READ_CLEAR           MPU6050_BOOL_TRUE                         /**< enable interrupt read clear */
#define MPU6050_BASIC_DEFAULT_EXTERN_SYNC                    MPU6050_EXTERN_SYNC_INPUT_DISABLED        /**< extern sync input disable */
#define MPU6050_BASIC_DEFAULT_FSYNC_INTERRUPT                MPU6050_BOOL_FALSE                        /**< disable fsync interrupt */
#define MPU6050_BASIC_DEFAULT_FSYNC_INTERRUPT_LEVEL          MPU6050_PIN_LEVEL_LOW                     /**< low level */
#define MPU6050_BASIC_DEFAULT_IIC_MASTER                     MPU6050_BOOL_FALSE                        /**< disable iic master */
#define MPU6050_BASIC_DEFAULT_IIC_BYPASS                     MPU6050_BOOL_FALSE                        /**< disable iic bypass */

void mpu_6050_init(void);

void mpu_6050_deinit(void);

void mpu_6050_print(void);

#else

inline void mpu_6050_init(void){}
inline void mpu_6050_deinit(void){}
inline void mpu_6050_print(void){}

#endif

#endif //MPU_6050_H
