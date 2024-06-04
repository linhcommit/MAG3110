#include "I2C.h"
#include "MAG3110.h"

static int16_t x,y,z;

int main(void){
	i2c_init(I2C0);
	MAG3110_Init();
	
	while(1){
		x = MAG3110_x();
		y = MAG3110_y();
		z = MAG3110_z();
		//x = MAG3110_Read(0x07);
	}
}

