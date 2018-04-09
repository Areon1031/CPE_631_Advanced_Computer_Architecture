import numpy as np
import matplotlib.pyplot as plt

# Data Variables
# NOTE: Create them as numpy arrays so 
# that they can be added together in the
# bar call, just to get the bottoms correct
A = np.array([5., 30., 45., 22.])
B = np.array([5., 25., 50., 20.])
C = np.array([10., 10., 10., 10.])

# X index
X = range(4)

# Create Plot Objects
plt.bar(X, A, color = 'b')
plt.bar(X, B, color = 'r', bottom = A)
plt.bar(X, C, color = 'g', bottom = (A + B))

# Show the plot
#plt.show()
plt.plot()

# Save the Figure
plt.savefig("../bin/Results/CPI_Stack.png")



# Output
# Groupx:GroupName: CPI|x.xxxx|
# saved in file cpiInfo.txt
# Need to read in this file and parse each group
# generate the stacked bar graph for the gui to use
cpiFile = open("../build-QuickPerformance-Desktop-Debug/cpiInfo.txt", 'r')
count = 0

for line in cpiFile:
    # Don't process the first line
    if count != 0:
        # Get the pieces of information
        parseString = line.split(':') 

        # Get the group from the info
        group = parseString[1]

        # Gather the CPI information if any
        cpiString = parseString[2].split('|')
        cpi = cpiString[1]
    # end if

    count += 1
#end for
