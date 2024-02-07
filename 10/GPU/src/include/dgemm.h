#ifndef JACOBI_H
#define JACOBI_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

/* This function iterates over a grid to perform a jacobi time step.
 */
void gpu_blas_mmul( double *A, double *B, double *C,  uint64_t m,  uint64_t k,  uint64_t n);
#endif
