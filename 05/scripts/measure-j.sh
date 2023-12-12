#!/bin/bash -l
module load intel

sbatch ./meggie-j.sh

while [ ! -f ready ]; do
	sleep 60
done
rm ready

