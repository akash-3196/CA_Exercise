#!/bin/bash -l
#SBATCH -N 1                # Number of nodes
#SBATCH --ntasks-per-node=1 # Number of tasks per node
#SBATCH --exclusive         # Request exclusive node access
#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 00:30:00         # Maximum job runtime

#SBATCH --cpus-per-task=20


# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel
module load likwid/5.3.0

echo "ArraySize,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" >> parallel_jacobi.csv


#4GB -> 4,194,304 KB
#dist=(1024 1328 1722 2233 2896 3756 4871 6317 8192 10624 13777 17867 23170 30048 38968 50535 65536 84990 110218 142935 185364 240387 311744 404281 524288 679917 881744 1143480 1482910 1923097 2493948 3234251 4000000)
#dist=(4000000)
dist=(1024)

for size_KiB in "${dist[@]}"; do
	#srun likwid-pin -c E:S0:0-9:1:1@S1:10-19:1:1 ../task_7 "$size_KiB" >> parallel_jacobi.csv
	#srun likwid-pin -c 0-9@10-19 ../task_7 "$size_KiB" >> parallel_jacobi.csv
	#srun likwid-pin -c E:S0:10:1:1@S1:2:1:1 ../task_7 "$size_KiB" >> parallel_jacobi.csv
	srun likwid-pin -c S0:0-9@S1:10-19 ../task_7 "$size_KiB" >> parallel_jacobi.csv
done
# Note: copy the result.csv to a local machine! #SBATCH --constraint=hwperf


touch ready
