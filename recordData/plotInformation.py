import numpy as np
import matplotlib.pyplot as plt
file = "information" +  raw_input()  + ".txt"
xr = [float(l.split()[0]) for l in open(file)]
yr = [float(l.split()[1]) for l in open(file)]
thetar = [float(l.split()[2]) for l in open(file)]
xq = [float(l.split()[3]) for l in open(file)]
yq = [float(l.split()[4]) for l in open(file)]
thetaq = [float(l.split()[5]) for l in open(file)]
uCommond = [float(l.split()[6]) for l in open(file)]
wCommond = [float(l.split()[7]) for l in open(file)]
uReal = [float(l.split()[8]) for l in open(file)]
wReal = [float(l.split()[9]) for l in open(file)]
e1 = [float(l.split()[10]) for l in open(file)]
e2 = [float(l.split()[11]) for l in open(file)]
e3 = [float(l.split()[12]) for l in open(file)]

fig1 = plt.figure(figsize=[8,6])
ax = fig1.add_subplot(111)
ax.plot(np.array(xr),np.array(yr),'r-',label = 'xr-yr')
ax.plot(np.array(xq),np.array(yq),'g-',label = 'xq-yq')
ax.legend()
fig1.show()

fig2 = plt.figure(figsize=[8,6])
ax1 = fig2.add_subplot(211)
ax1.plot(np.array(uCommond),'r-',label = 'uCommond')
ax1.plot(np.array(uReal),'g-',label = 'uReal')
ax1.legend()
ax2 = fig2.add_subplot(212)
ax2.plot(np.array(wCommond),'r-',label = 'wCommond')
ax2.plot(np.array(wReal),'g-',label = 'wReal')
ax2.legend()
fig2.show()

fig3 = plt.figure(figsize=[8,6])
ax = fig3.add_subplot(111)
ax.plot(np.array(e1),'r-',label = 'e1')
ax.plot(np.array(e2),'g-',label = 'e2')
ax.plot(np.array(e3),'b-',label = 'e3')
ax.legend()
fig3.show()

fig4 = plt.figure(figsize=[8,6])
ax = fig4.add_subplot(111)
ax.plot(np.array(thetar),'r-',label = 'thetar')
ax.legend()
fig4.show()

raw_input()
