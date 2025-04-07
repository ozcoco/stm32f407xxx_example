//
// Created by ozcom on 2025/4/3.
//

#ifdef USE_USER_MPU_6050

#include "mpu_6050.h"
#include <stdint.h>
#include "i2c_utils.h"
#include "delay/delay.h"
#include "log/log.h"

// #define MPU_6050_ADDR 0x68
#define MPU_6050_ADDR 0xD0
//-----------------------------------------
// 定义MPU6050内部地址
//-----------------------------------------
#define SMPLRT_DIV 0x19 //陀螺仪采样率，典型值：0x07(125Hz)
#define CONFIG 0x1A //低通滤波频率，典型值：0x06(5Hz)
#define GYRO_CONFIG 0x1B //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define ACCEL_CONFIG 0x1C //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)

/* 加速度相关寄存器地址 */
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

/* 温度相关寄存器地址 */
#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42

/* 陀螺仪相关寄存器地址 */
#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define PWR_MGMT_1 0x6B  //电源管理，典型值：0x00(正常启用)
#define WHO_AM_I 0x75 //IIC地址寄存器(默认数值0x68，只读)

static void mpu6050_write_reg(const uint8_t reg_addr, uint8_t* const data, const uint16_t len)
{
    US_I2C_MEM_WRITE(MPU_6050_ADDR, reg_addr, data, len);
}

static void mpu6050_write_data(const uint8_t reg_addr, uint8_t data)
{
    US_I2C_MEM_WRITE(MPU_6050_ADDR, reg_addr, &data, 1);
}


static void mpu6050_read_reg(const uint8_t reg_addr, uint8_t* const data, const uint16_t len)
{
    US_I2C_MEM_READ(MPU_6050_ADDR, reg_addr, data, len);
}


static int16_t mpu6050_read_data(const uint8_t reg_addr)
{
    int16_t data = 0U;
    mpu6050_read_reg(reg_addr, (uint8_t*)&data, sizeof(data));
    return data;
}


void mpu_6050_init(void)
{
    // delay_ms(100);
    // 解除休眠状态
    mpu6050_write_data(PWR_MGMT_1, 0x00);
    // 陀螺仪采样率，典型值：0x07(125Hz)
    mpu6050_write_data(SMPLRT_DIV, 0x07);
    mpu6050_write_data(CONFIG, 0x06); //低通滤波频率，典型值：0x06(5Hz)
    mpu6050_write_data(GYRO_CONFIG, 0x18); //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
    mpu6050_write_data(ACCEL_CONFIG, 0x01); //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
}

void mpu_6050_print(void)
{
    /* 打印 x, y, z 轴加速度 */
    LOGI("ACCEL_X: %d\t", mpu6050_read_data(ACCEL_XOUT_H));
    LOGI("ACCEL_Y: %d\t", mpu6050_read_data(ACCEL_YOUT_H));
    LOGI("ACCEL_Z: %d\t", mpu6050_read_data(ACCEL_ZOUT_H));

    /* 打印温度，需要根据手册的公式换算为摄氏度 */
    LOGI("TEMP: %0.2f\t", mpu6050_read_data(TEMP_OUT_H) / 340.0 + 36.53);

    /* 打印 x, y, z 轴角速度 */
    LOGI("GYRO_X: %d\t", mpu6050_read_data(GYRO_XOUT_H));
    LOGI("GYRO_Y: %d\t", mpu6050_read_data(GYRO_YOUT_H));
    LOGI("GYRO_Z: %d\t", mpu6050_read_data(GYRO_ZOUT_H));

    LOGI("\r\n");
}

#endif
