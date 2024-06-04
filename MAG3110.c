#include "MAG3110.h"
#include "i2c.h"
#define MAG3110_ADDR					(0x0E << 1)
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
	// Ngan cach truyen nhan I2C giua cac lan
	delay();
	// bit ST
	START(I2C0);
	// 6 bit Device Address and 1 bit Write + ACK
	i2c_write(I2C0, MAG3110_ADDR | I2C_WRITE);
	
	// 7 bit Register Address + ACK
	i2c_write(I2C0, addr);
	
	// 1 bit SR
	i2c_repeated_start(I2C0);
	
	//6 bit Device Address + 1 bit Read + ACK
	i2c_write(I2C0, MAG3110_ADDR | I2C_READ);
	
	// Chuyen sang qua trinh nhan du lieu
	i2c_set_rx(I2C0);
	
	//Send bit NACK for Slave
	i2c_give_nack(I2C0);
	
	i2c_read(I2C0);
	
	// delay to wait I2C0
	WAIT_ACK(I2C0);
	
	uint8_t data = i2c_read(I2C0);
	WAIT_ACK(I2C0);
	
	STOP(I2C0);
	
	return data;
}

void MAG3110_Init(void) {
    uint8_t id;
    id = MAG3110_Read(0x07);
    
    if(id != (0x0E << 1)) {  // Corrected the comparison
        return;
    } else {
        // CTRL_REG1 has address is 0x10;
				// Only need turn bit ActiveMode in CTRL_REG1
        MAG3110_Write(0x10, 0x79);
        delay();  // Ensure delay() is properly defined
				delay();
        // CTRL_REG2 has address is 0x11;
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
// page 17 / part 5.1.2 of Datasheet MAG3110
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










