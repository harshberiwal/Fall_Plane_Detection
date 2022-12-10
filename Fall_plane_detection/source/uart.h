/*
 * uart.h includes the declaration to initialize the Serial Terminal. The uart1 is used
 * to communicate with the Bluetooth Module.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Final_Project
 *
 * THE UART0_init was heavily taken from Alexander Dean Code as given below in his Github.
 *
 * https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/UART.c
 *
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <MKL25Z4.H>
#include "cbfifo.h"


/*
 * Initializes the SERIAL UART with the given BAUD RATE.
 *
 * Parameter:
 *  Baud rate desired.
 *
 *  Returns:
 *   None.
 */
void Init_UART0(uint32_t baud_rate);

/*
 * Initializes the UART1 for Bluetooth with the given BAUD RATE.
 *
 * Parameter:
 *  Baud rate desired.
 *
 *  Returns:
 *   None.
 */
void Init_Bluetooth(uint32_t baud_rate);


/*
 * Check if the plane detection is on and returns the value. A getter function()
 *
 * Parameter:
 *  None
 *
 *  Returns:
 *   1 - Plane Detection is on 	0- Plane detection is off
 */
uint8_t check_plane_detection();


/*
 * Resets the Plane Detection variable so it doesn't obstruct the other applications
 *
 * Parameter:
 *  None
 *
 *  Returns:
 *   None.
 */
void reset_plane_detection();

/*
 * Check if the fall detection is on and returns the value. A getter function()
 *
 * Parameter:
 *  None
 *
 *  Returns:
 *   1 - Fall Detection is on 	0- Fall detection is off
 */
uint8_t check_fall_on();

/*
 * Transmit the Byte of data to the UART1 Data Register.
 *
 * Parameter:
 *  The 8 bit data to be transferred.
 *
 *  Returns:
 *   None.
 */
void transmit_data(int data);

#endif

