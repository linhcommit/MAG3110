#include "MKL46Z4.h"
#include "uart.h"
#include<stdio.h>

void UART_Init() {
	//PORTA clock enable
	SIM->SCGC5 |= 1 << 9;
	
	//UART Clock enable
	SIM->SCGC4 |= 1 << 10;
	
	//MCGFLLCLK/2 clock source
	SIM->SOPT2 |= 1 << 26;
	
	//PTA1 as RX, PTA2 as TX (Alternative Function 2)
	PORTA->PCR[1] |= 1 << 9;
	PORTA->PCR[2] |= 1 << 9;
	
	//Disable UART0 to configuring
	UART0->C2 &= ~(1 << 3 | 1 << 2);
	
	//8 or 9 bit data
	UART0->C4 &= ~((uint8_t) 1 << 5);
	
	//8 bit data
	UART0->C1 &= ~((uint8_t) 1 << 4);
	
	//No Parity
	UART0->C1 &= ~((uint8_t) 1 << 1);
	
	//LSB (bit 0) as first bit tramsmitted after start bit
	UART0->S2 &= ~((uint8_t) 1 << 5);
	
	//RX data not inverted
	UART0->S2 &= ~((uint8_t) 1 << 4);
	
	//TX data not inverted
	UART0->C3 &= ~((uint8_t) 1 << 4);
	
	//1 stop bit
	UART0->BDH &= ~((uint8_t) 1 << 5);
	
	//Baud rate
	uint16_t sbr = SystemCoreClock / (16 * UART_BAUDRATE);
	
	UART0->BDH = (uint8_t)(sbr & 0x1F00);
	UART0->BDL = ((uint8_t)(sbr & 0xFF));
	
	//TX and RX enable
	UART0->C2 |= (1 << 3 | 1 << 2);
}

void UART_SendChar(char data) {
	while(!(UART0->S1 & (1 << 7)));
	UART0->D = data;
}

void UART_SendString(const char *str) {
	while (*str) {
        UART_SendChar((uint8_t)*str++);
    }
}

void UART_SendInt16(int16_t data) {
    char buffer[6];
    sprintf(buffer, "%d", data);
    UART_SendString(buffer);
}

void UART_SendUint8(uint8_t data) {
    char buffer[4];
    sprintf(buffer, "%u", data);
    UART_SendString(buffer);
}

void UART_SendFloat(float value) {
    char buffer[20];
    sprintf(buffer, "%.3f", value);
    UART_SendString(buffer);
}
