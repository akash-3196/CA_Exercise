#!/bin/bash -l
module load intel

sbatch ./meggie_st.sh "$1"

while [ ! -f ready ]; do
	sleep 60
done
rm ready

