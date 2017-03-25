import csv
import sys
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import subprocess
from io import StringIO   # StringIO behaves like a file object

# y = np.empty((1,100000))
COUNT = 20
ITR = 100000


y = np.empty([COUNT, ITR])
cmd = ['./uct.out', '1']

for i in range(0, COUNT):
  out = subprocess.check_output(cmd)
  cur_data = StringIO(out.decode())
  x,cur_y = np.loadtxt(cur_data, delimiter=",", unpack=True)
  y[i] = cur_y

print(y)
mean = np.mean(y, axis=0)
std = np.std(y, axis=0)
print(std)

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
ax1.set_title('B = 8, D = 4')
ax1.set_xlabel('number of iterartion')
ax1.set_ylabel('lose rate')
ax1.set_xscale("log")
ax1.set_yscale("log", nonposy='clip')
ax1.set_ylim((1.0e-6,1.0))

erange = np.logspace(1.0,5.0, num=5, dtype=np.uint64) - 1
ax1.errorbar(erange, mean[erange], yerr=std[erange], fmt='o')
ax1.plot(x, mean, label="UCT")

ax1.legend()
fig.savefig("loserate.pdf")
