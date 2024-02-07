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
module load mkl
module load likwid/5.3.0




#srun likwid-pin -c S0:0-9@S1:10-19 ../bin/LINPACK_CPU  >> cbas_cpu.csv
srun ../bin/LINPACK_CPU  >> cbas_cpu.csv

#SBATCH --constraint=hwperf


touch ready
