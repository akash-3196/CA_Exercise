#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#include <likwid-marker.h>


#include "get_time.h"
#include "helper_func.h"

// Check if LIKWID_PERFMON is defined

static void usage_msg(void) {
	//fprintf(stderr, "Usage: ./jacobi  <Grid Height> <Grid Width>\n");
	fprintf(stderr, "Usage: ./jacobi  grid_size_KiB\n");
	return;
}

int main(int argc, char *argv[]) {



	if(argc != 2 || argv == NULL) {
		usage_msg();
		return -1;
	}
	
	#ifdef LIKWID_PERFMON
		printf("LIKWID_PERFMON Available\n");
	#else
		printf("NO Likwid!!\n");
	#endif


	uint32_t kilobyte_arg = atoi(argv[1]);
	
//Start Vec_sum benchmark
	//engage_vec_sum_benchmark(kilobyte_arg, 4);


//Start jacobi benchmark
	engage_jacobi_benchmark(kilobyte_arg);



	return 0;
}

