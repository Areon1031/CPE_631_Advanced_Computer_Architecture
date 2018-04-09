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

# TODO: Evenutally this will be passed in as a parameter to python
cpiFile = open("../build-QuickPerformance-Desktop-Debug/cpiInfo.txt", 'r')
count = 0

# Containers to hold the information
groupCPIList = list()
groupList = list()

# Loop through the file and parse the information
for line in cpiFile:
    # Don't process the first line
    if count != 0:
        # Get the pieces of information
        parseString = line.split(':') 

        # Get the group from the info
        group = parseString[1]

        # Create the group list for the legend
        groupList.append(group)

        # Gather the CPI information if any
        cpiList = parseString[2].split('|')

        # Don't use if CPI not reported
        if cpiList[1].find('-') == -1:
            cpiString = cpiList[1]
        else:
            cpiString = '0'
        #end if

        groupCPIList.append((group, float(cpiString)))
    #end if
    count += 1
#end for

print groupCPIList

arrayList = list()
colorList = list()

# Generate containers with numpy arrays and assigned colors
for i in range(0, len(groupCPIList)):
    arrayList.append(np.array(groupCPIList[i][1]))
    colorList.append(np.random.random(3))

# Plot the data on a bar graph
cpiSum = 0
if (len(groupCPIList) > 0):
    plt.bar(0, arrayList[0], color = colorList[0])
    margin = arrayList[0]
    cpiSum += arrayList[0]
    for i in range(1, len(groupCPIList)):
        print arrayList[i]
        plt.bar(0, arrayList[i], color = colorList[i], bottom = margin)
        margin += arrayList[i]
        cpiSum += arrayList[i]
    # end for
# end if

# Set the axis
plt.axis([-1, 1, 0, cpiSum + 1])
plt.gca().legend(groupList)
plt.title("CPI Stack")

# Show the plot
#plt.show()
plt.plot()

# Save the figure
# TODO: Have this save the png in the same directory that is passed in, when that part is finished.
plt.savefig("../bin/Results/CPI_Stack.png")
