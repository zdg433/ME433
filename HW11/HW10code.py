from ulab import numpy as np # to get access to ulab numpy functions
import array
import math
import time
from ulab.utils import spectrogram

dt = 1.0/1024.0 # 1024Hz
t = np.arange(0.0, 1.0, dt) # 1s

s = 4.0 * np.sin(2 * np.pi * 50 * t) + 0.25 * np.sin(2 * np.pi * 1 * t) + np.sin(2 * np.pi * 10 * t)


Fs = 1024 # sample rate
Ts = 1.0/Fs; # sampling interval
ts = np.arange(0,t[-1],Ts) # time vector
y = s # the data to make the fft from
n = len(y) # length of the signal
k = np.arange(n)
T = n/Fs
frq = k/T # two sides frequency range
frq = frq[range(int(n/2))] # one side frequency range

Y = spectrogram(s) # fft magnitude
for x in Y[:512]:
    print("("+str(x)+",)")
    time.sleep(.003) # delay in seconds

