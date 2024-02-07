#ifndef JACOBI_H
#define JACOBI_H

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

/* This function iterates over a grid to perform a jacobi time step.
 */
__global__ void update_grid(double* grid_source, double* grid_target, uint32_t x, uint32_t y);
void serial_update_grid(double *grid_source, double *grid_target, uint32_t x, uint32_t y);
__global__ void addKernel(double *grid_source, double *grid_target, double *result, uint32_t x, uint32_t y);

#endif
