#include "MKL46Z4.h"
#ifndef I2C_H
#define I2C_H

// I2C_Type in line 1470 or 1644 of MKL46Z4.h

// Set up I2C
void i2c_set_master(I2C_Type *p);
void i2c_set_slave(I2C_Type *p);

void i2c_set_tx(I2C_Type *p);
void i2c_set_rx(I2C_Type *p);

void i2c_init(I2C_Type *p);

// Transmit - Receive
uint8_t i2c_read(I2C_Type *p);
int i2c_write(I2C_Type *p, uint8_t data);

// Bit State 
void i2c_give_nack(I2C_Type *p); // Slave 
void i2c_repeated_start(I2C_Type *p);

// START ----- STOP
void START(I2C_Type *p);
void STOP(I2C_Type *p);
void WAIT_ACK(I2C_Type *p);

void DELAY(void);

#endif
