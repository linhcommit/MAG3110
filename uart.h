#include "MKL46Z4.h"

#define UART_BAUDRATE 9600

void UART_Init(void);
void UART_SendChar(char data);
void UART_SendString(const char *str);
void UART_SendInt16(int16_t data);
void UART_SendUint8(uint8_t data);
void UART_SendFloat(float data);
