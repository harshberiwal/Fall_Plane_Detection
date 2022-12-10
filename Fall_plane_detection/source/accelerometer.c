/*
 * This file includes the definitions to initialize the accelerometer and process the
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

#include <MKL25Z4.H>
#include "accelerometer.h"
#include "i2c.h"
#include <math.h>
#include "gpio.h"

int16_t acc_X=0, acc_Y=0, acc_Z=0;
float roll=0.0, pitch=0.0;

int init_accelerometer()
{
	//set active mode, 14 bit samples and 800 Hz ODR
	i2c_write_byte(MMA_ADDR, REG_CTRL1, 0x01);
	return 1;
}

int test_accelerometer(){
		if(init_accelerometer()!=1){
			printf("Accelerometer didn't Initialize correctly \n");
			red_led_on();
			while(1);
			return 0;
		}
		printf("ACCELEROMETER TEST COMPLETE\n\r");
		return 1;
}

void read_full_xyz(int *acc)
{
	int i;
	uint8_t data[6];
	int16_t temp[3];

	i2c_start();
	i2c_read_setup(MMA_ADDR , REG_XHI);

	// Read five bytes in repeated mode
	for( i=0; i<5; i++)	{
		data[i] = i2c_repeated_read(0);
	}
	// Read last byte ending repeated mode
	data[i] = i2c_repeated_read(1);

	for ( i=0; i<3; i++ ) {
		temp[i] = (int16_t) ((data[2*i]<<8) | data[2*i+1]);
	}
	//*********************COPYING CALCULATED DATA TO THE BUFFER**************************
	acc_X = *acc++ = temp[0]/4;
	acc_Y = *acc++ = temp[1]/4;
	acc_Z = *acc++ = temp[2]/4;

}

void convert_xyz_to_roll_pitch() {
	float ax = acc_X/MAX_ACC_COUNT,
				ay = acc_Y/MAX_ACC_COUNT,
				az = acc_Z/MAX_ACC_COUNT;
	roll = atan2(ay, az)*180/PI;
	pitch = atan2(ax, sqrt(ay*ay + az*az))*180/PI;
}

float get_roll() {
	return fabs(roll);
}

float get_pitch() {
	return fabs(pitch);
}
