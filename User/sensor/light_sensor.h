//
// Created by ozcom on 2025/4/3.
//

#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "stdint.h"

#ifdef USE_USER_LIGHT_SENSOR

int32_t light_sensor_get_value(void);

#else

inline int32_t light_sensor_get_value(void)
{
    return 0;
}

#endif

#endif //LIGHT_SENSOR_H
