# genBreakdownChart.py
# Author: Kyle Ray
# CPE 631 Advanced Computer Architecture
# Project

# Script to generate break down chart from perf output

# Imports
import sys
import numpy as np
import matplotlib.pyplot as plt

# Data Variables
# NOTE: Create them as numpy arrays so 
# that they can be added together in the
# bar call, just to get the bottoms correct

# Output
# metric:count

# TODO: Evenutally this will be passed in as a parameter to python
breakdownFile = open(sys.argv[1], 'r')

# Containers to hold the information
metricList = list()
metricCountList = list()

# Loop through the file and parse the information
for line in breakdownFile:
    # Get the pieces of information
    parseString = line.split(':') 

    # Get the metric from the info
    metric = parseString[0]

    # Create the metric list for the legend
    metricList.append(metric)

    # Gather the CPI information if any
    count = parseString[1]

    metricCountList.append((metric, float(count)))
    #end if
#end for

print metricList
print metricCountList

arrayList = list()
colorList = list()

# Generate containers with numpy arrays and assigned colors
for i in range(0, len(metricCountList)):
    arrayList.append(np.array(metricCountList[i][1]))
    colorList.append(np.random.random(3))

# Plot the data on a bar graph
for i in range(0, len(metricCountList)):
    plt.bar(i, arrayList[i], color = colorList[i])

ind = np.arange(0, len(metricCountList))
plt.xticks(ind, metricList, rotation=45)
plt.tight_layout()

# Set the axis
#plt.axis([-1, 1, 0, 1])
plt.title("Break Down Chart")

# Show the plot
#plt.show()
plt.plot()

# Save the figure
# TODO: Have this save the png in the same directory that is passed in, when that part is finished.
plt.savefig(sys.argv[2] + "/PerfBreakdown.png")
