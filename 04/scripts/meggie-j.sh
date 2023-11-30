#!/bin/bash -l
#SBATCH -N 1                # Number of nodes
#SBATCH --ntasks-per-node=1 # Number of tasks per node
#SBATCH --exclusive         # Request exclusive node access
#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 00:10:00         # Maximum job runtime
#SBATCH --constraint=hwperf


# Enable debug and verbose mode
set -x
set -v

module load intel
module load likwid/5.2.1


echo "ArraySize,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" >> result_jacobi.csv

dist=(4686 6767)

for size_KiB in "${dist[@]}"; do
    srun likwid-perfctr -O --stats -C 8 -c 8 -f -m -g "MEM_UOPS_RETIRED_LOADS_ALL:PMC1,MEM_LOAD_UOPS_RETIRED_L1_HIT:PMC2" ./task_4 "$size_KiB" >> result_jacobi.csv
     #likwid-perfctr -O --stats -C 0 -c 0 -f -m -g MEM_UOPS_RETIRED_LOADS_ALL:PMC1,MEM_LOAD_UOPS_RETIRED_L1_HIT:PMC2 ./task_4 "$size_KiB" >> result_jacobi.csv
done

squeue

touch ready
