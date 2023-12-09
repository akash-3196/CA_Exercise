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
module load likwid/5.3.0


#echo "ArraySize,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" >> result_jacobi.csv

dist=(1 2 3 4 6 9 13 19 27 39 57 82 119 172 248 358 517 746 1077 1556 2247 3245 4686 6767 9773 14113 20380 29431 42502 61378 88636 128000)

#dist=(4686 6767)

for size_KiB in "${dist[@]}"; do
    #srun likwid-perfctr -O --stats -C 0 -c 0 -f -g NUMA -m ./task_4 "$size_KiB" >> result_likwid.csv
	#srun likwid-perfctr -O --stats -C 0 -g FLOPS_DP -c 0 -m -e FLOPS_DP ../task_4 "$size_KiB" >> result_likwid.csv
   # srun  likwid-perfctr -O --stats -C 0 -g MEM_DP -c 0 -m -e MEM_DP,UOPS ./task_4 "$size_KiB" >> result_likwid.csv
     
        srun likwid-perfctr -O --stats -C 0 -c 0 -f -m -g MEM_UOPS_RETIRED_LOADS_ALL:PMC1,MEM_LOAD_UOPS_RETIRED_L1_HIT:PMC2 ../task_4 "$size_KiB" >> result_likwid_colwise.csv
done

squeue

touch ready
