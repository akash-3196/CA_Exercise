#!/usr/bin/bash -l

#LOADS=$(cat $1 | grep MEM_UOPS_RETIRED_LOADS | grep STAT | cut-d , -f 5)
LOADS=$(cat $1 | grep MEM_UOPS_RETIRED_LOADS | cut -d , -f 1)

echo $LOADS