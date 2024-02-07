#!/bin/bash -l

#SBATCH --cpu-freq=2200000  # CPU frequency setting
#SBATCH -t 00:05:00         # Maximum job runtime
#SBATCH --gres=gpu:rtx3080:1

# Enable debug and verbose mode
set -x
set -v

# Load module with CUDA
module load cuda

# Run the CUDA program
srun ../cuda_stream  >> triad_cuda.csv

# Create a file to indicate job completion
touch ready