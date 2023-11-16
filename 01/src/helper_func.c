#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>
#include <inttypes.h>
#include "helper_func.h"
#include <time.h>

/* Initialize the left and top margin with 1.0 and sets the remaining cells to 0.0
   @x grid height
   @y grid width 
 */
void initialize_grid(double* grid, uint32_t h, uint32_t w){


	for(uint64_t i=0; i<h; ++i){
		for(uint64_t j=0; j<w; ++j){
			if(i==0  || j==0){
				 grid[w*i +j]=1.0;
			}
			else{
				grid[w*i +j]=0.0;
			}
           
	    }
	}
}

void swap(double** grid_target, double** grid_source) {
    double* temp = *grid_target;
    *grid_target = *grid_source;
    *grid_source = temp;
}


void insertRandomValue(double* array, size_t size) {
    // Seed the random number generator
    srand(time(NULL));

    // Generate a random double value between 0 and 1
    double randomValue = (double)rand() / RAND_MAX;

    // Insert the random value into the array
    array[size] = randomValue;
}
