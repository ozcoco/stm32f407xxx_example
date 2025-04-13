//
// Created by ozcom on 2025/4/3.
//

#ifdef USE_USER_MPU_6050

#include "mpu_6050.h"

// #define MPU_6050_ADDR 0x68
#define MPU_6050_ADDR 0xD0

static mpu6050_handle_t gs_handle; /**< mpu6050 handle */

/**
 * @brief     basic example init
 * @param[in] addr_pin iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
static uint8_t mpu6050_basic_init(mpu6050_address_t addr_pin);


/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
static uint8_t mpu6050_basic_deinit(void);

/**
 * @brief      basic example read
 * @param[out] *g pointer to a converted data buffer
 * @param[out] *dps pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t mpu6050_basic_read(float g[3], float dps[3]);

/**
 * @brief      basic example read temperature
 * @param[out] *degrees pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 * @note       none
 */
static uint8_t mpu6050_basic_read_temperature(float* degrees);

float g[3];
float dps[3];
float degrees;

void mpu_6050_init(void)
{
    /* init */
    const uint8_t res = mpu6050_basic_init(MPU6050_ADDRESS_AD0_LOW);
    LOGI("mpu6050 init: %d.\n", res);
}

void mpu_6050_deinit(void)
{
    mpu6050_basic_deinit();
}

void mpu_6050_print(void)
{
    /* read */
    if (mpu6050_basic_read(g, dps) != 0)
    {
        LOGE("mpu_6050_print: mpu6050_basic_read failed.\n");
        mpu6050_basic_deinit();
    }

    if (mpu6050_basic_read_temperature(&degrees) != 0)
    {
        LOGE("mpu_6050_print: mpu6050_basic_read_temperature failed.\n");
        mpu6050_basic_deinit();
    }
    /* output */
    // LOGI("**************** MPU6050 info *********************");
    // LOGI("mpu6050: acc x is %0.2fg.\n", g[0]);
    // LOGI("mpu6050: acc y is %0.2fg.\n", g[1]);
    // LOGI("mpu6050: acc z is %0.2fg.\n", g[2]);
    // LOGI("mpu6050: gyro x is %0.2fdps.\n", dps[0]);
    // LOGI("mpu6050: gyro y is %0.2fdps.\n", dps[1]);
    // LOGI("mpu6050: gyro z is %0.2fdps.\n", dps[2]);
    // LOGI("mpu6050: temperature %0.2fC.\n", degrees);
    // LOGI("****************************************************");
    /* LCD output */
    static uint8_t lcd_clear_flag = 0;
    if (lcd_clear_flag == 0)
    {
        lcd_clear_flag = 1;
        LCD_Fill_Color(WHITE);
    }

    static char lcd_display_text[64] = {0};

    sprintf(lcd_display_text, "acc x:%0.2f", g[0]);
    LCD_WriteString(10, 20, lcd_display_text, BLUE, WHITE);

    memset(lcd_display_text, 0, sizeof(lcd_display_text));
    sprintf(lcd_display_text, "acc y:%0.2f", g[1]);
    LCD_WriteString(10, 20 + (18 * 1), lcd_display_text, BLUE, WHITE);

    memset(lcd_display_text, 0, sizeof(lcd_display_text));
    sprintf(lcd_display_text, "acc z:%0.2f", g[2]);
    LCD_WriteString(10, 20 + (18 * 2), lcd_display_text, BLUE, WHITE);

    memset(lcd_display_text, 0, sizeof(lcd_display_text));
    sprintf(lcd_display_text, "gyro x:%0.2f", dps[0]);
    LCD_WriteString(10, 20 + (18 * 3), lcd_display_text, BLUE, WHITE);

    memset(lcd_display_text, 0, sizeof(lcd_display_text));
    sprintf(lcd_display_text, "gyro y:%0.2f", dps[1]);
    LCD_WriteString(10, 20 + (18 * 4), lcd_display_text, BLUE, WHITE);

    memset(lcd_display_text, 0, sizeof(lcd_display_text));
    sprintf(lcd_display_text, "gyro z:%0.2f", dps[2]);
    LCD_WriteString(10, 20 + (18 * 5), lcd_display_text, BLUE, WHITE);

    memset(lcd_display_text, 0, sizeof(lcd_display_text));
    sprintf(lcd_display_text, "temperature %0.2fC", degrees);
    LCD_WriteString(10, 20 + (18 * 6), lcd_display_text, BLUE, WHITE);

    /* delay 1000 ms */
    US_DELAY_MS(3000);
}


/**
 * @brief     basic example init
 * @param[in] addr_pin iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t mpu6050_basic_init(mpu6050_address_t addr_pin)
{
    uint8_t res;

    /* link interface function */
    DRIVER_MPU6050_LINK_INIT(&gs_handle, mpu6050_handle_t);
    DRIVER_MPU6050_LINK_IIC_INIT(&gs_handle, mpu6050_interface_iic_init);
    DRIVER_MPU6050_LINK_IIC_DEINIT(&gs_handle, mpu6050_interface_iic_deinit);
    DRIVER_MPU6050_LINK_IIC_READ(&gs_handle, mpu6050_interface_iic_read);
    DRIVER_MPU6050_LINK_IIC_WRITE(&gs_handle, mpu6050_interface_iic_write);
    DRIVER_MPU6050_LINK_DELAY_MS(&gs_handle, mpu6050_interface_delay_ms);
    DRIVER_MPU6050_LINK_DEBUG_PRINT(&gs_handle, mpu6050_interface_debug_print);
    DRIVER_MPU6050_LINK_RECEIVE_CALLBACK(&gs_handle, mpu6050_interface_receive_callback);

    /* set the addr pin */
    res = mpu6050_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set addr pin failed.\n");

        return 1;
    }

    /* init */
    res = mpu6050_init(&gs_handle);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: init failed.\n");

        return 1;
    }

    /* delay 100 ms */
    mpu6050_interface_delay_ms(100);

    /* disable sleep */
    res = mpu6050_set_sleep(&gs_handle, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set sleep failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default clock source */
    res = mpu6050_set_clock_source(&gs_handle, MPU6050_BASIC_DEFAULT_CLOCK_SOURCE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set clock source failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default rate */
    res = mpu6050_set_sample_rate_divider(&gs_handle, (1000 / MPU6050_BASIC_DEFAULT_RATE) - 1);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set sample rate divider failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default low pass filter */
    res = mpu6050_set_low_pass_filter(&gs_handle, MPU6050_BASIC_DEFAULT_LOW_PASS_FILTER);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set low pass filter failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable temperature sensor */
    res = mpu6050_set_temperature_sensor(&gs_handle, MPU6050_BOOL_TRUE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set temperature sensor failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default cycle wake up */
    res = mpu6050_set_cycle_wake_up(&gs_handle, MPU6050_BASIC_DEFAULT_CYCLE_WAKE_UP);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set cycle wake up failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default wake up frequency */
    res = mpu6050_set_wake_up_frequency(&gs_handle, MPU6050_BASIC_DEFAULT_WAKE_UP_FREQUENCY);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set wake up frequency failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable acc x */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_ACC_X, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable acc y */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_ACC_Y, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable acc z */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_ACC_Z, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable gyro x */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_GYRO_X, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable gyro y */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_GYRO_Y, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* enable gyro z */
    res = mpu6050_set_standby_mode(&gs_handle, MPU6050_SOURCE_GYRO_Z, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set standby mode failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable gyroscope x test */
    res = mpu6050_set_gyroscope_test(&gs_handle, MPU6050_AXIS_X, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set gyroscope test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable gyroscope y test */
    res = mpu6050_set_gyroscope_test(&gs_handle, MPU6050_AXIS_Y, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set gyroscope test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable gyroscope z test */
    res = mpu6050_set_gyroscope_test(&gs_handle, MPU6050_AXIS_Z, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set gyroscope test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable accelerometer x test */
    res = mpu6050_set_accelerometer_test(&gs_handle, MPU6050_AXIS_X, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set accelerometer test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable accelerometer y test */
    res = mpu6050_set_accelerometer_test(&gs_handle, MPU6050_AXIS_Y, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set accelerometer test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable accelerometer z test */
    res = mpu6050_set_accelerometer_test(&gs_handle, MPU6050_AXIS_Z, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set accelerometer test failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable fifo */
    res = mpu6050_set_fifo(&gs_handle, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable temp fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_TEMP, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable xg fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_XG, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable yg fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_YG, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable zg fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_ZG, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* disable accel fifo */
    res = mpu6050_set_fifo_enable(&gs_handle, MPU6050_FIFO_ACCEL, MPU6050_BOOL_FALSE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fifo enable failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default interrupt level */
    res = mpu6050_set_interrupt_level(&gs_handle, MPU6050_BASIC_DEFAULT_INTERRUPT_PIN_LEVEL);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt level failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default pin type */
    res = mpu6050_set_interrupt_pin_type(&gs_handle, MPU6050_BASIC_DEFAULT_INTERRUPT_PIN_TYPE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt pin type failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default motion interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_MOTION, MPU6050_BASIC_DEFAULT_INTERRUPT_MOTION);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default fifo overflow interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_FIFO_OVERFLOW,
                                MPU6050_BASIC_DEFAULT_INTERRUPT_FIFO_OVERFLOW);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default dmp interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_DMP, MPU6050_BASIC_DEFAULT_INTERRUPT_DMP);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default i2c master interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_I2C_MAST, MPU6050_BASIC_DEFAULT_INTERRUPT_I2C_MAST);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default data ready interrupt */
    res = mpu6050_set_interrupt(&gs_handle, MPU6050_INTERRUPT_DATA_READY, MPU6050_BASIC_DEFAULT_INTERRUPT_DATA_READY);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default interrupt latch */
    res = mpu6050_set_interrupt_latch(&gs_handle, MPU6050_BASIC_DEFAULT_INTERRUPT_LATCH);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt latch failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default interrupt read clear */
    res = mpu6050_set_interrupt_read_clear(&gs_handle, MPU6050_BASIC_DEFAULT_INTERRUPT_READ_CLEAR);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set interrupt read clear failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the extern sync */
    res = mpu6050_set_extern_sync(&gs_handle, MPU6050_BASIC_DEFAULT_EXTERN_SYNC);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set extern sync failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default fsync interrupt */
    res = mpu6050_set_fsync_interrupt(&gs_handle, MPU6050_BASIC_DEFAULT_FSYNC_INTERRUPT);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fsync interrupt failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default fsync interrupt level */
    res = mpu6050_set_fsync_interrupt_level(&gs_handle, MPU6050_BASIC_DEFAULT_FSYNC_INTERRUPT_LEVEL);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set fsync interrupt level failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default iic master */
    res = mpu6050_set_iic_master(&gs_handle, MPU6050_BASIC_DEFAULT_IIC_MASTER);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set iic master failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default iic bypass */
    res = mpu6050_set_iic_bypass(&gs_handle, MPU6050_BASIC_DEFAULT_IIC_BYPASS);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set iic bypass failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default accelerometer range */
    res = mpu6050_set_accelerometer_range(&gs_handle, MPU6050_BASIC_DEFAULT_ACCELEROMETER_RANGE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set accelerometer range failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    /* set the default gyroscope range */
    res = mpu6050_set_gyroscope_range(&gs_handle, MPU6050_BASIC_DEFAULT_GYROSCOPE_RANGE);
    if (res != 0)
    {
        mpu6050_interface_debug_print("mpu6050: set gyroscope range failed.\n");
        (void)mpu6050_deinit(&gs_handle);

        return 1;
    }

    return 0;
}

/**
 * @brief      basic example read temperature
 * @param[out] *degrees pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read temperature failed
 * @note       none
 */
uint8_t mpu6050_basic_read_temperature(float* degrees)
{
    int16_t raw;

    /* read temperature */
    if (mpu6050_read_temperature(&gs_handle, &raw, degrees) != 0)
    {
        return 1;
    }

    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *g pointer to a converted data buffer
 * @param[out] *dps pointer to a converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t mpu6050_basic_read(float g[3], float dps[3])
{
    uint16_t len;
    int16_t accel_raw[3];
    int16_t gyro_raw[3];
    float accel[3];
    float gyro[3];

    /* set 1 */
    len = 1;

    /* read data */
    if (mpu6050_read(&gs_handle,
                     (int16_t (*)[3])&accel_raw, (float (*)[3])&accel,
                     (int16_t (*)[3])&gyro_raw, (float (*)[3])&gyro,
                     &len) != 0
    )
    {
        return 1;
    }

    /* copy the data */
    g[0] = accel[0];
    g[1] = accel[1];
    g[2] = accel[2];
    dps[0] = gyro[0];
    dps[1] = gyro[1];
    dps[2] = gyro[2];

    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t mpu6050_basic_deinit(void)
{
    /* deinit */
    if (mpu6050_deinit(&gs_handle) != 0)
    {
        return 1;
    }

    return 0;
}


#endif
