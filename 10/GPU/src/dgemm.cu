//#define _POSIX_C_SOURCE 199309L
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include <curand.h>

extern "C"
{
#include "dgemm.h"
}

// Uncomment the following line to enable twofold unrolling

void gpu_blas_mmul(double *A, double *B, double *C, uint64_t m, uint64_t k, uint64_t n)
{
    int lda = m, ldb = k, ldc = m;
    double alf = 1;
    double bet = 0;
    double *alpha = &alf;
    double *beta = &bet;

    // Create a handle for CUBLAS
    cublasHandle_t handle;
    cublasCreate(&handle);

    // Do the actual multiplication
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
    // Destroy the handle
    cublasDestroy(handle);
}