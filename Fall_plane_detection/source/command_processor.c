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


#include "command_processor.h"

//****************************MACROS THAT ARE EDITABLE********************************

#define FALL_ZAXIS_THRESHOLD	1400
#define FALL_XAXIS_THRESHOLD	200
#define TWO_SECOND				32
#define THREE_AXIS				3
#define MSB_SHIFT(x)			(((x)>>8) & 0xFF)
#define LSB_SHIFT(x)			((x) & 0xFF)
#define FLAT_ROLL_THRSD			3
#define FLAT_PITCH_THRSD		2


//**********************ENUM FOR THE ALL THE THREE AXIS********************************
typedef enum{
	axis_X,
	axis_Y,
	axis_Z,
}axis_t;

int previous_Z =0, fall_detected =0,change =0;
float current_roll =0.0, current_pitch = 0.0;
int Acc_RAW_data[3];
int *Acc_data = &Acc_RAW_data[0];

void process_fall_detection() {
	if(check_fall_on()){
		if((previous_Z - Acc_RAW_data[axis_Z]>FALL_ZAXIS_THRESHOLD) &&
				(Acc_RAW_data[axis_X]<FALL_XAXIS_THRESHOLD)){
			printf("\n\rFall Detected. Dropped from %d\n\r", previous_Z/4);
			//*********************Updates the Previous Value****************************
			previous_Z = Acc_RAW_data[axis_Z] ;
			//********************FALL DETECTED- TURNS ON GREEN LED**********************
			green_led_on();
			reset_timer();
			fall_detected =1;
		} else {
			//*************************CHECKING FOR FALL*********************************
			previous_Z = Acc_RAW_data[axis_Z] ;
		}
	}
	Delay(50000);
}

void process_accelerometer(){
	read_full_xyz(Acc_data);
}

void check_fall_LED(){
	if(fall_detected ==1 && (get_timer()>TWO_SECOND)){
		all_led_off();
		fall_detected =0;
	}
}

void send_data_to_bluetooth() {
	for(int i =0; i<THREE_AXIS; i++){
		transmit_data(MSB_SHIFT(Acc_RAW_data[i]));
		transmit_data(LSB_SHIFT(Acc_RAW_data[i]));
	}
}

void get_magnitude(){
	for(int i=0; i<THREE_AXIS; i++){
		Acc_RAW_data[i] = abs(Acc_RAW_data[i]);
	}
}

void plane_check(){
	if(check_plane_detection()){
		//*****************GETS THE ROLL AND PITCH FROM ACCELROMETER***********************
		current_roll = get_roll();
		current_pitch = get_pitch();
		//*****************************FLAT SURFACE DETECTED*******************************
		if((get_roll()<FLAT_ROLL_THRSD) && (get_pitch()<FLAT_PITCH_THRSD)) {
			if(change ==1){
				printf("\n\rFlat surface Detected\n\r");
				change =0;
			}
			blue_led_on();
		} else {
			change =1;
			all_led_off();
		}
	}
}

void display_UI(){
	printf("\n\rCommands: ");
	printf("\n\rPress 1 to turn on Plane Detection");
	printf("\n\rPress 2 to turn on Fall Detection");
	printf("\n\n\rEnter the Commands: ");
}

void Delay(int delay_us){
	for(int i =0; i<delay_us; i++);
}

