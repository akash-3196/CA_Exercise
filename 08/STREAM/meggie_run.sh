#!/bin/bash -l

#SBATCH -N 1                # Number of nodes
#SBATCH --ntasks-per-node=1 # Number of tasks per node
#SBATCH --exclusive         # Request exclusive node access
#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 00:10:00         # Maximum job runtime

#SBATCH --cpus-per-task=20


# Enable debug and verbose mode
set -x
set -v

# Load module with icc compiler
module load intel
module load likwid/5.3.0

srun likwid-pin -c S0:0-9@S1:10-19 ./STREAM_BENCH >> benchmark_stream_meggie.csv


touch ready
