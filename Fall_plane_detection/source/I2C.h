/*
 * I2C.h includes the declaration to initialize the I2c communication between the accelerometer
 * and the SoC
 *
 * Author: Alexandar Dean
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Final_Project
 *
 * The I2c Driver code was taken from Alexander Dean Github.
 *
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c
 *
 */

#include <stdint.h>

#define I2C_M_START 	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP  	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RSTART 	I2C0->C1 |= I2C_C1_RSTA_MASK

#define I2C_TRAN			I2C0->C1 |= I2C_C1_TX_MASK
#define I2C_REC				I2C0->C1 &= ~I2C_C1_TX_MASK

#define BUSY_ACK 	    while(I2C0->S & 0x01)
#define TRANS_COMP		while(!(I2C0->S & 0x80))
#define I2C_WAIT 			i2c_wait();

#define NACK 	        I2C0->C1 |= I2C_C1_TXAK_MASK
#define ACK           I2C0->C1 &= ~I2C_C1_TXAK_MASK

/*
 * Initializes pins as i2c0 bus
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void i2c_init(void);

/*
 * send start sequence
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void i2c_start(void);

/*
 * send device and register addresses
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void i2c_read_setup(uint8_t dev, uint8_t address);


/*
 * read a byte and ack/nack as appropriate
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
uint8_t i2c_repeated_read(uint8_t);


/*
 * funcs for reading and writing a single byte
 * using 7bit addressing reads a byte from dev:address
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
uint8_t i2c_read_byte(uint8_t dev, uint8_t address);


/*	using 7bit addressing writes a byte data to dev:address
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void i2c_write_byte(uint8_t dev, uint8_t address, uint8_t data);
