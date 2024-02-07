#ifndef JACOBI_H
#define JACOBI_H

#include <stdio.h>
#include <stdint.h>

/* This function iterates over a grid to perform a jacobi time step.
 */
void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y);
void jacobi_column_wise(double* grid_source, double* grid_target, uint32_t x, uint32_t y);
void jacobi_spatial_blocking(double* grid_source, double* grid_target, uint32_t x, uint32_t y);
void jacobi_L1_prefetch_blocking(double* grid_source, double* grid_target, uint32_t x, uint32_t y);
void jacobi_subgrid(double *grid_source, double *grid_target, uint32_t x, uint32_t y, uint32_t row_start, uint32_t row_end/*, uint32_t col_start, uint32_t col_end*/);




#endif
