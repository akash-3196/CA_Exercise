#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <mkl.h>

#include "get_time.h"

void printGrid(double *grid, uint32_t h, uint32_t w)
{

	for (uint32_t i = 0; i < h; ++i)
	{
		for (uint32_t j = 0; j < w; ++j)
		{

			printf("i:%" PRId32 " j:%" PRId32 " = %f\t", i, j, grid[w * i + j]);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	
	uint64_t ArrayLength = ARRAY_SIZE / sizeof(double);
	uint64_t MATRIX_ROW_LENGTH = sqrt(ArrayLength / 3); // Share among square arrays
	uint64_t MATRIX_COL_LENGTH = MATRIX_ROW_LENGTH;

	// printf(" \tTOTAL ARRAY_LENGTH:%f" , ARRAY_SIZE);
	printf("\nJOB_INFO:\n \tROWS:%" PRId64 " COLUMNS:%" PRId64 "\n", MATRIX_ROW_LENGTH, MATRIX_COL_LENGTH);

	double *A = (double *)malloc(MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));
	double *C = (double *)malloc(MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));
	double *B = (double *)malloc(MATRIX_ROW_LENGTH * MATRIX_COL_LENGTH * sizeof(double));

	uint64_t start = 0u;
	uint64_t stop = 0u;
	uint64_t actual_runtime = 0u;
	uint64_t runs = 0u;

	uint64_t minimal_runtime = 1000000;

	uint64_t M = MATRIX_ROW_LENGTH;
	uint64_t K = MATRIX_COL_LENGTH;
	uint64_t N = MATRIX_COL_LENGTH;

	for (uint64_t i = 0; i < N; ++i)
	{
		for (uint64_t j = 0; j < N; ++j)
		{
			A[N * i + j] = 2;
			B[N * i + j] = 3;
		}
	}


	double beta = 0.0;
	double alpha = 1.0;
	printf("A_VALUE: %f\n", A[(N - 1) * (N - 1)]);

	//for (runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u)
	//{
		start = get_time_us();

		//for (uint64_t i = 0u; i < runs; i++)
		//{

			/*
				A = M x K
				B = K x N
				C = M x N

			*/

			cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, M, N, K, alpha, A, K, B, N, beta, C, N);
		//}

		stop = get_time_us();
		actual_runtime = stop - start;
	//}


	printf("\n\nResult Validity:");
	printf("\n \tC[0]: %f", C[0]);
	printf("\n \tC[1]: %f\n", C[1]);
	int numDots = 3;
	for (int i = 0; i < numDots; i++)
	{
		printf("\t  .\n");
	}
	int offset = N * N;
	printf(" \tC[%d]: %f", offset - 2, C[offset - 2]);
	printf("\n \tC[%d]: %f\n", offset - 1, C[offset - 1]);

	// Calculate the Bandwidth
	//runs = runs / 2;
	uint64_t dgemm_FLOPS = 2 * pow(N, 3);
	uint64_t giga_flops_per_second = (dgemm_FLOPS/ (actual_runtime * 1e-6)) / 1e9;

	// Print Benchmark Output
	printf("\n\nFunction\t\t GFLOP/s\t\t Time\n\n");
	printf("CBLAS(CPU)   \t\t %" PRId64 "    \t\t %" PRId64 "\n\n\n", giga_flops_per_second, actual_runtime);




	free(A);
	free(C);
	free(B);

	return 0;
}
