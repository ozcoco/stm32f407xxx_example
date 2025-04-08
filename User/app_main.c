//
// Created by ozcom on 2025/3/31.
//

#include "app_main.h"
#include "log/log.h"
#include "led/led_test.h"
#include "delay/delay.h"
#include "stdlib.h"
#include "sensor/light_sensor.h"
#include "mpu/mpu_6050.h"
#include "at24c02/at24c02.h"


/** 串口编号 **/
#define UART_NUM_LOG 1

/** I2C编号 **/
#define I2C_NUM_MEM 1
#define I2C_NUM_SENSOR 2

/** 声明 **/
static void on_init(void);
static void on_begin(void);
static void on_start(void);
static uint8_t on_loop(void);
static void on_end(void);
static void on_uart_rx(const uint8_t uart_num, const uint8_t* data, uint16_t size);

/** 实例化 **/
app_main_t app_main = {
    .on_init = on_init,
    .on_begin = on_begin,
    .on_start = on_start,
    .on_loop = on_loop,
    .on_end = on_end,
    .on_uart_rx = on_uart_rx,
};

/** 定义 **/
static void on_init(void)
{
}

static void on_begin(void)
{
    // log初始化
    LOG_RX_ENABLE();
    LOGI("STM32F407VET6 example\n");
    LOGI("on_begin\n");
}

static void on_start(void)
{
    LOGI("on_start\n");
    led_init();
#ifdef USE_USER_MPU_6050
    mpu_6050_init();
#endif

#ifdef USE_USER_AT24C02
    at24c02_init(); // 初始化AT24C02
#endif
}


static uint8_t on_loop(void)
{
#ifdef USE_USER_LIGHT_SENSOR
    // 读取光照强度
    const int32_t light = light_sensor_get_value();
    LOGI("light=%d\r\n", light);
    // 控制LED
    if (light < 0)
    {
        on_led_cmd(CMD_LED_0_ON);
    }
    else
    {
        on_led_cmd(CMD_LED_0_OFF);
    }
    // 延时1s
    // delay_ms(3000);
#endif

#ifdef USE_USER_MPU_6050
    mpu_6050_print();
#endif

#ifdef USE_USER_AT24C02
    at24c02_print();
#endif

    return 0;
}

static void on_end(void)
{
    LOGI("on_end\n");
}


/*************************************************************
 * 以下为UART中断回调函数
 **************************************************************/

/**
 * @brief 串口接收回调函数
 *
 * @param uart_num 串口编号
 * @param data 数据
 * @param size 数据大小
 */
static void on_uart_rx(const uint8_t uart_num, const uint8_t* data, uint16_t size)
{
    if (uart_num == UART_NUM_LOG)
    {
        const int32_t cmd = strtol((const char*)data, NULL, 16);
        on_led_cmd(cmd);
    }
}


/*************************************************************
 * 以下为I2C中断回调函数
 **************************************************************/

/**
 * @brief I2C接收回调函数
 *
 * @param uart_num I2C编号
 */
void i2c_rx_callback(const uint8_t uart_num)
{
    if (uart_num == I2C_NUM_MEM)
    {
        on_at24c02_event(US_AT24C02_EVENT_RX_COMPLETE);
    }
}

/**
 * @brief I2C发送回调函数
 *
 * @param uart_num I2C编号
 */
void i2c_tx_callback(const uint8_t uart_num)
{
    if (uart_num == I2C_NUM_MEM)
    {
        on_at24c02_event(US_AT24C02_EVENT_TX_COMPLETE);
    }
}

/**
 * @brief I2C错误回调函数
 *
 * @param uart_num I2C编号
 */
void i2c_err_callback(const uint8_t uart_num)
{
    if (uart_num == I2C_NUM_MEM)
    {
        on_at24c02_event(US_AT24C02_EVENT_ERROR);
    }
}

/**
 * @brief I2C中止回调函数
 *
 * @param uart_num I2C编号
 */
void i2c_abort_callback(const uint8_t uart_num)
{
}
