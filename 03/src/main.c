#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


#include "get_time.h"
#include "helper_func.h"

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
	

	uint32_t kilobyte_arg = atoi(argv[1]);
	
//Start Vec_sum benchmark
	//engage_vec_sum_benchmark(kilobyte_arg, 4);


//Start jacobi benchmark
	engage_jacobi_benchmark(kilobyte_arg);



	return 0;
}

