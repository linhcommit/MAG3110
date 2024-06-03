#include "MAG3110.h"
#include "i2c.h"
#define MAG3110_ADDR					0x0E
#define I2C_WRITE							0
#define I2C_READ							1

void MAG3110_Write(uint8_t addr, uint8_t data){
	delay();
	START(I2C0);
	// i2c_write(I2C0, MAG3110_I2C_ADDR<<1);
	i2c_write(I2C0, MAG3110_ADDR | I2C_WRITE);
	i2c_write(I2C0, addr);
	i2c_write(I2C0, data);
	STOP(I2C0);
}

// is fixing
uint8_t MAG3110_Read(uint8_t addr){
	delay();
	START(I2C0);
	
	i2c_write(I2C0, MAG3110_ADDR | I2C_WRITE);
	i2c_write(I2C0, addr);
	
	i2c_repeated_start(I2C0);
	i2c_write(I2C0, MAG3110_ADDR | I2C_READ);
	
	i2c_set_rx(I2C0);
	i2c_give_nack(I2C0);
	
	i2c_read(I2C0);
	
	
	STOP(I2C0);
	return i2c_read(I2C0);
}

void MAG3110_Init(void) {
    uint16_t id;
    id = MAG3110_Read(0x07);
    
    if(id != (0x0E << 1)) {  // Corrected the comparison
        return;
    } else {
        // CTRL_REG1;
				// Only need turn bit ActiveMode in CTRL_REG1
        MAG3110_Write(0x10, 0x79);
        delay();  // Ensure delay() is properly defined
        // CTRL_REG2;
        MAG3110_Write(0x11, 0x80);
    }
}

// Collect data from sensor
int16_t MAG3110_Read_Reg16(uint8_t reg){
	// 2 register adjacent, so I will add 1 to reg
	int16_t result = MAG3110_Read(reg);
	result = (result<<8) | MAG3110_Read(reg + 1);
	return result;
}

// x Axis
int16_t MAG3110_x(void){
	return MAG3110_Read_Reg16(0x01);
}

// y Axis
int16_t MAG3110_y(void){
	return MAG3110_Read_Reg16(0x03);
}

// z Axis
int16_t MAG3110_z(void){
	return MAG3110_Read_Reg16(0x05);
}










