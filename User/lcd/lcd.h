//
// Created by ozcom on 2025/4/7.
//

#ifndef LCD_H
#define LCD_H

#ifdef USE_USER_LCD

/**
 * @brief 初始化LCD设备。
 *
 * 此函数用于对LCD设备进行初始化操作，包括设置LCD的工作模式、初始化引脚等，
 * 确保LCD设备可以正常工作，为后续的显示操作做准备。
 */
void lcd_init(void);

/**
 * @brief 在LCD上显示内容。
 *
 * 此函数用于在已初始化的LCD设备上显示指定的内容。
 * 它会根据LCD的驱动和设置，将相应的数据发送到LCD，以实现内容的显示。
 */
void lcd_display(void);

#else

inline void lcd_init(void){}

inline void lcd_display(void){}

#endif

#endif
