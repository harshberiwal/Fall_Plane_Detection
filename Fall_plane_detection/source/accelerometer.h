/*
 * This file includes the declaration to initialize the accelerometer and process the
 * data received from the accelerometer.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Final_Project
 *
 * The basic call to the i2c driver were taken from the Alexander dean Github given below.
 * The given function were further modified to serve the application and many additionals
 * functions were created to communication with the application entry point.
 *
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/I2C.c
 *
 */


#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <stdint.h>

#define MMA_ADDR 0x3A

#define REG_XHI 0x01
#define REG_XLO 0x02
#define REG_YHI 0x03
#define REG_YLO 0x04
#define REG_ZHI	0x05
#define REG_ZLO 0x06

#define REG_WHOAMI 0x0D
#define REG_CTRL1  0x2A
#define REG_CTRL4  0x2D

#define WHOAMI 0x1A

#define MAX_ACC_COUNT (4096.0)
#define PI (3.14159265)


/* Initialize the accelerometer by sending its slave address to the acceleromter
 * through the I2C bus.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   1 - if Initialization successful, 0 - initialization failed
 */
int init_accelerometer(void);


/* Reads the xyz coordinate data from the accelerometer and returns
 * through the I2C bus.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void read_full_xyz(int *acc_val);

/* Uses the Xyz co-ordinates of the accelerometer and converts that to roll and
 * pitch using tan inverse.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None
 */
void convert_xyz_to_roll_pitch(void);

/* Returns The current pitch of the accelerometer
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   The pitch
 */
float get_pitch();

/* Returns The current roll of the accelerometer
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   The roll
 */
float get_roll();


/* Checks if the Accelerometer initialization is successful otherwise turns on Red led
 * and terminates the program.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *  1 - if success 0 - failed
 */
int test_accelerometer();


#endif /* ACCELEROMETER_H_ */
