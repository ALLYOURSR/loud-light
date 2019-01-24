import matplotlib.pyplot as plt
import math
import numpy as np

xvals = np.arange(0, 300, .5)

perception_yvals = np.zeros(xvals.shape)
output_yvals = np.zeros(xvals.shape)

for i in range(len(xvals)):
    x = xvals[i]
    perception_yvals[i] = (math.log(x + 1)/.055452)
    output_yvals[i] = math.exp(.055352 * x) - 1

f, ax = plt.subplots(1, 1)

ax.plot(xvals, perception_yvals, label="Human Perception")
ax.plot(xvals, output_yvals, label="Corrected Brightness")
ax.plot(xvals, xvals, label="Perceived Brightness")

plt.title("Brightness Perception Correction")
plt.xlabel("True Output Intensity")
plt.ylabel("Intensity (Perceived and Corrected)")

ax.set_xlim([0,255])
ax.set_ylim([0,255])

handles, labels = ax.get_legend_handles_labels()
plt.legend(handles, labels)
plt.show()