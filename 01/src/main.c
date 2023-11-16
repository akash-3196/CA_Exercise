#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <mm_malloc.h>

#include "jacobi.h"
#include "draw.h"
#include "get_time.h"
#include "helper_func.h"

static void usage_msg(void) {
	//fprintf(stderr, "Usage: ./jacobi  <Grid Height> <Grid Width>\n");
	fprintf(stderr, "Usage: ./jacobi  grid_size_KiB\n");
	return;
}

int main(int argc, char *argv[]) {
	uint64_t minimal_runtime  = 1e6; // set minimal runtime to 1000000 microseconds = 1 seconds
	uint64_t actual_runtime   = 0u;
	uint64_t grid_size_bytes = 0u;  // The allocated array size in bytes
	uint32_t num_rows = 0u;  // 
	uint32_t num_cols = 0u;  // 

	uint64_t runs             = 0u;
	uint64_t start            = 0u;
	uint64_t stop             = 0u;
	uint64_t   mega_updates_per_second  = 0u;
	uint64_t edge_size = 0u;


	if(argc != 2 || argv == NULL) {
		usage_msg();
		return -1;
	}
	
	//Get grid dimensions from command line
	//grid_height = atoi(argv[1]);
	//grid_width = atoi(argv[2]);
	grid_size_bytes = atoi(argv[1]) * 1024;
	uint64_t gridLength = grid_size_bytes/ sizeof(double); 
	
	
	//_mm_malloc() with alignment on 64 B.
	double * grid_trgt = (double *)_mm_malloc(gridLength*sizeof(double), 64);
	double * grid_src = (double *)_mm_malloc(gridLength*sizeof(double), 64);

// Check if memory allocation is successful
    if (grid_trgt == NULL || grid_src == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
		
	//We assume that the given grid size is a linearized array
	//hence division by 2 
	
	edge_size= sqrt(gridLength/2);
	num_rows = edge_size;
	num_cols =  num_rows;

	

	//Initialize the left and top margin with 1.0 and sets the remaining cells to 0.0 
	initialize_grid(grid_src, num_rows, num_cols);
	initialize_grid(grid_trgt, num_rows, num_cols);
	
	//TODO: measurement with a runtime of at least 1 s
	for(runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
		start = get_time_us();
		for(uint64_t i = 0u; i < runs; i++) {
			// TODO
			jacobi(grid_src,grid_trgt, num_cols, num_rows);
			swap (& grid_trgt , & grid_src );
		}
		
		stop  = get_time_us();
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
fprintf(stdout, "%lu,%" PRIu64 ",%lf,%" PRIu64 ",%" PRIu64 "\n", grid_size_bytes, mega_updates_per_second, (double)actual_runtime, minimal_runtime, edge_size);

	    // Free the allocated memory
        _mm_free(grid_trgt);
        _mm_free(grid_src);
	return 0;
}

