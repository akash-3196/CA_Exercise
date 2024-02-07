#define _POSIX_C_SOURCE 199309L
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "jacobi.h"

// Uncomment the following line to enable twofold unrolling

__global__ void update_grid(double *grid_source, double *grid_target, uint32_t x, uint32_t y)
{
    uint32_t i = blockIdx.x * blockDim.x + threadIdx.x;
    uint32_t j = blockIdx.y * blockDim.y + threadIdx.y;
    //if (i < x && j < x)
    if (i > 0 && i < x && j > 0 && j < x)
    {
        grid_target[x * i + j] = 0.25 * (grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                         grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]);
    }

    //printf("i:%" PRId32  " j:%" PRId32 "\n", i,j);
}

void serial_update_grid(double *grid_source, double *grid_target, uint32_t x, uint32_t y)
{
    for (uint32_t i = 1; i < y - 1; ++i)
    {
        for (uint32_t j = 1; j < x - 1; ++j)
        {
            grid_target[x * i + j] = 0.25 * (grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                             grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]);
        }
    }
}

__global__ void addKernel(double *grid_source, double *grid_target, double *result, uint32_t x, uint32_t y)
{
    uint32_t i = blockIdx.x * blockDim.x + threadIdx.x;
    uint32_t j = blockIdx.y * blockDim.y + threadIdx.y;
    if (i < x && j < x)
    {
        result[x * i + j] = grid_source[x * i + j ] + grid_target[x * i +  j];
    }
}
