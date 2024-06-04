#include "I2C.h"
#include "MAG3110.h"
#include "uart.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int16_t x,y,z;

int mainMag(void){
	i2c_init(I2C0);
	MAG3110_Init();
	UART_Init();
	char msg[32];
	
	while(1){
		x = MAG3110_x();
		y = MAG3110_y();
		z = MAG3110_z();
		sprintf(msg,"%d %d %d\n\r",x,y,z);
		UART_SendString(msg);
		for(int i = 0;i<3000000;i++){}
	}
}

