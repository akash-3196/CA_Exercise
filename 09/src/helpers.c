#define _POSIX_C_SOURCE 199309L
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "helpers.h"


void initialize_grid(double *grid, uint32_t h, uint32_t w)
{

	for (uint32_t i = 0; i < h; ++i)
	{
		for (uint32_t j = 0; j < w; ++j)
		{
			if (i == 0 || j == 0)
			{
				grid[w * i + j] = 1.0;
			}
			else
			{
				grid[w * i + j] = 0.0;
			}
		}
	}
}

void initializeAddKernel(double *grid, uint32_t h, uint32_t w)
{

	for (uint32_t i = 0; i < h; ++i)
	{
		for (uint32_t j = 0; j < w; ++j)
		{
			
				grid[w * i + j] = 3.0;
			
		}
	}
}


void printGrid(double *grid, uint32_t h, uint32_t w)
{

	for (uint32_t i = 0; i < h; ++i)
	{
		for (uint32_t j = 0; j < w; ++j)
		{
			
			printf("i:%" PRId32 " j:%" PRId32 " = %f\t" , i,j, grid[w * i + j]);
			
		}
        printf("\n");
	}
}


void swap(double** grid_target, double** grid_source) {
    double* temp = *grid_target;
    *grid_target = *grid_source;
    *grid_source = temp;
}