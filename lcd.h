////////////////////////////////////////////////
///// Tác giả / Author: Trần Hồng Quân ////////
//////////////////////////////////////////////

#ifndef LCD_H
#define LCD_H
#include <stdint.h>
#include <stdbool.h>

void delay(uint32_t time);
void LCD_Init(void);
void LCD_DisplayAll(void);
void LCD_DisplayDemical(uint16_t val);
void LCD_DisplayError(void);
void LCD_DisplayTime(uint8_t num1,uint8_t num2);
void LCD_StopBlinkMode(void);
void LCD_StartBlinkMode(void);
void LCD_StopDisplay(void);
void LCD_StartDisplay(void);
void LCD_SetNum(uint8_t dig, uint8_t num, bool isShowZero,bool isShowDot);

#endif
