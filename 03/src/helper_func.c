#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <mm_malloc.h>
#include <math.h>


#include "get_time.h"
#include "draw.h"
#include "helper_func.h"
#include "vec_sum.h"
#include "jacobi.h"


	
/* Initialize the left and top margin with 1.0 and sets the remaining cells to 0.0
   @x grid height
   @y grid width 
 */

uint64_t minimal_runtime  = 1e6; // set minimal runtime to 1000000 microseconds = 1 seconds
uint64_t   mega_updates_per_second  = 0u;
double   adds_per_second  = 0u;
uint64_t grid_size_bytes= 0u;

void initialize_grid(double* grid, uint32_t h, uint32_t w){


	for(uint32_t i=0; i<h; ++i){
		for(uint32_t j=0; j<w; ++j){
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


void benchmark_vector(float (*vec_sum)(float[], uint32_t), float mArr[], uint32_t arraySize, uint64_t minimal_runtime) {
    uint64_t start = 0u;
    uint64_t stop= 0u;
    uint64_t actual_runtime= 0u;
    uint64_t runs= 0u;

    for (runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
        start = get_time_us();

        for (uint64_t i = 0u; i < runs; i++) {
            // TODO: Make sure vec_sum is properly defined and returns a result
            vec_sum(mArr, arraySize);
        }

        stop = get_time_us();
        actual_runtime = stop - start;
    }
}

void benchmark_jacobi(double *grid_src, double *grid_trgt, uint32_t num_cols, uint32_t num_rows) {
    uint64_t start = 0u;
    uint64_t stop= 0u;
    uint64_t actual_runtime= 0u;
    uint64_t runs= 0u;

    for (runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
        start = get_time_us();

        for (uint64_t i = 0u; i < runs; i++) {
            // TODO: Make sure jacobi and swap functions are properly defined
            jacobi(grid_src, grid_trgt, num_cols, num_rows);
            swap(&grid_trgt, &grid_src);
        }

        stop = get_time_us();
        actual_runtime = stop - start;
    }


    //printf("Program Code ran successfully!\n");
	char file_path[50];
	sprintf(file_path, "jacobi_heat_map_%dx%d.ppm", num_rows, num_cols);


	//draw_grid(grid_src, grid_width, grid_height, file_path);
	draw_grid(grid_trgt, num_cols, num_rows, file_path);
 
	//TODO: calculate and print
	//1 FLOP per iteration in the vec_sum
	runs= runs/2;
	mega_updates_per_second = ((1*runs*(num_rows-2)*(num_cols-2))/ (actual_runtime * 1e-6))/1e6;


	//fprintf(stdout, "%" PRIu64 ",%lf,%" PRIu64 ",%" PRIu64 "\n", mega_updates_per_second, actual_runtime, minimal_runtime,edge_size);
fprintf(stdout, "%lu,%" PRIu64 ",%lf,%" PRIu64  "\n", grid_size_bytes, mega_updates_per_second, (double)actual_runtime, minimal_runtime);

	    // Free the allocated memory
        _mm_free(grid_trgt);
        _mm_free(grid_src);
}


void engage_vec_sum_benchmark(uint32_t byte_data, uint32_t unroll_factor){

//TODO: parse parameter: size of the vector in KiB
	uint64_t array_size_bytes = byte_data * 1024;
	uint64_t arraySize = array_size_bytes/ sizeof(float); // convert Bytes to array length
    
   
   
	//TODO: allocate memory and initialize it
	float * mArr = (float *)malloc(arraySize*sizeof(float));
	//assign value to array elements
	for(uint64_t i=0; i<=arraySize; ++i){
		mArr[i]= 12.0f;  // arbitrary
	}
 
    uint64_t start = 0u;
    uint64_t stop= 0u;
    uint64_t actual_runtime= 0u;
    uint64_t runs= 0u;

    for (runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
        start = get_time_us();
		for(uint64_t i = 0u; i < runs; i++) {
			// TODO
			vec_sum(mArr, runs * arraySize);
		}
		stop  = get_time_us();
		actual_runtime = stop - start;
	}
 
	//TODO: calculate and print
	//1 FLOP per iteration in the vec_sum
	//adds_per_second = (1*arraySize)/ (actual_runtime * 1e-6); // Measured performance as floating point additions per second
	runs= runs/2;
	adds_per_second = (1*runs*arraySize)/ (actual_runtime * 1e-6);


	fprintf(stdout, "%" PRIu64 ",%lf,%" PRIu64 ",%" PRIu64 "\n", array_size_bytes, adds_per_second, actual_runtime, minimal_runtime);
        // Free the allocated memory
        free(mArr);

     
}

void engage_jacobi_benchmark(uint32_t kilobyte){


    grid_size_bytes = kilobyte * 1024;
	uint64_t gridLength = grid_size_bytes/ sizeof(double); 


	//_mm_malloc() with alignment on 64 B.
	double * grid_trgt = (double *)_mm_malloc(gridLength*sizeof(double), 64);
	double * grid_src = (double *)_mm_malloc(gridLength*sizeof(double), 64);

// Check if memory allocation is successful
   /* if (grid_trgt == NULL || grid_src == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    */
		
	//We assume that the given grid size is a linearized array
	//hence division by 2 
	
	uint64_t edge_size= sqrt(gridLength/2);
	uint64_t num_rows = edge_size;
	uint64_t num_cols =  num_rows;
    //printf("Jacobi starated... x=y=%lu\n", num_rows);

    	//Initialize the left and top margin with 1.0 and sets the remaining cells to 0.0 
	initialize_grid(grid_src, num_rows, num_cols);
	initialize_grid(grid_trgt, num_rows, num_cols);

    //TODO: measurement with a runtime of at least 1 s
	benchmark_jacobi(grid_src,grid_trgt, num_cols, num_rows);




}