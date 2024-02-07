#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <time.h>
#include <sys/time.h>

#include <cuda.h>
#include <cuda_runtime.h>

#include "get_time.h"
#include "vec_triad.h"

__global__ void triad_kernel(float *A, float *B, float *C, float c, uint32_t N)
{
	uint64_t i = blockIdx.x * blockDim.x + threadIdx.x;
	if (i < N)
		A[i] = B[i] * c + C[i];
}

uint64_t get_time_us(void)
{
	struct timespec a;
	clock_gettime(CLOCK_MONOTONIC, &a);
	return (uint64_t)(((double)a.tv_nsec / 1000.0) + ((double)a.tv_sec * (1000.0 * 1000.0)));
}

void serial_vec_triad(float *A, float *B, float *C, float c, uint64_t vector_size)
{

	for (uint32_t k = 0; k < vector_size; ++k)
	{
		A[k] = B[k] * c + C[k];
	}
	printf("serial_vec_triad:vector_size %" PRId64 "\n", vector_size);
	printf("\n A_RESULT:0: %f", A[0]);
	printf("\n A_RESULT:LAST %f\n", A[vector_size - 1]);
}

int main(int argc, char *argv[])
{
	uint64_t start = 0u;
	uint64_t stop = 0u;
	uint64_t actual_runtime_without_copy = 0u;
	uint64_t actual_runtime_with_copy = 0u;
	float *d_A;
	float *d_B;
	float *d_C;

	uint32_t ARRAY_LENGHT = STREAM_ARRAY_SIZE / sizeof(float);
	// Initialize Arrays
	float *h_A = (float *)malloc(ARRAY_LENGHT * sizeof(float));
	float *h_B = (float *)malloc(ARRAY_LENGHT * sizeof(float));
	float *h_C = (float *)malloc(ARRAY_LENGHT * sizeof(float));
	float c = 0.3; // 0.0 - 1.0

	printf("\n\nSTREAM_ARRAY_SIZE: %d\n", STREAM_ARRAY_SIZE);
	printf("ARRAY_LENGTH: %d\n", ARRAY_LENGHT);

	for (uint32_t i = 0; i < ARRAY_LENGHT; i++)
	{
		h_B[i] = 3.0;
		h_C[i] = 2.0;
	}
	// Allocate memory
	cudaError_t cudaStatus = cudaMalloc((void **)&d_A, sizeof(float) * ARRAY_LENGHT);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc for d_A failed: %s\n", cudaGetErrorString(cudaStatus));
	}
	cudaStatus = cudaMalloc((void **)&d_B, sizeof(float) * ARRAY_LENGHT);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc for d_B failed: %s\n", cudaGetErrorString(cudaStatus));
	}
	cudaStatus = cudaMalloc((void **)&d_C, sizeof(float) * ARRAY_LENGHT);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMalloc for d_C failed: %s\n", cudaGetErrorString(cudaStatus));
	}

	// Copy data from host to device
	cudaStatus = cudaMemcpy(d_B, h_B, sizeof(float) * ARRAY_LENGHT, cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy for d_B failed: %s\n", cudaGetErrorString(cudaStatus));
	}

	cudaStatus = cudaMemcpy(d_C, h_C, sizeof(float) * ARRAY_LENGHT, cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy for d_C failed: %s\n", cudaGetErrorString(cudaStatus));
	}

	// set kernel dimension
	// RTX GPU SM

	uint RTX_MAX_THREAD_BLOCK = 1024;
	int numBlocks = (ARRAY_LENGHT + RTX_MAX_THREAD_BLOCK) / RTX_MAX_THREAD_BLOCK;

	dim3 grid_size(numBlocks);
	dim3 block_size(RTX_MAX_THREAD_BLOCK);

	// Benchmark Triad
	start = get_time_us();
	triad_kernel<<<grid_size, block_size>>>(d_A, d_B, d_C, c, ARRAY_LENGHT);
	cudaDeviceSynchronize();

	// Measuring without Copy operation
	stop = get_time_us();
	actual_runtime_without_copy = stop - start;

	// Copy results back to host
	cudaStatus = cudaMemcpy(h_A, d_A, sizeof(float) * ARRAY_LENGHT, cudaMemcpyDeviceToHost);
	/*if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy for d_A failed: %s\n", cudaGetErrorString(cudaStatus));
	}*/

	// With Copy operation
	stop = get_time_us();
	actual_runtime_with_copy = stop - start;

	// Used for debugging
	printf("\n\nResult Validity:");
	printf("\n \tA[0]: %f", h_A[0]);
	printf("\n \tA[1]: %f\n", h_A[1]);
	int numDots =3;
	for (int i = 0; i < numDots; i++)
	{
		printf("\t  .\n");
	}
	printf(" \tA[%d]: %f", ARRAY_LENGHT - 2, h_A[ARRAY_LENGHT - 2]);
	printf("\n \tA[%d]: %f", ARRAY_LENGHT - 1, h_A[ARRAY_LENGHT - 1]);

	// Calculate the Bandwidth
	uint64_t total_bytes = (3 * sizeof(float) * ARRAY_LENGHT); // =>2 load operations, 1 store operation
	uint64_t mega_bytes_per_second = (total_bytes / (actual_runtime_without_copy * 1e-6)) / 1e6;

	printf("\n\nTotal Bytes Loaded: %d GiB\n\n", (int)(total_bytes / 1e9));
	// Print Benchmark Output
	printf("\nFunction\t\t MB/s\t\t Time\n\n");
	fprintf(stdout, "Triad(Without COPY)   \t %" PRId64 "    \t %" PRId64 "\n", mega_bytes_per_second, actual_runtime_without_copy);


	total_bytes = (3 * sizeof(float) + sizeof(float)) * ARRAY_LENGHT;
	mega_bytes_per_second = (total_bytes / (actual_runtime_with_copy * 1e-6)) / 1e6;
	fprintf(stdout, "Triad(With COPY)   \t %" PRId64 "    \t %" PRId64 "\n\n\n", mega_bytes_per_second, actual_runtime_with_copy);

	free(h_A);
	free(h_B);
	free(h_C);

	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	return 0;
}
