#!/bin/bash -l
#SBATCH -N 1                # Number of nodes
#SBATCH --ntasks-per-node=1 # Number of tasks per node
#SBATCH --exclusive         # Request exclusive node access
#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 00:05:00         # Maximum job runtime
#SBATCH --constraint=hwperf


# Enable debug and verbose mode
set -x
set -v

module load intel
module load likwid/5.3.0


echo "ArraySize,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" >> result_jacobi.csv

dist=(4686 6767)

for size_KiB in "${dist[@]}"; do
     likwid-perfctr -O --stats -C 1 -c 1 -f -m -g L3 \
    #likwid-perfctr -O --stats -C 0 -c 0 -f -m -g L3 
	../bin/benchmark_loop "$size_KiB" >> result_jacobi.csv
done

squeue

touch ready
