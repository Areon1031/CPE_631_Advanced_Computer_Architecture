# genCPIStack.py
# Author: Kyle Ray
# CPE 631 Advanced Computer Architecture
# Project

# Script to generate CPI stack from Likwid output

# Imports
import numpy as np
import matplotlib.pyplot as plt

# Data Variables
# NOTE: Create them as numpy arrays so 
# that they can be added together in the
# bar call, just to get the bottoms correct

# Output
# Groupx:GroupName: CPI|x.xxxx|
# saved in file cpiInfo.txt
# Need to read in this file and parse each group
# generate the stacked bar graph for the gui to use
cpiFile = open("../build-QuickPerformance-Desktop-Debug/cpiInfo.txt", 'r')
count = 0

# Containers to hold the information
groupList = list()
cpiList = list()

# Loop through the file and parse the information
for line in cpiFile:
    # Don't process the first line
    if count != 0:
        # Get the pieces of information
        parseString = line.split(':') 

        # Get the group from the info
        groupList.append(parseString[1])

        # Gather the CPI information if any
        cpiString = parseString[2].split('|')

        # Don't use if CPI not reported
        if cpiString != '-':
            cpiList.append(float(cpiString[1]))
        #end if        
    # end if
    count += 1
#end for

arrayList = list()
colorList = list()

# Generate containers with numpy arrays and assigned colors
for i in range(0, len(cpiList)):
    arrayList.append(np.array(cpiList[i]))
    colorList.append(np.random.random(3))

# Plot the data on a bar graph
plt.bar(0, arrayList[0], color = colorList[0])
margin = 0
for i in range(1, len(cpiList)):
    plt.bar(0, arrayList[i], color = colorList[i], bottom = margin)
    margin += arrayList[i]
# end for

# Set the axis
plt.axis([0, 0, 0, sum(cpiList)])

# Show the plot
plt.show()
#plt.plot()

# Save the figure
plt.savefig("../bin/Results/CPI_Stack.png")
