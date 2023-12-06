#!/usr/bin/bash -l

PMC2=$(cat $1 | grep MEM_LOAD_UOPS_RETIRED_L1_HIT | grep STAT | cut -d , -f 5)
PMC1=$(cat $1 | grep MEM_UOPS_RETIRED_LOADS_ALL | grep STAT | cut -d , -f 5)

echo "$PMC1,"
echo ""
echo "$PMC2,"
