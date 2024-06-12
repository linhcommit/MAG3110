#include "MKL46Z4.h"
#ifndef MAG3110_H
#define MAG3110_H

// Transmit and Receive
void MAG3110_Write(uint8_t addr, uint8_t data);
uint8_t MAG3110_Read(uint8_t addr);

// Initiate
void MAG3110_Init(void);

// Collect Data
int16_t MAG3110_Read_Reg16(uint8_t reg);
// x Axis
int16_t MAG3110_x(void);
// y Axis
int16_t MAG3110_y(void);
// z Axis
int16_t MAG3110_z(void);

// Read Angle
extern float x_calib;
extern float y_calib;
float calibx();
float caliby();
float MAG3110_ReadAngle(void);

#endif 
