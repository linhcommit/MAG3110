#ifndef LCD_H
#define LCD_H
#include <stdint.h>

void delay(uint32_t time);
void LCD_Init(void);
void LCD_Display_All(void);
void LCD_DisplayDemical(uint16_t val);

#endif
