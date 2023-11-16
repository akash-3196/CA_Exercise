#define _POSIX_C_SOURCE 199309L
#include <stdint.h>
#include <stdio.h>
#include "jacobi.h"
#include "helper_func.h"

void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
	// TODO implement
	for(uint32_t i=1; i<y-1; ++i){
			for(uint32_t j=1; j<x-1; ++j){
					grid_target[x*i +j] =  0.25 *( grid_source[x*i +(j-1)] + grid_source[x*i +(j+1)] + grid_source[x*(i-1) +j] + grid_source[x*(i+1) +j]);  
				//printf("runs: [%d][%d]\n", i, j);   
				//printf("runs: grid[%d][%d]\n", i, j);   
			}
			 //swap (& grid_source , & grid_target );
	}
	
}
