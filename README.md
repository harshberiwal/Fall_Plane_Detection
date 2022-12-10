# PES_Final_Project

An application that communicates with the built-in Accelerometer peripheral throguh I2C and detects Plane and Fall detection according to the user input through UART. Tried implementing Bluetooth Communication to translate the accelerometer data to the mouse poistion on the computer. 

Author: Harsh Beriwal, harsh.beriwal@colorado.edu

IDE Used: MCUXpresso IDE v11.6.0 [Build 8187] [2022-07-13] Github Link: https://github.com/harshberiwal/PES_Assignment_7

Three Important Applications of Accelerometer were demonstrated. 

1)Plane Detection - Whenever the Frdm kl25z Dev board is placed on a flat plane without any skewness(slantness), a Blue LED lights up indicating the flat surface. This can be used to identify Road-surface anamolies and to study terrains. 

2) Fall Detection - Whenever a fall is made from 50 cm or above, a Fall is detected and a green LED glows up on the FRDM indicating a FALL. The same is also configured to communicate with the UART. Fall detection makes for an important application on smartwatches and smartphones. 

3) Wireless Mouse - Bluetooth Communication was also established to send the X, Y, Z co-rdinates of the accelerometer to the computer. A python script was written to communicate with the received data and PyautoGUI was used to translate the change in acceleromter data to the mouse cursor. However, the data received from the Bluetooth was not correct which resulted in the inability to decode the received data at the computer using Python. 

Following important functions were implemented in the firmware: 

1] Process_fall_detection() - First checks if the user wants Fall Detection, if they do, then checks if fall is detected using a sudden change in Z-Axis. A Green LED and the UART0 is used to demonstrate if the Fall is Detected. 

2] send_data_to_bluetooth() - The received value from the accelerometer for each axis is sent in a pair of two through the UART1. This is because the Sample is 16 bit while the UART1 -> D register is only 8 bits. First we send the MS Byte and then the LS byte for each axis. 

3] Process_accelerometer() - Sends the Read Sequence through i2C to the accelerometer to get the value of X,Y,Z co-ordinates. THis can be later translated to roll
and pitch using the tan inverse function (atan2). 

4] plane_check() - First checks if the Plane Detection is on, if it is, then turns on the BLUE LED indicator to demonstrate the user of the plane flat surface without any skewness. If the board is placed on a surface which appears flat without any slantness, this plane_check can help you identify that. 

Funtionality proposed in the Project Proposal 
1] UART
2] I2C
3] GPIO 
4] Interrupts 
5] Accelrometer 
6] Bluetooth 

Functionality completed as per the proposal 
1) UART
2) I2C
3) GPIO
4) UART Interrupt 
5) Accelerometer

1) Bluetooth - The software for Bluetooth is written and the communication was established between the host computer and the FRDM but the data tranmission was incorrect possibly due to the incorrect initialization of the UART1 [not working entirely]. 

I proposed for Wireless Air Mouse which would have worked if the data recieved from the FRDM to the computer was correct but it was not. So, to demonstrate for this project I worked on Fall and Plane Detection using the Accelerometer which I proposed. 

#Key Observations #

1) Configuring UART0 for external peripheral is not straightforward and requires some sort of mux selection which I browsed through the Kl25z reference manual but couldn't find it. It was because the UART0 and the STDIO is shorted and my message from computer to HC-05 Bluetooth Module was getting routed to the COM port connected to the FRDM for serial communication. THe same data was not coming inside the kl25z MCU chip but was reaching the external UART peripheral. 
 
2) Another thing I observed with the Bluetooth was while configuring UART1 for Bluetooth communication, the S1 register or status register was read only, and I was not able to clear the error flags in the S1 register because it was read only. The S1 register for UART0 can be easily written but the S1 register for UART1 is rad -only, something I couldn't find in the Kl25Z reference Manual. 

3) I checked multiple Githubs, articles, videos  online and couldn't find a single UART1 or UART2 init and there was something that was going wrong with my UART1 Init that the Start condition for UART was not correct. 

# Key Learnings #

1) Learned to configure the AT commands for the Bluetooth Module. 
2) Learned to write a Python Script that can automate Mouse movement and communicate with the Serial port that is assigned while Pairing the HC-05 module with my computer.
3) Found a lot of issues that is a part of UART configuration that was not seen when the printf is getting routed through the STDIO and displayed on the serial terminal. Also learned a lot about the FRDM internal UART circuit from the reference manual while trying to resolve the issue. 
4) The fall Detection was not easy and I learned a lot through Trial and Error which is discussed in the Key challenges Below.  

# Key Challenges #

Fall Detection

Fall was detected using a sudden change in the Z-Axis. I stopped the code execution, created a stationary known point(x,Y,z) in the code, dropped it multiple times from that point and started the code execution simultaneously to detect the changes in the Axes. 

Following were the changes observed - The Z-axis data falls suddenly by the huge margin which is otherwie almost constant. Because of the Padding at each corner of the FRDM and the weight evenly distributed across the FRDM, the Frdm falls horizontally every single time for the brief amount of time while in Air. This was later translated to the change in the X-Axis and fall was detected.

Bluetooth Communication for Wireless Air Mouse

I faced a lot of issues with the Bluetooth communication. Initially I started with the UART0 which I found was too complex without the Muxing required to swtich it from STDIO to UART. The data via the computer connected wirelessly was transmitted to the UART0 pin but was not triggering an interrupt. Same could be seen in the COM port connected through the programming probes with the FRDM on the computer. A detailed video on this can be found here - https://github.com/harshberiwal/PES_Final_Project/blob/main/Test%20Documentations%20%26%20Videos/Bluetooth_demo.mp4. 
