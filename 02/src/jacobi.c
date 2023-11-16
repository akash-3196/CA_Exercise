#define _POSIX_C_SOURCE 199309L
#include <stdint.h>
#include <stdio.h>
#include "jacobi.h"

/*
void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
	// TODO implement
	for(uint32_t i=1; i<y-1; ++i){
			for(uint32_t j=1; j<x-1; ++j){
					grid_target[x*i +j] =  0.25 * (grid_source[x*i +(j-1)] + grid_source[x*i +(j+1)] + grid_source[x*(i-1) +j] + grid_source[x*(i+1) +j]);   
			}
			 
	}
	
}
*/



// Uncomment the following line to enable twofold unrolling
// #define TWOFOLD_UNROLLING

// Uncomment the following line to enable fourfold unrolling
// #define FOURFOLD_UNROLLING

void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
    // TODO implement

    for(uint32_t i = 1; i < y - 1; ++i) {
        for(uint32_t j = 1; j < x - 1; ++j) {

            #ifdef TWOFOLD_UNROLLING
                // Twofold unrolling
                grid_target[x * i + j] = 0.25 * (
                    grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                    grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                );
                ++j; // Move to the next iteration
            #elif defined(FOURFOLD_UNROLLING)
                // Fourfold unrolling
                grid_target[x * i + j] = 0.25 * (
                    grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                    grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                );
                ++j;
                grid_target[x * i + j] = 0.25 * (
                    grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                    grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                );
                ++j; // Move to the next iteration
            #else
                // No unrolling
                grid_target[x * i + j] = 0.25 * (
                    grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                    grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                );
            #endif
        }
    }
}
