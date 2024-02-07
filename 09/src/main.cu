#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <time.h>
#include <sys/time.h>

#include <cuda.h>
#include <cuda_runtime.h>

extern "C"
{
#include "draw.h"
}
extern "C"
{
#include "get_time.h"
}
extern "C"
{
#include "helpers.h"
}
#include "jacobi.h"

// #define GRID_SIZE 3000000000

int main(int argc, char *argv[])
{
	uint64_t start = 0u;
	uint64_t stop = 0u;
	uint64_t actual_runtime_without_copy = 0u;
	uint64_t actual_runtime_with_copy = 0u;

	//uint64_t actual_runtime = 0u;
	uint64_t runs = 0u;
	//uint64_t minimal_runtime = 1000000; // 1 sec
	//uint64_t minimal_runtime = 100000; // 100 millisec
	uint64_t minimal_runtime = 10000000; //10 sec

	double *d_gridSource;
	double *d_gridTarget;
	// double *d_result;

	uint64_t gridLength = GRID_SIZE / sizeof(double);
	uint64_t edge_size = sqrt(gridLength) - 4;
	//printf(" edge_size:%" PRId64 "\n", edge_size);

	uint64_t num_rows = edge_size;
	uint64_t num_cols = num_rows;

	double *h_gridSource = (double *)malloc(gridLength * sizeof(double));
	double *h_gridTarget = (double *)malloc(gridLength * sizeof(double));
	double *h_resultGrid = (double *)malloc(gridLength * sizeof(double));

	initialize_grid(h_gridSource, num_rows, num_cols);
	initialize_grid(h_gridTarget, num_rows, num_cols);

	// initializeAddKernel(h_gridSource, num_rows, num_cols);
	// initializeAddKernel(h_gridTarget, num_rows, num_cols);

	printf("\nJOB_INFO:\n \tROWS:%" PRId64 " COLUMNS:%" PRId64 "\n", num_rows, num_cols);
	printf(" \tNUMBER OF GRID POINTS:%" PRId64, gridLength);

	// Allocate memory
	cudaMalloc((void **)&d_gridSource, sizeof(double) * gridLength);
	cudaMalloc((void **)&d_gridTarget, sizeof(double) * gridLength);
	// cudaMalloc((void **)&d_result, sizeof(double) * gridLength);

	// Copy data from host to device
	uint64_t preMemTimeStart = get_time_us();
	cudaMemcpy(d_gridSource, h_gridSource, sizeof(double) * gridLength, cudaMemcpyHostToDevice);
	cudaMemcpy(d_gridTarget, h_gridTarget, sizeof(double) * gridLength, cudaMemcpyHostToDevice);
	uint64_t preMemTime = get_time_us() - preMemTimeStart;
	/*if (cudaStatus != cudaSuccess)
	{
		fprintf(stderr, "cudaMemcpy failed for one of the memory copy operations: %s\n", cudaGetErrorString(cudaStatus));
	}*/

	// set kernel dimension
	// RTX GPU SM
	// 32x32 =1024
	uint RTX_MAX_THREAD_BLOCK = 1024;
	uint x_count = sqrt(RTX_MAX_THREAD_BLOCK);
	uint y_count = x_count;

	dim3 block_size(x_count, y_count);
	uint x = (num_cols + block_size.x - 1) / block_size.x;
	uint y = (num_rows + block_size.y - 1) / block_size.y;
	dim3 grid_size(x, y);

	printf("\n\n \tGPU KERNEL:\n \t\tGRID_SIZE:%dx%d  BLOCK_SIZE:%dx%d  \n",  grid_size.x, grid_size.y, block_size.y, block_size.x);

	

	for (runs = 1u; actual_runtime_without_copy < minimal_runtime; runs = runs << 1u)
	{
		start = get_time_us();

		for (uint64_t i = 0u; i < runs; i++)
		{
			// serial_update_grid(h_gridSource, h_gridTarget, num_cols, num_rows);
			// swap(&h_gridSource, &h_gridTarget);

			update_grid<<<grid_size, block_size>>>(d_gridSource, d_gridTarget, num_cols, num_rows);
			// addKernel<<<grid_size, block_size>>>(d_gridSource, d_gridTarget, d_result, num_cols, num_rows);

			cudaDeviceSynchronize();
			swap(&d_gridTarget, &d_gridSource);
		}

		stop = get_time_us();
		actual_runtime_without_copy = stop - start;
	}

	uint64_t postMemTimeStart = get_time_us();
	cudaMemcpy(h_resultGrid, d_gridTarget, sizeof(double) * gridLength, cudaMemcpyDeviceToHost);
	uint64_t postMemTime = get_time_us() - preMemTimeStart;

	actual_runtime_with_copy = actual_runtime_without_copy + (preMemTime + postMemTime);

	// debugger:
	// h_resultGrid = h_gridTarget; //to be deleted

	// printGrid(h_resultGrid, num_rows, num_cols);
	printf("\n\nResult Validity:");
	printf("\n \th_resultGrid[0]: %f", h_resultGrid[0]);
	printf("\n \th_resultGrid[1]: %f\n", h_resultGrid[1]);
	int numDots = 3;
	for (int i = 0; i < numDots; i++)
	{
		printf("\t  .\n");
	}
	uint offset = num_cols * num_rows;
	printf(" \th_resultGrid[%d]: %f", offset - 2, h_resultGrid[offset - 2]);
	printf("\n \th_resultGrid[%d]: %f\n", offset - 1, h_resultGrid[offset - 1]);

	char file_path[50];
	sprintf(file_path, "jacobi_heat_map_%" PRId64 "x%" PRId64 ".ppm", num_rows, num_cols);

	// draw_grid(h_resultGrid, num_cols, num_rows, file_path);

	// Calculate the Bandwidth
	runs= runs/2;
	uint64_t total_bytes = (5 * sizeof(double) * gridLength * runs); // =>4 load operations, 1 store operation
	uint64_t mega_bytes_per_second = (total_bytes / (actual_runtime_without_copy * 1e-6)) / 1e6;

	printf("\n\nTotal Bytes Loaded: %d GiB\n\n", (int)(total_bytes / 1e9));
	// Print Benchmark Output
	printf("\nFunction\t\t MB/s\t\t Time\n\n");
	printf("JACOBI(Without COPY)   \t %" PRId64 "    \t %" PRId64 "\n", mega_bytes_per_second, actual_runtime_without_copy);

	total_bytes = ((5 * sizeof(double)*runs) + sizeof(double)) * gridLength;
	mega_bytes_per_second = (total_bytes / (actual_runtime_with_copy * 1e-6)) / 1e6;
	fprintf(stdout, "JACOBI(With COPY)   \t %" PRId64 "    \t %" PRId64 "\n\n\n", mega_bytes_per_second, actual_runtime_with_copy);

	free(h_gridSource);
	free(h_gridTarget);
	free(h_resultGrid);

	cudaFree(d_gridSource);
	cudaFree(d_gridTarget);
	// cudaFree(d_result);

	return 0;
}
