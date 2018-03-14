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
plt.show()
