import sys
import serial
import time

def reset(arduino):
        print "RESET"
        arduino.setDTR(False)
        time.sleep(1)
        arduino.flushInput()
        arduino.setDTR(True)


def readall(to=50):
	time.sleep(0.1)
	ctr = 0
	s = ""
	while True:
		while ser.inWaiting()  > 0:
			c = ser.read()
			s += c
			sys.stdout.write(c),
		time.sleep(0.01)
		if ser.inWaiting()==0:
			ctr +=1
			if ctr==to:
				break
		else:
			ctr = 0	
	print "RESP", s.encode("hex"), repr(s), " LEN = ", len(s)


ser = serial.Serial('/dev/ttyUSB0',19200,)  # open serial port

inp1 = "6425252525252525252525252525252525252500".decode("hex")
inp2 = "010000ffff".decode("hex")

for i in range(26, 256):
	readall()
	print "TEST ", i
	x = inp1 + chr(i) + inp2 +   "\r\n"
	print x, x.encode("hex")
	ser.write(x)
	readall(100)
	readall()
	reset(ser)
	readall(200)

readall()

ser.close()
