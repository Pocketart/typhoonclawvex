import serial.tools.list_ports
import serial
import time
import sys
import struct

ports = list(serial.tools.list_ports.comports())

for p in ports:
	if "Arduino" in p[1]:
		print(p[0])

ser = serial.Serial(p[0],9600)
while 1:
	print(ser.readline().decode('utf-8'))
