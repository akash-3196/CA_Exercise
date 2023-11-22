#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H

#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <mm_malloc.h>
#include <math.h>

#include "draw.h"
#include "vec_sum.h"
#include "jacobi.h"

/* Initialize the left and top margin with 1.0 and sets the remaining cells to 0.0
   @x grid width
   @y grid height 
 */
  void initialize_grid(double* grid,uint32_t x, uint32_t y);
  void swap(double** grid_target, double** grid_source);
  void insertRandomValue(double* array, size_t size);



  void benchmark_vector(float (*vec_sum)(float[], uint32_t), float mArr[], uint32_t arraySize, uint64_t minimal_runtime);
  void benchmark_jacobi(double *grid_src, double *grid_trgt, uint32_t num_cols, uint32_t num_rows) ;
  void engage_vec_sum_benchmark(uint32_t byte_data, uint32_t unroll_factor);
  void engage_jacobi_benchmark(uint32_t kilobyte);
  
#endif
