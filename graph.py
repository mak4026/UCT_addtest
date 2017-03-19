import csv
import sys
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

x,y = np.loadtxt(sys.stdin, delimiter=",", unpack=True)

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
ax1.set_title('B = 8, D = 8')
ax1.set_xlabel('number of iterartion')
ax1.set_ylabel('lose rate')
ax1.set_xscale("log")
ax1.set_yscale("log")

ax1.plot(x, y, label="UCT")
ax1.legend()
fig.savefig("loserate.pdf")
