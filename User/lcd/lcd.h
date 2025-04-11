//
// Created by ozcom on 2025/4/7.
//

#ifndef LCD_H
#define LCD_H

#ifdef USE_USER_LCD

void lcd_init(void);

void lcd_display(void);

#else

inline void lcd_init(void){}

inline void lcd_display(void){}

#endif

#endif
