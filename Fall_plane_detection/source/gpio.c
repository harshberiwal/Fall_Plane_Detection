/*
 * gpio.c includes all the definitions of functions in gpio.h
 * This include gpio_Init(), and led on and off functions for each led.
 *
 * Author: Harsh Beriwal
 * IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13]
 *
 * Github Link: https://github.com/harshberiwal/PES_Assignment_3
 *
 * No leveraged code or files
 *
 */

#include "gpio.h"


void gpio_init()
{
	//****************Turning on Clock for GPIOs**************************
	SIM -> SCGC5 |= PORT_A;
	SIM -> SCGC5 |= PORT_B;

	//****************Configuring Pins as GPIO****************************
	PORTB -> PCR[RED] = (uint32_t)(0x00000100);
	PORTB -> PCR[GREEN] = (uint32_t)(0x00000100);
	PORTD -> PCR[BLUE]= (uint32_t)(0x00000100);

	//****************Configuring Pins as output**************************
	GPIOB -> PDDR |= red_LED;
	GPIOB -> PDDR |= green_LED;
	GPIOD -> PDDR |= blue_LED;

	//****************Initializing Pins to Low****************************
	GPIOB -> PDOR |= red_LED;
	GPIOB -> PDOR |= green_LED;
	GPIOD -> PDOR |= blue_LED;
}

void all_led_off(){
	GPIOB -> PDOR |= green_LED;
	GPIOD -> PDOR |= blue_LED;
	GPIOB -> PDOR |= red_LED;
}

void red_led_on(){
	GPIOB -> PDOR |= green_LED;
	GPIOD -> PDOR |= blue_LED;
	GPIOB -> PDOR &= red_LED;
}

void green_led_on() {
	GPIOB -> PDOR &= ~green_LED;
	GPIOD -> PDOR |= blue_LED;
	GPIOB -> PDOR |= red_LED;
}

void blue_led_on() {
	GPIOB -> PDOR |= green_LED;
	GPIOD -> PDOR &= ~blue_LED;
	GPIOB -> PDOR |= red_LED;
}
