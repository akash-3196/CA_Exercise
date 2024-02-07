#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


#include <cuda_runtime.h>

#include "vec_triad.h"

//exactly 1 GiByte
#ifndef STREAM_ARRAY_SIZE
#define STREAM_ARRAY_SIZE	1000
#endif


void serial_vec_triad(float* A, float* B, float* C, float c, uint64_t vector_size) {
  
        for (uint32_t k = 0; k < vector_size; ++k) {
            A[k] = B[k]*c + C[k];
        }
}

float get_rand() {
    srand((unsigned int)time(NULL));
    int randInt = rand();
    float randFloat = (float)randInt/RAND_MAX;
    return randFloat;
}
