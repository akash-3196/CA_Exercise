import sys
import numpy as np

# Read data from a text file (assuming the data is in a file named 'data.txt')
if len(sys.argv)>1:
    file_path = sys.argv[1]
    
else:
    print(f"No file name specified in the commandline")
    sys.exit(1)
# Initialize lists to store ArraySize and AdditionsPerSecond
array_sizes = []
additions_per_second = []

# Read data from the file and populate the lists
with open(file_path, 'r') as file:
    for line in file:
        if line.strip() and not line.startswith('ArraySize'):
            values = line.strip().split(',')
            array_size = int(values[0])
            additions = float(values[1])
            benchmark_time  = float(values[3])
            array_sizes.append(array_size)
            additions_per_second.append(additions)

# Calculate the standard deviation
standard_deviation = np.std(additions_per_second, ddof=1)
#print(np.mean(additions_per_second))
std_percentage = (standard_deviation / np.mean(additions_per_second)) * 100


# Print the result
data_to_append =f"Standard Deviation -  AdditionsPerSecond: {std_percentage:.2f}% at inputed benchmark of {benchmark_time} microsecond\n"
#print(data_to_append)
#data_to_append =f"Standard Deviation -  AdditionsPerSecond: {standard_deviation:.2f}% at inputed benchmark of {benchmark_time} microsecond\n"


archive_st = "archive_st"
with open(archive_st, 'a') as file:
    # Append the data to the file
    file.write(data_to_append)
