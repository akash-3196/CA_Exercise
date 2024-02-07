#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdint.h>

/* This function iterates over a grid to perform a jacobi time step.
 */
void initialize_grid(double *grid, uint32_t h, uint32_t w);
void swap(double** grid_target, double** grid_source);
void initializeAddKernel(double *grid, uint32_t h, uint32_t w);
void printGrid(double *grid, uint32_t h, uint32_t w);

#endif