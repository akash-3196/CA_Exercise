#ifndef HELPER_FUNC_H
#define HELPER_FUNC_H

#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

/* Initialize the left and top margin with 1.0 and sets the remaining cells to 0.0
   @x grid width
   @y grid height 
 */
  void initialize_grid(double* grid,uint32_t x, uint32_t y);
  void swap(double** grid_target, double** grid_source);
  void insertRandomValue(double* array, size_t size);
  
#endif
