#include "I2C.h"
#include "MAG3110.h"
#include "math.h"
#include "uart.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

static int16_t x,y;
static int8_t heading = 0;
uint64_t i = 0;

float x_calib;
float y_calib;

float calibx() {
	float minx = 30000;
	float maxx = -30000;
	for (int i = 0; i < 500; i++) {
		int16_t data = MAG3110_x();
		if (data < minx) minx = (float)data;
		if (data > maxx) maxx = (float)data;
		DELAY();
	}
	return (minx + maxx) / 2.0;
}

float caliby() {
	float miny = 30000;
	float maxy = -30000;
	for (int i = 0; i < 500; i++) {
		int16_t data = MAG3110_y();
		if (data < miny) miny = (float)data;
		if (data > maxy) maxy = (float)data;
		DELAY();
	}
	return (miny + maxy) / 2.0;
}
/*
int main(void){
	i2c_init(I2C0);
	MAG3110_Init();
	
	//x_calib = calibx();
	//y_calib = caliby();
	
	
	while(1){
		x = MAG3110_x() - 213;
		DELAY();
		y = MAG3110_y() + 251;
		DELAY();
		// degree
		
		heading = atan2(y,x)*57.2957;
		
		char name[32];
		sprintf(name,"%d %d %d\n\r",x,y,heading);
		UART_SendString(name);
		
		for(i = 0; i < 300000; i++){}
	}
}
*/
uint16_t angle(){
		int16_t x = MAG3110_x() - 213;
		int16_t y = MAG3110_y() + 251;
		
		double heading = atan2((double)y,(double)x)*57.2957;
	
		if(heading < 0) heading += 360;
		return (uint16_t)heading;
}

