#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include <cuda.h>
#include <cuda_runtime.h>
#include <cublas_v2.h>
#include <curand.h>

extern "C"
{
#include "get_time.h"
}
extern "C"
{
#include "dgemm.h"
}


int main(int argc, char *argv[])
{
	uint64_t start = 0u;
	uint64_t stop = 0u;
	uint64_t actual_runtime_without_copy = 0u;
	uint64_t actual_runtime_with_copy = 0u;

	// uint64_t actual_runtime = 0u;
	uint64_t runs = 0u;
	//uint64_t minimal_runtime = 1000000;

	uint64_t ArrayLength = ARRAY_SIZE / sizeof(double);
	uint64_t MATRIX_ROW_LENGTH = sqrt(ArrayLength / 3); // Share among square arrays
	uint64_t MATRIX_COL_LENGTH = MATRIX_ROW_LENGTH;

	uint64_t N = MATRIX_ROW_LENGTH;

	double *h_A = (double *)malloc(MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));
	double *h_C = (double *)malloc(MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));
	double *h_B = (double *)malloc(MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));

	printf("\nJOB_INFO:\n \tROWS:%" PRId64 " COLUMNS:%" PRId64 "\n", N, N);
	//printf(" \tNUMBER OF GRID POINTS:%ld" , ARRAY_SIZE);

	double *d_A, *d_B, *d_C;
	cudaMalloc(&d_A, MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));
	cudaMalloc(&d_B, MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));
	cudaMalloc(&d_C, MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));

	for (uint64_t i = 0; i < N; ++i)
	{
		for (uint64_t j = 0; j < N; ++j)
		{
			h_A[N * i + j] = 2;
			h_B[N * i + j] = 3;
		}
	}

	// Copy data from host to device
	uint64_t preMemTimeStart = get_time_us();
	cudaMemcpy(d_A, h_A, sizeof(double) * (N * N), cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, sizeof(double) * (N * N), cudaMemcpyHostToDevice);
	uint64_t preMemTime = get_time_us() - preMemTimeStart;
	/*if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed for one of the memory copy operations: %s\n", cudaGetErrorString(cudaStatus));
	}*/

	// set kernel dimension
	// RTX GPU SM
	// 32x32 =1024
	//uint RTX_MAX_THREAD_BLOCK = 1024;
	//uint x_count = sqrt(RTX_MAX_THREAD_BLOCK);
	//uint y_count = x_count;

	//dim3 block_size(x_count, y_count);
	//uint x = (MATRIX_COL_LENGTH + block_size.x - 1) / block_size.x;
	//uint y = (MATRIX_ROW_LENGTH + block_size.y - 1) / block_size.y;
	//dim3 grid_size(x, y);

	//printf("\n\n \tGPU KERNEL:\n \t\tGRID_SIZE:%dx%d  BLOCK_SIZE:%dx%d  \n", grid_size.x, grid_size.y, block_size.y, block_size.x);

	// for (runs = 1u; actual_runtime_without_copy < minimal_runtime; runs = runs << 1u)
	//{
	start = get_time_us();

	// for (uint64_t i = 0u; i < runs; i++)
	//{
	gpu_blas_mmul(d_A, d_B, d_C, MATRIX_ROW_LENGTH, MATRIX_COL_LENGTH, MATRIX_COL_LENGTH);
	//}

	stop = get_time_us();
	actual_runtime_without_copy = stop - start;
	//}

	uint64_t postMemTimeStart = get_time_us();
	cudaMemcpy(h_C, d_C, sizeof(double) * (N * N), cudaMemcpyDeviceToHost);
	uint64_t postMemTime = get_time_us() - preMemTimeStart;

	actual_runtime_with_copy = actual_runtime_without_copy + (preMemTime + postMemTime);

	printf("\n\nResult Validity:");
	printf("\n \th_C[0]: %f", h_C[0]);
	printf("\n \th_C[1]: %f\n", h_C[1]);
	int numDots = 3;
	for (int i = 0; i < numDots; i++)
	{
		printf("\t  .\n");
	}
	uint offset = N * N;
	printf(" \th_C[%d]: %f", offset - 2, h_C[offset - 2]);
	printf("\n \th_C[%d]: %f\n", offset - 1, h_C[offset - 1]);

	// Calculate the Bandwidth
	//runs = runs / 2;

	uint64_t dgemm_FLOPS = 2 * pow(N, 3);

	uint64_t giga_flops_per_second = (dgemm_FLOPS / (actual_runtime_without_copy * 1e-6)) / 1e9;

	// Print Benchmark Output
	printf("\n\nFunction\t\t GFLOP/s\t\t Time\n\n");
	printf("CBLAS(Without COPY)   \t %" PRId64 "    \t %" PRId64 "\n", giga_flops_per_second, actual_runtime_without_copy);

	giga_flops_per_second = (dgemm_FLOPS / (actual_runtime_with_copy * 1e-6)) / 1e9;
	fprintf(stdout, "CBLAS(With COPY)   \t %" PRId64 "    \t %" PRId64 "\n\n\n", giga_flops_per_second, actual_runtime_with_copy);



	free(h_A);
	free(h_B);
	free(h_C);

	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	return 0;
}
