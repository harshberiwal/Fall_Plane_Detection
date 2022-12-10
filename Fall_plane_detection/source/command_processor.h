/*
 * A command processor that interacts with the built-in Accelerometer peripheral throguh I2C
 * and detects Plane and Fall detection according to the user input through UART.
 * Implemented Bluetooth Communication to translate the accelerometer data to the
 * mouse poistion on the computer.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Final_Project
 *
 * No Leveraged code in this file.
 *
 */

#ifndef COMMAND_PROCESSOR_H_
#define COMMAND_PROCESSOR_H_

#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "uart.h"
#include "cbfifo.h"
#include "gpio.h"
#include "SysTick.h"
#include "accelerometer.h"

/* First checks if the Fall Detection is on, if it is, then checks if fall is detected
 * and later processes it.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None.
 */
void process_fall_detection();

/* Sends one byte of data one time after another of all the three axis.
 * First Sends the MS Byte and then the LS byte for each axis.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None.
 */
void send_data_to_bluetooth();

/* THIS FUNCTIONS PROVIDES THE ABSOLITE VALUE OF EACH Axis and ignores its direction.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None.
 */
void get_magnitude();

/* First checks if the Plane Detection is on, if it is, then turns on an LED indicator to
 * demonstrate the user of the plane flat surface without any skew.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None.
 */
void plane_check();


/* If fall Detection LED Is on, then turn it off after 2 sec using SysTick.
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None.
 */
void check_fall_LED();

/* Processes Accelerometer Data
 *
 * Parameters:
 *   None
 *
 * Returns:
 *   None.
 */
void process_accelerometer();

/*Displays the Opening Screen for User Interface*/
void display_UI();

/*Generates a crude Delay operation using loops*/
void Delay(int delay_us);

#endif /* COMMAND_PROCESSOR_H_ */
