//
// Created by ozcom on 2025/4/8.
//

#ifndef AT24C02_H
#define AT24C02_H

#include "main.h"

#ifdef USE_USER_AT24C02

void at24c02_init(void);

#else

inline void at24c02_init(void){}

#endif

#endif //AT24C02_H
