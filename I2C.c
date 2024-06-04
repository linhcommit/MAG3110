//////////////////////////////////////////////////////////////
////////////////////////DAO TUAN LINH/////////////////////////
//////////////////////////////////////////////////////////////

#include "MKL46Z4.h"                 // CMSIS Driver:I2C:Custom

void i2c_set_master(I2C_Type *p){
	// Page 716 Bit 5 (MST - Master Mode Select): When the 
	// MST bit is changed from a 0 to a 1, a START signal is 
	// generated on the bus and master mode is selected.
	// p->C1 |= (0<<5);
	// p->C1 |= (1<<5);
	// p->C1 |= I2C_C1_MST(0);
	p->C1 |= I2C_C1_MST_MASK;
}

void i2c_set_slave(I2C_Type *p){
	// Page 716 Bit 5: When the MST bit is changed from a 1 
	// to a 0, a STOP signal is generated and the mode of 
	// operation from master to slave.
	// p->C1 |= (1<<5);
	// p->C1 |= (0<<5);
	p->C1 &= ~I2C_C1_MST_MASK;
}

void i2c_set_tx(I2C_Type *p){
	// 716 TX: Transmit Mode Select
	// p->C1 |= (1<<4); // Set 1 is Transmit
	p->C1 |= I2C_C1_TX_MASK;
}

void i2c_set_rx(I2C_Type *p){
	// 717 RX: Receive Mode Select
	// p->C1 |= (0<<4); // Set 0 is Receive
	p->C1 &= ~I2C_C1_TX_MASK;
}

void i2c_init(I2C_Type *p){
	// Enable clocks
	
	// SCGC4 in 12.2.8 / page 214
	// SIM_SCGC4_I2C0_MASK			(0x40U)
	// I2C0 is bit 6 in SCGC4 Register
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	
	// in MAG3110								KL46Z
	// SCL correspond with			PTE25
	// SDA correspond with 			PTE24
	// SCGC5 in 12.2.9 / page 216
	// SIM->SCGC5 |= (1u<<13);
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// Configure I2C
	// Find page 173: PTE24 -----> I2C0_SCL(ALT5)
	// Configure SDA ---> PTE24
	// Page 194, ALT5 is 101 (bit 10 - bit 9 - bit 8)
	// PORTE->PCR[24] |= (0b101 << 8);
	PORTE->PCR[24] |= PORT_PCR_MUX(5);
	// Find page 173: PTE25 -----> I2C0_SDA(ALT5)
	PORTE->PCR[25] |= PORT_PCR_MUX(5);
	
	// 38.3.2/715 Set Baund Rate
	p->F = 0x14;
	// 38.3.3/716 I2C Control Register 1 (I2Cx_C1)
	// p->C1 = (1u<<7);
	p->C1 = I2C_C1_IICEN_MASK;
}

// Master read data from Slave
uint8_t i2c_read(I2C_Type *p){
	return p->D;
}

// Master send data to Slave
int i2c_write(I2C_Type *p, uint8_t data){
	// Send data, wait
	p->D = data;
	
	// wait ACK, IICIF(Interrupt Flag, page 719)
	// while(p->S != (0b10));
	while((p->S & I2C_S_IICIF_MASK) == 0);
	// certainly turn on flag interrupt
	p->S |= I2C_S_IICIF_MASK;
	
	// Page 719 RXAK = 0 when ACK signal was received
	// <=> bit 0 in S register equals 0
	// can it will not use 
	return ((p->S & I2C_S_RXAK_MASK) == 0);
}

// Give not ACK
void i2c_give_nack(I2C_Type * p){
	// bit 3 TXAK = 1 (page 717): No acknowledge signal 
	// is sent to the bus on the following receiving 
	// data byte (if FACK is cleared).
	// p->C1 |= (1u<<3);
	p->C1 |= I2C_C1_TXAK_MASK;
}

void i2c_repeated_start(I2C_Type *p){
	// bit 2 RSTA in page 717
	p->C1 |= (1u<<2);
}

void START(I2C_Type *p){
	i2c_set_master(p);
	i2c_set_tx(p);
}

void STOP(I2C_Type *p){
	i2c_set_slave(p);
	i2c_set_rx(p);
}

void WAIT_ACK(I2C_Type *p){
	while((p->S & I2C_S_IICIF_MASK) == 0);
	// certainly turn on flag interrupt
	p->S |= I2C_S_IICIF_MASK;
}

void delay(void){
	for(uint16_t i = 0; i < 100; i++){ }
}




