#!/bin/bash -l
#SBATCH -N 1                # Number of nodes
#SBATCH --ntasks-per-node=1 # Number of tasks per node
#SBATCH --exclusive         # Request exclusive node access
#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 00:05:00         # Maximum job runtime


# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel

# TODO allocate a compute node
#salloc -N 1 --ntasks-per-node=1 --exclusive --cpu-freq=2200000 -t 02:00:00
# This line creates / overrides a result csv file
echo "ArraySize,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" >> result_cache_effects.csv

# TODO run benchmark 1
# execute measurement with for loop
# 32 measurement points, exponentially distributed: 1 KiB - 128 MiB, each with 1000 ms as minimal runtime
# results should be appended to the result.csv (see >> operator)
# input parameter:
# to run an executable:
#       srun ../bin/vecSum [size of the vector in KiB]
# Estimated exponentially increasing distribution using Geometric progression (max/min)**(1/32)


# The actual range below 1KiB to 128MiB produces segmentation error after 15KiB
dist=( 1024 1385 1872 2532 3424 4630 6261 8466 11449 15481 20935 28309 38281 51765 70000 94657 128000 173088 234058 316505 427994 578754 782621 1058298 1431084 1935182 2616849 3538634 4785116 6470672 8749963 11832135 16000000)
#So i used the below range just for testing for now
#dist=(1 2 3 4 5 6 7 8 9 10 11 12 13 14 15)
for size_KiB in "${dist[@]}"; do
	srun ../task_5 "$size_KiB" >> result_cache_effects.csv
done
# Note: copy the result.csv to a local machine!


touch ready
