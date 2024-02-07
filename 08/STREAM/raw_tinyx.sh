#!/bin/bash -l

srun --cpu-freq=2200000 -t 00:10:00 --gres=gpu:rtx3080:1 likwid-pin -c S0:0-7@S1:8-15 ./STREAM_BENCH