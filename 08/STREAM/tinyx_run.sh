#!/bin/bash -l

#SBATCH -N 1                # Number of nodes
#SBATCH --exclusive         # Request exclusive node access
#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 00:10:00         # Maximum job runtime
#SBATCH --gres=gpu:rtx3080:1


# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel

srun likwid-pin -c 0-7@8-15 ./STREAM_BENCH >> benchmark_stream_tinyx.csv


touch ready
