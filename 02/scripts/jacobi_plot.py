#Plots data obtained from HPC benchmarking of Jacobi with variant unrolling factors
#
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter
import pandas as pd

# Define a function to read CSV and return x and y axes
def read_csv(file_path):
    df = pd.read_csv(file_path, delimiter=",")
    x_axis = df['ArraySize'].to_numpy()
    y_axis = df['MegaUpdatesPerSecond'].to_numpy()
    return x_axis, y_axis

# Define file paths
file_paths = [
  '../server_data/jacobi/u1/result_jacobi.csv',
  '../server_data/jacobi/u2/result_jacobi.csv',
  '../server_data/jacobi/u4/result_jacobi.csv',
]

# Read CSV files and plot
colors = [ 'blue', 'green', 'red']
labels = [ 'NO_UNROLL', 'UNROLL = 2', 'UNROLL = 4']

matplotlib.rc('figure', figsize=(12, 5))

for file_path, color, label in zip(file_paths, colors, labels):
    x_axis, y_axis = read_csv(file_path)
    plt.plot(x_axis, y_axis, 'o-', color=color, label=label)

# Set plot details
formatter = ScalarFormatter()
formatter.set_scientific(False)

# Apply the formatter to the x-axis
# Get the current axes
ax = plt.gca()
ax.xaxis.set_major_formatter(formatter)
plt.xlabel("Memory Consumption (KiB)")
plt.ylabel("MegaUpdatesPerSecond")
plt.grid()
plt.legend()
plt.show()
