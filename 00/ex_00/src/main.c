#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "vec_sum.h"
#include "get_time.h"

static void usage_msg(void) {
	fprintf(stderr, "Usage: ./vecSum <array size in kiB> <minimal runtime in milliseconds>\n");
	return;
}

int main(int argc, char *argv[]) {
	uint64_t minimal_runtime  = 1e6; // set minimal runtime to 1000000 microseconds = 1 seconds
	uint64_t actual_runtime   = 0u;
	uint64_t array_size_bytes = 0u;  // The allocated array size in bytes
	uint64_t runs             = 0u;
	uint64_t start            = 0u;
	uint64_t stop             = 0u;
	double   adds_per_second  = 0u;

	if(argc != 3 || argv == NULL) {
		usage_msg();
		return -1;
	}

	//TODO: parse parameter: size of the vector in KiB
	array_size_bytes = atoi(argv[1]) * 1024;
	uint32_t arraySize = array_size_bytes/ sizeof(float); // convert Bytes to array length
	//Measurement time in milliseconds
    uint64_t mtime_us = atoi(argv[2])*1000; // from milliseconds to microseconds
	// make sure running time will be >1 seconds
	minimal_runtime = ((mtime_us)>minimal_runtime)? mtime_us:minimal_runtime; 
	//TODO: allocate memory and initialize it
	float * mArr = (float *)malloc(arraySize*sizeof(float));
	//assign value to array elements
	for(uint64_t i=0; i<=arraySize; ++i){
		mArr[i]= 12.0f;  // arbitrary
	}

	//TODO: measurement with a runtime of at least 1 s

	for(runs = 1u; actual_runtime < minimal_runtime; runs = runs << 1u) {
		start = get_time_us();
		for(uint64_t i = 0u; i < runs; i++) {
			// TODO
			vec_sum(mArr, arraySize);
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
	return 0;
}

