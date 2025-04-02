//
// Created by ozcom on 2025/4/3.
//

#ifdef USE_USER_LIGHT_SENSOR

#include "light_sensor.h"
#include "stm32f4xx_hal.h"
#include "adc.h"

int32_t light_sensor_get_value(void)
{
    HAL_ADC_Start(&hadc3);
    HAL_ADC_PollForConversion(&hadc3, HAL_MAX_DELAY);
    const uint32_t value = HAL_ADC_GetValue(&hadc3);
    return 100 - value / 30;
}

#else

#include "light_sensor.h"

int32_t light_sensor_get_value(void)
{
    return 0;
}

#endif