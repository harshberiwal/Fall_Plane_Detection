import serial
import pyautogui
import time
import sys
import signal
	
print(pyautogui.size())

COM=input("Enter the COM Port\n")
BAUD=input("Enter the Baudrate\n")
SerialPort = serial.Serial(COM,BAUD,timeout=1)

while (1):
	try:
		OutgoingData=input('> ')
		SerialPort.write(bytes(OutgoingData,'utf-8'))
	except KeyboardInterrupt:
		print("Closing and exiting the program")
		SerialPort.close()
		sys.exit(0)
	Received_data=SerialPort.readline()
	if(Received_data):
		print((Received_data).decode('utf-8'))
		pyautogui.moveRel(0, 50, duration = 1)
	time.sleep(0.01)
