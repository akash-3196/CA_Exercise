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
#define JACOBI_UNROLLING 1

// Uncomment the following line to enable fourfold unrolling
// #define FOURFOLD_UNROLLING

void jacobi(double* grid_source, double* grid_target, uint32_t x, uint32_t y) {
    // TODO implement
    #ifdef JACOBI_UNROLLING

        #if JACOBI_UNROLLING == 2
               //debugger: printf("JACOBI_FACTOR = TWO\n");
            for(uint32_t i = 1; i < y - 1; ++i) {

                # pragma novector
                # pragma nounroll
                for(uint32_t j = 1; j < x - 1; j+=JACOBI_UNROLLING) {
                     grid_target[x * i + j] = 0.25 * (
                            grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                            grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                        );
                        grid_target[x * i + (j+1)] = 0.25 * (
                            grid_source[x * i + (j)] + grid_source[x * i + (j + 2)] +
                            grid_source[x * (i - 1) + (j+1)] + grid_source[x * (i + 1) + (j+1)]
                        );
                        
                }
            }
        #elif JACOBI_UNROLLING == 4
            //debugger: printf("JACOBI_FACTOR = FOUR\n");
            for(uint32_t i = 1; i < y - 1; ++i) {

                # pragma novector
                # pragma nounroll
                for(uint32_t j = 1; j < x - 1; j+=JACOBI_UNROLLING) {
                     grid_target[x * i + j] = 0.25 * (
                            grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                            grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                        );
                    grid_target[x * i + (j+1)] = 0.25 * (
                            grid_source[x * i + (j)] + grid_source[x * i + (j + 2)] +
                            grid_source[x * (i - 1) + (j+1)] + grid_source[x * (i + 1) + (j+1)]
                        );

                    grid_target[x * i + (j+2)] = 0.25 * (
                            grid_source[x * i + (j+1)] + grid_source[x * i + (j + 3)] +
                            grid_source[x * (i - 1) + (j+2)] + grid_source[x * (i + 1) + (j+2)]
                        );
                    grid_target[x * i + (j+3)] = 0.25 * (
                            grid_source[x * i + (j+2)] + grid_source[x * i + (j + 4)] +
                            grid_source[x * (i - 1) + (j+3)] + grid_source[x * (i + 1) + (j+3)]
                        );
                        
                }
            }
         #else
        //debugger: printf("JACOBI_FACTOR = ONE\n");
            for(uint32_t i = 1; i < y - 1; ++i) {

                    # pragma novector
                    # pragma nounroll
                    for(uint32_t j = 1; j < x - 1; ++j) {
                        grid_target[x * i + j] = 0.25 * (
                                grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                                grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                            );
                    }
                }

         #endif

    #else 

            for(uint32_t i = 1; i < y - 1; ++i) {

                # pragma novector
                # pragma nounroll
                for(uint32_t j = 1; j < x - 1; ++j) {
                     grid_target[x * i + j] = 0.25 * (
                            grid_source[x * i + (j - 1)] + grid_source[x * i + (j + 1)] +
                            grid_source[x * (i - 1) + j] + grid_source[x * (i + 1) + j]
                        );
                }
            }
        
    #endif
}
