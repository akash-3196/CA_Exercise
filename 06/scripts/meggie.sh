#!/bin/bash -l
#SBATCH -N 1                # Number of nodes
#SBATCH --ntasks-per-node=1 # Number of tasks per node
#SBATCH --exclusive         # Request exclusive node access
#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 06:00:00         # Maximum job runtime


# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel

echo "ArraySize,MegaUpdatesPerSecond,ActualRuntime,MinimalRuntime" >> result_l1_blocking_$1_.csv



dist=( 1024 1385 1872 2532 3424 4630 6261 8466 11449 15481 20935 28309 38281 51765 70000 94657 128000 173088 234058 316505 427994 578754 782621 1058298 1431084 1935182 2616849 3538634 4785116 6470672 8749963 11832135 16000000)

#dist=( 1024)
#dist=(1 2 3 4 6 9 13 19 27 39 57 82 119 172 248 358 517 746 1077 1556 2247 3245 4686 6767 9773 14113 20380 29431 42502 61378 88636 128000)

for size_KiB in "${dist[@]}"; do
	srun ../task_6 "$size_KiB" >> result_l1_blocking_$1_.csv
done
# Note: copy the result.csv to a local machine!


touch ready
