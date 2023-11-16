#!/bin/bash -l
#SBATCH -N 1                # Number of nodes
#SBATCH --ntasks-per-node=1 # Number of tasks per node
#SBATCH --exclusive         # Request exclusive node access
#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 00:10:00         # Maximum job runtime


# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel

# TODO allocate a compute node
#salloc -N 1 --ntasks-per-node=1 --exclusive --cpu-freq=2200000 -t 02:00:00
# This line creates / overrides a result csv file
echo "ArraySize,AdditionsPerSecond,ActualRuntime,MinimalRuntime" >> result_"$1"_st.csv

# TODO run benchmark 1
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 1 KiB - 128 MiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
#       srun ../bin/vecSum [size of the vector in KiB]
# Estimated exponentially increasing distribution using Geometric progression (max/min)**(1/20)
dist=(1 2 3 6 11 19 34 61 110 199 358 644 1160 2088 3759 6767 12183 21935 39490 71097 128000)
for size_KiB in "${dist[@]}"; do
	srun ../../bin/vecSum "$size_KiB" "$1" >> result_"$1"_st.csv
done
# Note: copy the result.csv to a local machine!


touch ready
