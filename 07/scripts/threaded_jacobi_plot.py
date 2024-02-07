
#Vectorization

#Plots data obtained from HPC benchmarking of Jacobi with variant unrolling factors
#
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter
import pandas as pd
import os
import sys



# Define a function to read CSV and return x and y axes
def read_csv(file_path):
    df = pd.read_csv(file_path, delimiter=",")
    x_axis = df['Thread'].to_numpy()
    y_axis = df['MegaUpdatesPerSecond'].to_numpy()
    return x_axis, y_axis

# Define file paths
if len(sys.argv) != 2:
    print("Usage: python cache_effects_plot.py path_to_files")
    sys.exit(1)

# Access the path provided as an argument
path_to_file = sys.argv[1]


directory_path = '../server_data/' + path_to_file  # Update this with your actual directory path
file_prefix = 'threads_plot'


# List all files in the directory that start with the specified prefix
matching_files = [f for f in os.listdir(directory_path) if f.startswith(file_prefix)]

# Create full file paths by joining the directory path and file names
file_paths = [os.path.join(directory_path, f) for f in matching_files]

#print(len(file_paths))


colors = ['#009999', '#CC0000', '#0000CC', '#007F00', '#CC00CC', '#FFD700', '#FF8C00', '#8000FF', '#664200', '#008080']
labels =[]
for file_path in file_paths:
    file_name = os.path.basename(file_path)
    label = file_name.replace(file_prefix + '_', '').replace('.csv', '')
    labels.append(label)

matplotlib.rc('figure', figsize=(12, 5))
x_axis =[]
y_axis =[]
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
ax.yaxis.set_major_formatter(formatter)


#plt.xscale('log')
plt.xticks(range(1, 21))
plt.xlabel("Threads")
plt.ylabel("MegaUpdatesPerSecond")
plt.legend()
plt.grid()
plt.legend()
plt.show()
