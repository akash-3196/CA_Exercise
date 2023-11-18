#Plots data obtained from HPC benchmarking of vector sum unrolling variants
#
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter
import pandas as pd

# Define a function to read CSV and return x and y axes
def read_csv(file_path):
    df = pd.read_csv(file_path, delimiter=",")
    x_axis = df['ArraySize'].to_numpy()
    y_axis = df['AdditionsPerSecond'].to_numpy()
    return x_axis, y_axis

# Define file paths
file_paths = [
    '../server_data/vecsum/result_u1.csv',
    '../server_data/vecsum/result_u2.csv',
    '../server_data/vecsum/result_u3.csv',
    '../server_data/vecsum/result_u4.csv',
     '../server_data/vecsum/result_u8.csv',
]

# Read CSV files and plot
colors = [ 'black', 'blue', 'green', 'red', 'purple']
labels = [ 'NO_UNROLL','UNROLL = 2', 'UNROLL = 3', 'UNROLL = 4', 'UNROLL = 8']

matplotlib.rc('figure', figsize=(12, 5))

for file_path, color, label in zip(file_paths, colors, labels):
    x_axis, y_axis = read_csv(file_path)
    plt.plot(x_axis, y_axis, 'o-', color=color, label=label)

# Set plot details
# Set plot details
formatter = ScalarFormatter()
formatter.set_scientific(False)

# Apply the formatter to the x-axis
# Get the current axes
ax = plt.gca()
ax.xaxis.set_major_formatter(formatter)
ax.yaxis.set_major_formatter(formatter)

#plt.xscale('log')

plt.xlabel("Memory Consumption (KiB)")
plt.ylabel("AdditionsPerSecond")
plt.grid()
plt.legend()
plt.show()
