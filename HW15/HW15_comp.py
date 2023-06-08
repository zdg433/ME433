# get a line of raw bitmap and plot the components
import serial
ser = serial.Serial('COM4',230400) # the name of your Pico port
print('Opening port: ')
print(ser.name)

ser.write(b'hi\r\n') # send a newline to request data
data_read = ser.read_until(b'\n',50) # read the echo

sampnum = 0
index = 0
raw = []
reds = []
greens = []
blues = []
bright = []

# Pico sends back index and raw pixel value
while sampnum < 60: # width of bitmap
    data_read = ser.read_until(b'\n',50) # read until newline
    data_text = str(data_read,'utf-8') # convert bytes to string
    data = list(map(int,data_text.split())) # convert string to values

    if(len(data)==2):
        index = data[0]
        raw.append(data[1])
        reds.append(((data[1]>>5)&0x3F)/0x3F*100) # red value is middle 6 bits
        greens.append((data[1]&0x1F)/0x1F*100) # green value is rightmost 5 bits
        blues.append(((data[1]>>11)&0x1F)/0x1F*100) # blue vale is leftmost 5 bits
        bright.append((data[1]&0x1F)+((data[1]>>5)&0x3F)+((data[1]>>11)&0x1F)) # sum of colors
        sampnum = sampnum + 1

# print the raw color as a 16bit binary to double check bitshifting
for i in range(len(reds)):
    print(f"{raw[i]:#018b}")

# plot the colors 
import matplotlib.pyplot as plt 
x = range(len(reds)) # time array
plt.plot(x,reds,'r*-',x,greens,'g*-',x,blues,'b*-')
plt.ylabel('color')
plt.xlabel('position')
plt.show()
red_COM = 0
blue_COM = 0
green_COM = 0
in_sum = 0

for i in range(len(reds)):
    if reds[i] > 40:
        red_COM = red_COM + reds[i]*i
    if reds[i] > 20:
        blue_COM = blue_COM + blues[i]*i
    if reds[i] > 20:
        green_COM = green_COM + greens[i]*i
    
    in_sum = in_sum + i

red_COM = red_COM/in_sum
blue_COM = blue_COM/in_sum
green_COM = green_COM/in_sum

COM = (red_COM + blue_COM + green_COM)/3

print(COM)

# be sure to close the port
ser.close()