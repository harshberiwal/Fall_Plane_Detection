/*
 * An application that communicates with the built-in Accelerometer peripheral throguh I2C
 * and detects Plane and Fall detection according to the user input through UART.
 * Implemented Bluetooth Communication to translate the accelerometer data to the
 * mouse poistion on the computer.
 *
 * This file includes the main.c.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Final_Project
 *
 * No Leveraged code in this file.
 *
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "I2C.h"
#include "accelerometer.h"
#include "uart.h"
#include "cbfifo.h"
#include "gpio.h"
#include "SysTick.h"
#include "test_cbfifo.h"
#include "command_processor.h"

#define UART0_BAUD_RATE 		38400
#define BLUETOOTH_BAUD_RATE 	9600

int main(void) {
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    //*****************INITIALIZE SYSTICK FOR LED TIMING AND MODULE TESTING**************
    initialize_SysTick();
    //***********************GPIO INIT FOR RED GREEN AND BLUE LED************************
    gpio_init();
    //*****************I2C INIT FOR COMMUNICATING WITH ACCELROMETER**********************
    i2c_init();
    //*****************UART0 INIT FOR COMMUNICATING WITH THE COM PORT********************
    Init_UART0(UART0_BAUD_RATE);

    //*****************UART1 INIT FOR COMMUNICATING WITH THE BLUETOOTH*******************
    Init_Bluetooth(BLUETOOTH_BAUD_RATE);

    //********************TESTING UART, CBFIFO, I2C and ACCELEROMETER********************
#ifdef DEBUG
	int success = test_cbfifo();
	if(!success)
		printf("\n\rCircular buffer Tests Failed\n\r");
	else
		success &= test_accelerometer();
	if(success)
		printf("\n\rAll Module Tests Passed\n\r");
#endif
	//********************DISPLAYING UI FOR ACCELEROMETER TEST AND APP*******************
    display_UI();
    while(1){
    	//***********************READS CURRENT X, Y, Z CO-ORDINATES**********************
    	process_accelerometer();
    	//***************************READING THE ABSOLUTE VALUE**************************
    	get_magnitude();
    	//******************SENDS THE ABSOLUTE DATA OVER BLUETOOTH***********************
    	send_data_to_bluetooth();

    	//************GETS THE ROLL AND PITCH OF THE ACCELEROMTER THROUGH XYZ************
    	convert_xyz_to_roll_pitch();

    	//*************CHECKS IF THE USER WANTS PLANE DETECTION AND PROCESSES************
    	plane_check();

    	//********************TURNS THE LED OFF AFTER 2 SECONDS IF ON********************
    	check_fall_LED();

    	//**************PROCESSES FALL DETECTION OF THE MICROCONTROLLER******************
    	process_fall_detection();
    }
}
